#!/usr/bin/env python3
"""UDP telemetry receiver for the Sun Sensor project.

Defaults follow the project's initial-setup addresses:
- Bind (receive) address: 10.0.0.1:53335 (default)
- Remote (send) address: 10.0.0.2:54345 (used by the RPi)

This simple receiver binds a UDP socket and prints each received datagram
with a timestamp and source address. Use `--bind` and `--port` to override
the defaults.
"""
from __future__ import annotations

import argparse
import datetime
import socket
import sys
import logging

# Module-level logger; configured in __main__ from CLI
logger = logging.getLogger("receiver")


def run(bind_ip: str, bind_port: int, bufsize: int = 4096, outfile: str | None = None) -> None:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((bind_ip, bind_port))

    print(f"Listening for UDP on {bind_ip}:{bind_port} (buffer={bufsize})")
    out_f = open(outfile, "ab") if outfile else None

    try:
        while True:
            data, addr = sock.recvfrom(bufsize)
            ts = datetime.datetime.now().isoformat(sep=" ", timespec="milliseconds")
            src = f"{addr[0]}:{addr[1]}"
            logger.info("[%s] %s %d bytes", ts, src, len(data))

            # Try to print as UTF-8 text, otherwise show hex
            try:
                text = data.decode("utf-8")
            except UnicodeDecodeError:
                text = None

            if text is not None:
                # Log text payload (strip trailing newlines only for readability)
                logger.info(text.rstrip("\n"))
            else:
                # Print a short hex summary for binary payloads
                hex_preview = data.hex()
                if len(hex_preview) > 512:
                    hex_preview = hex_preview[:512] + "..."
                logger.info("hex: %s", hex_preview)

            if out_f:
                # Simple binary append: [timestamp] [src ip:port]\n[data]\n
                header = f"[{ts}] {src} {len(data)} bytes\n".encode("utf-8")
                out_f.write(header)
                out_f.write(data)
                out_f.write(b"\n")
                out_f.flush()

    except KeyboardInterrupt:
        logger.info("Interrupted, shutting down")
    finally:
        sock.close()
        if out_f:
            out_f.close()


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="UDP telemetry receiver (defaults from project spec)")
    p.add_argument("--bind", "-b", default="10.0.0.1", help="IP address to bind to (default: 10.0.0.1)")
    p.add_argument("--port", "-p", type=int, default=53335, help="Port to bind to (default: 53335)")
    p.add_argument("--bufsize", type=int, default=4096, help="Max UDP payload size to receive")
    p.add_argument("--outfile", "-o", default=None, help="Optional file to append received datagrams to")
    p.add_argument("--log-level", "-l", default="INFO",
                   choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"],
                   help="Logging level (default: INFO)")
    return p.parse_args()


if __name__ == "__main__":
    args = parse_args()
    # Configure logging from CLI
    logging.basicConfig(
        level=getattr(logging, args.log_level.upper(), logging.INFO),
        format="%(asctime)s %(levelname)s: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )
    logger = logging.getLogger("receiver")

    try:
        run(args.bind, args.port, args.bufsize, args.outfile)
    except Exception:
        logger.exception("Unhandled error in receiver")
        sys.exit(1)
