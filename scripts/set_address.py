#!/usr/bin/env python3
"""Send an address-change command to the PSS Array over UDP.

Two commands are supported (see manual Tables 19 & 22):

  set_cmd_address "IP:port"   -- change the IP:port on which the PSS
                                  receives commands (default 10.0.0.2:54345)

  set_tlm_address "IP:port"   -- change the IP:port to which the PSS sends
                                  telemetry (default 10.0.0.1:53335)

Example usage
-------------
# Point the sensor to receive commands on a new address:
python set_address.py cmd 10.0.0.5:54345

# Update the telemetry destination:
python set_address.py tlm 10.0.0.3:53335

# Reach a sensor that has already been moved to a non-default address:
python set_address.py cmd 10.0.0.5:54345 --sensor-ip 10.0.0.7 --sensor-port 54345
"""
from __future__ import annotations

import argparse
import ipaddress
import logging
import socket
import sys

logger = logging.getLogger("set_address")

# ── defaults from the manual ─────────────────────────────────────────────────
DEFAULT_SENSOR_IP = "10.0.0.2"
DEFAULT_SENSOR_PORT = 54345


def _validate_address(address: str) -> str:
    """Validate 'IP:port' string; return it normalised or raise ValueError."""
    try:
        ip_str, port_str = address.rsplit(":", 1)
        ipaddress.ip_address(ip_str)          # raises if invalid
        port = int(port_str)
        if not (0 < port < 65536):
            raise ValueError(f"Port {port} out of range 1-65535")
    except ValueError as exc:
        raise ValueError(
            f"Invalid address '{address}'. Expected format: IP:port  (e.g. 10.0.0.2:54345)"
        ) from exc
    return address


def build_command(kind: str, new_address: str) -> bytes:
    """Return the ASCII command bytes for the requested address change."""
    if kind == "cmd":
        cmd = f'set_cmd_address "{new_address}"'
    else:
        cmd = f'set_tlm_address "{new_address}"'
    return cmd.encode("ascii")


def send_command(
    sensor_ip: str,
    sensor_port: int,
    payload: bytes,
    bind_ip: str = "0.0.0.0",
    bind_port: int = 0,
) -> None:
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        sock.bind((bind_ip, bind_port))
        sock.sendto(payload, (sensor_ip, sensor_port))
        logger.info(
            "Sent %d bytes to %s:%d  →  %s",
            len(payload),
            sensor_ip,
            sensor_port,
            payload.decode("ascii"),
        )
    finally:
        sock.close()


def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Change the command or telemetry IP:port of the PSS Array.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    p.add_argument(
        "kind",
        choices=["cmd", "tlm"],
        help=(
            "'cmd' → set_cmd_address (where the PSS listens for commands); "
            "'tlm' → set_tlm_address (where the PSS sends telemetry)"
        ),
    )
    p.add_argument(
        "new_address",
        metavar="IP:PORT",
        help="New address in IP:port format, e.g. 10.0.0.5:54345",
    )
    p.add_argument(
        "--sensor-ip",
        default=DEFAULT_SENSOR_IP,
        help=f"Current IP of the PSS sensor (default: {DEFAULT_SENSOR_IP})",
    )
    p.add_argument(
        "--sensor-port",
        type=int,
        default=DEFAULT_SENSOR_PORT,
        help=f"Current command port of the PSS sensor (default: {DEFAULT_SENSOR_PORT})",
    )
    p.add_argument(
        "--bind-ip",
        default="0.0.0.0",
        help="Local IP to bind the send socket to (default: 0.0.0.0)",
    )
    p.add_argument(
        "--log-level",
        "-l",
        default="INFO",
        choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"],
        help="Logging level (default: INFO)",
    )
    return p.parse_args()


if __name__ == "__main__":
    args = parse_args()

    logging.basicConfig(
        level=getattr(logging, args.log_level.upper(), logging.INFO),
        format="%(asctime)s %(levelname)s: %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

    try:
        new_address = _validate_address(args.new_address)
        ipaddress.ip_address(args.sensor_ip)
    except ValueError as exc:
        logger.error("%s", exc)
        sys.exit(1)

    payload = build_command(args.kind, new_address)

    try:
        send_command(
            sensor_ip=args.sensor_ip,
            sensor_port=args.sensor_port,
            payload=payload,
            bind_ip=args.bind_ip,
        )
    except OSError as exc:
        logger.error("Socket error: %s", exc)
        sys.exit(1)
