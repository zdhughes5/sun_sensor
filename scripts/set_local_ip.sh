#!/usr/bin/env bash
# set_ip.sh — Assign a static IP address to a network interface.
#
# Usage:
#   sudo ./set_ip.sh [INTERFACE] [IP/PREFIX]
#
# Defaults (sun sensor project):
#   INTERFACE : enp0s31f6
#   IP/PREFIX : 10.0.0.1/24

set -euo pipefail

IFACE="${1:-enp0s31f6}"
ADDR="${2:-10.0.0.1/24}"

if [[ $EUID -ne 0 ]]; then
    echo "Error: this script must be run as root (use sudo)." >&2
    exit 1
fi

if ! ip link show "$IFACE" &>/dev/null; then
    echo "Error: interface '$IFACE' not found." >&2
    echo "Available interfaces:" >&2
    ip -o link show | awk -F': ' '{print "  " $2}' >&2
    exit 1
fi

# Remove any existing addresses on the interface, then assign the new one
ip addr flush dev "$IFACE"
ip addr add "$ADDR" dev "$IFACE"
ip link set "$IFACE" up

echo "Set $IFACE → $ADDR"
ip addr show dev "$IFACE"
