#!/usr/bin/env python3
"""Send GPS and ADC control commands to the PSS Array over UDP.

Supported commands (see examples/gps_commands.c for C equivalents):

  connect    <baud> <device>   -- connect the GPS (e.g. 9600 /dev/ttyS0)
  disconnect                   -- disconnect the GPS
  reset-adc  <index>           -- force-reset ADC by index (e.g. 0, 1, …)

Example usage
-------------
# Connect the GPS on /dev/ttyS0 at 9600 baud:
python gps_commands.py connect 9600 /dev/ttyS0

# Disconnect the GPS:
python gps_commands.py disconnect

# Force-reset ADC 0:
python gps_commands.py reset-adc 0

# Target a sensor that is not at the default address:
python gps_commands.py connect 9600 /dev/ttyS0 --sensor-ip 10.0.0.5 --sensor-port 54345
"""
from __future__ import annotations

import argparse
import logging
import socket
import sys

logger = logging.getLogger("gps_commands")

# ── defaults from the manual ─────────────────────────────────────────────────
DEFAULT_SENSOR_IP = "10.0.0.2"
DEFAULT_SENSOR_PORT = 54345


# ── reusable command builders ─────────────────────────────────────────────────

def build_gps_connect_command(baud: int, device: str) -> bytes:
    """Return the ASCII command bytes to connect the GPS.

    Parameters
    ----------
    baud:
        Baud rate (e.g. ``9600``).
    device:
        Serial device path (e.g. ``/dev/ttyS0``).
    """
    return f"gps_connect {baud} '{device}'".encode("ascii")


def build_gps_disconnect_command() -> bytes:
    """Return the ASCII command bytes to disconnect the GPS."""
    return b"gps_disconnect"


def build_adc_force_reset_command(index: int) -> bytes:
    """Return the ASCII command bytes to force-reset an ADC.

    Parameters
    ----------
    index:
        Zero-based ADC index (e.g. ``0`` produces ``adc0_force_reset``).
    """
    return f"adc{index}_force_reset".encode("ascii")


# ── transport ─────────────────────────────────────────────────────────────────

def send_command(
    sensor_ip: str,
    sensor_port: int,
    payload: bytes,
    bind_ip: str = "0.0.0.0",
    bind_port: int = 0,
) -> None:
    """Send *payload* to the PSS Array via UDP.

    Parameters
    ----------
    sensor_ip:
        IP address of the PSS Array.
    sensor_port:
        UDP port on which the PSS Array listens for commands.
    payload:
        Raw bytes to transmit.
    bind_ip:
        Local interface to bind the send socket to.
    bind_port:
        Local port to bind to (``0`` lets the OS choose).
    """
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


# ── high-level convenience wrappers ───────────────────────────────────────────

def connect_gps(
    baud: int,
    device: str,
    sensor_ip: str = DEFAULT_SENSOR_IP,
    sensor_port: int = DEFAULT_SENSOR_PORT,
    **kwargs,
) -> None:
    """Connect the GPS and send the command to *sensor_ip*:*sensor_port*."""
    send_command(sensor_ip, sensor_port, build_gps_connect_command(baud, device), **kwargs)


def disconnect_gps(
    sensor_ip: str = DEFAULT_SENSOR_IP,
    sensor_port: int = DEFAULT_SENSOR_PORT,
    **kwargs,
) -> None:
    """Disconnect the GPS."""
    send_command(sensor_ip, sensor_port, build_gps_disconnect_command(), **kwargs)


def force_reset_adc(
    index: int,
    sensor_ip: str = DEFAULT_SENSOR_IP,
    sensor_port: int = DEFAULT_SENSOR_PORT,
    **kwargs,
) -> None:
    """Force-reset the ADC at *index*."""
    send_command(sensor_ip, sensor_port, build_adc_force_reset_command(index), **kwargs)


# ── CLI ───────────────────────────────────────────────────────────────────────

def parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(
        description="Send GPS / ADC control commands to the PSS Array.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    p.add_argument(
        "--sensor-ip",
        default=DEFAULT_SENSOR_IP,
        help=f"IP address of the PSS Array (default: {DEFAULT_SENSOR_IP})",
    )
    p.add_argument(
        "--sensor-port",
        type=int,
        default=DEFAULT_SENSOR_PORT,
        help=f"UDP command port of the PSS Array (default: {DEFAULT_SENSOR_PORT})",
    )
    p.add_argument(
        "--bind-ip",
        default="0.0.0.0",
        help="Local IP to bind the send socket to (default: 0.0.0.0)",
    )
    p.add_argument(
        "--log-level",
        default="INFO",
        choices=["DEBUG", "INFO", "WARNING", "ERROR"],
        help="Logging verbosity (default: INFO)",
    )

    sub = p.add_subparsers(dest="command", metavar="COMMAND", required=True)

    # connect sub-command
    connect_p = sub.add_parser("connect", help="Connect the GPS")
    connect_p.add_argument("baud", type=int, help="Baud rate (e.g. 9600)")
    connect_p.add_argument("device", help="Serial device path (e.g. /dev/ttyS0)")

    # disconnect sub-command
    sub.add_parser("disconnect", help="Disconnect the GPS")

    # reset-adc sub-command
    reset_p = sub.add_parser("reset-adc", help="Force-reset an ADC by index")
    reset_p.add_argument("index", type=int, help="Zero-based ADC index (e.g. 0)")

    return p.parse_args()


def main() -> None:
    args = parse_args()

    logging.basicConfig(
        level=args.log_level,
        format="%(asctime)s %(levelname)s %(name)s: %(message)s",
    )

    common = dict(
        sensor_ip=args.sensor_ip,
        sensor_port=args.sensor_port,
        bind_ip=args.bind_ip,
    )

    if args.command == "connect":
        connect_gps(args.baud, args.device, **common)
    elif args.command == "disconnect":
        disconnect_gps(**common)
    elif args.command == "reset-adc":
        force_reset_adc(args.index, **common)
    else:
        # argparse required=True should prevent reaching here
        logger.error("Unknown command: %s", args.command)
        sys.exit(1)


if __name__ == "__main__":
    main()
