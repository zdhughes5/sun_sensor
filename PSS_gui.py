#!/usr/bin/env python3
"""PyQt6 GUI for the Sun Sensor telemetry receiver.

The static window shell (main window, connection bar, tab widget) is defined
in ``main_window.ui`` and can be edited freely in Qt Designer.  Dynamic
content — the 6 PSS panels, overview fields, GPS/ADC fields — is built in
Python and attached to named QScrollArea widgets from the .ui at startup.

Usage
-----
    python gui.py [--bind <ip>] [--port <port>] [--schema <path>]

Defaults match the project spec: bind 10.0.0.1:53335.
"""
from __future__ import annotations

import argparse
import datetime
import pathlib
import socket
import sys
import threading
from typing import Optional

from PyQt6 import uic
from PyQt6.QtCore import Qt, QThread, pyqtSignal
from PyQt6.QtGui import QFont
from PyQt6.QtWidgets import (
    QApplication,
    QFrame,
    QGridLayout,
    QGroupBox,
    QLabel,
    QMainWindow,
    QVBoxLayout,
    QWidget,
)

_UI_FILE = pathlib.Path(__file__).parent / "ui" / "main_window.ui"

from receiver import build_parser, parse_packet

NUM_PSS = 6


# ---------------------------------------------------------------------------
# Background worker thread
# ---------------------------------------------------------------------------

class UDPWorker(QThread):
    """Receives UDP packets in a background thread and emits parsed data."""

    packet_received = pyqtSignal(dict)
    status_changed = pyqtSignal(str)
    error_occurred = pyqtSignal(str)

    def __init__(
        self,
        bind_ip: str,
        bind_port: int,
        schema_path: Optional[str] = None,
        bufsize: int = 4096,
        parent=None,
    ) -> None:
        super().__init__(parent)
        self.bind_ip = bind_ip
        self.bind_port = bind_port
        self.schema_path = schema_path
        self.bufsize = bufsize
        self._stop_event = threading.Event()

    def stop(self) -> None:
        self._stop_event.set()

    def run(self) -> None:
        try:
            fields = build_parser(self.schema_path)
        except Exception as exc:
            self.error_occurred.emit(f"Schema load failed: {exc}")
            return

        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            sock.settimeout(1.0)
            sock.bind((self.bind_ip, self.bind_port))
        except OSError as exc:
            self.error_occurred.emit(f"Socket error: {exc}")
            return

        self.status_changed.emit(f"Listening on {self.bind_ip}:{self.bind_port}")

        try:
            while not self._stop_event.is_set():
                try:
                    data, _addr = sock.recvfrom(self.bufsize)
                except socket.timeout:
                    continue

                # Skip plain-text packets (e.g. debug prints from the RPi)
                try:
                    data.decode("utf-8")
                    continue
                except UnicodeDecodeError:
                    pass

                parsed = parse_packet(data, fields)
                if parsed:
                    self.packet_received.emit(parsed)
        finally:
            sock.close()
            self.status_changed.emit("Disconnected")


# ---------------------------------------------------------------------------
# Small reusable widget helpers
# ---------------------------------------------------------------------------

_MONO_FONT = QFont("Monospace")
_MONO_FONT.setStyleHint(QFont.StyleHint.Monospace)


def _value_label(initial: str = "—") -> QLabel:
    lbl = QLabel(initial)
    lbl.setAlignment(Qt.AlignmentFlag.AlignRight | Qt.AlignmentFlag.AlignVCenter)
    lbl.setMinimumWidth(100)
    lbl.setFont(_MONO_FONT)
    return lbl


class BoolIndicator(QLabel):
    """Coloured pill that shows YES (green) / NO (red) / — (neutral)."""

    _STYLE_YES = (
        "background:#2d6a2d; color:#90ee90; border-radius:4px;"
        " padding:1px 8px; font-weight:bold;"
    )
    _STYLE_NO = (
        "background:#6a2d2d; color:#ee9090; border-radius:4px;"
        " padding:1px 8px; font-weight:bold;"
    )
    _STYLE_NEUTRAL = "border-radius:4px; padding:1px 8px;"

    def __init__(self, parent=None) -> None:
        super().__init__("—", parent)
        self.setAlignment(Qt.AlignmentFlag.AlignCenter)
        self.setMinimumWidth(55)
        self.setStyleSheet(self._STYLE_NEUTRAL)

    def set_value(self, val: int) -> None:
        if val:
            self.setText("YES")
            self.setStyleSheet(self._STYLE_YES)
        else:
            self.setText("NO")
            self.setStyleSheet(self._STYLE_NO)


def _hline() -> QFrame:
    line = QFrame()
    line.setFrameShape(QFrame.Shape.HLine)
    line.setFrameShadow(QFrame.Shadow.Sunken)
    return line


# ---------------------------------------------------------------------------
# Per-PSS sensor panel
# ---------------------------------------------------------------------------

class PSSPanel(QGroupBox):
    """Compact grid showing all telemetry for one PSS unit."""

    # (field_suffix, display_label, unit)
    _FIELDS = [
        ("v_x1",   "V X1",       "V"),
        ("v_x2",   "V X2",       "V"),
        ("v_y1",   "V Y1",       "V"),
        ("v_y2",   "V Y2",       "V"),
        ("v_sum",  "V Sum",      "V"),
        ("thresh", "Threshold",  ""),
        ("radius", "Radius",     ""),
        ("x_raw",  "X Raw",      ""),
        ("y_raw",  "Y Raw",      ""),
        ("x_corr", "X Corrected",""),
        ("y_corr", "Y Corrected",""),
        ("az",     "Azimuth",    "deg"),
        ("el",     "Elevation",  "deg"),
    ]

    def __init__(self, pss_idx: int, parent=None) -> None:
        super().__init__(f"PSS {pss_idx}", parent)
        self.pss_idx = pss_idx
        self._labels: dict[str, QLabel] = {}
        self._good_ind = BoolIndicator()
        self._valid_ind = BoolIndicator()
        self._build_ui()

    def _build_ui(self) -> None:
        grid = QGridLayout(self)
        grid.setSpacing(3)
        grid.setContentsMargins(6, 14, 6, 6)

        # Status flags
        grid.addWidget(QLabel("Good:"), 0, 0)
        grid.addWidget(self._good_ind, 0, 1, 1, 2)
        grid.addWidget(QLabel("Valid:"), 0, 3)
        grid.addWidget(self._valid_ind, 0, 4, 1, 2)
        grid.addWidget(_hline(), 1, 0, 1, 6)

        for row, (suffix, display, unit) in enumerate(self._FIELDS, start=2):
            val_lbl = _value_label()
            grid.addWidget(QLabel(f"{display}:"), row, 0, 1, 2)
            grid.addWidget(val_lbl, row, 2, 1, 3)
            grid.addWidget(QLabel(unit), row, 5)
            self._labels[suffix] = val_lbl

        grid.setColumnStretch(2, 1)

    def update_data(self, parsed: dict) -> None:
        idx = self.pss_idx
        for suffix, lbl in self._labels.items():
            val = parsed.get(f"{suffix}_pss_{idx}")
            if val is not None:
                lbl.setText(f"{val:.5f}" if isinstance(val, float) else str(val))
        good = parsed.get(f"good_pss_{idx}")
        valid = parsed.get(f"valid_pss_{idx}")
        if good is not None:
            self._good_ind.set_value(good)
        if valid is not None:
            self._valid_ind.set_value(valid)


# ---------------------------------------------------------------------------
# Overview tab
# ---------------------------------------------------------------------------

class OverviewWidget(QWidget):
    """Best/current pointing, sun position from GPS, array & table status."""

    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self._labels: dict[str, QLabel] = {}
        self._at_target = BoolIndicator()
        self._build_ui()

    def _add_row(self, grid: QGridLayout, row: int, label: str, key: str, unit: str = "") -> None:
        lbl = _value_label()
        self._labels[key] = lbl
        grid.addWidget(QLabel(f"{label}:"), row, 0)
        grid.addWidget(lbl, row, 1)
        grid.addWidget(QLabel(unit), row, 2)

    def _build_ui(self) -> None:
        root = QVBoxLayout(self)
        root.setAlignment(Qt.AlignmentFlag.AlignTop)
        root.setSpacing(10)

        # Pointing
        grp = QGroupBox("Best & Current Pointing")
        g = QGridLayout(grp)
        self._add_row(g, 0, "Best Azimuth",    "best_az",    "deg")
        self._add_row(g, 1, "Best Elevation",   "best_el",    "deg")
        self._add_row(g, 2, "Current Azimuth",  "current_az", "deg")
        self._add_row(g, 3, "Azimuth Offset",   "offset_az",  "deg")
        root.addWidget(grp)

        # Sun from GPS
        grp2 = QGroupBox("Sun Position (GPS-derived)")
        g2 = QGridLayout(grp2)
        self._add_row(g2, 0, "Right Ascension", "ra_sun_gps",  "")
        self._add_row(g2, 1, "Declination",      "dec_sun_gps", "")
        self._add_row(g2, 2, "Azimuth",          "az_sun_gps",  "deg")
        self._add_row(g2, 3, "Elevation",         "el_sun_gps",  "deg")
        self._add_row(g2, 4, "Hour Angle",        "ha_sun_gps",  "")
        root.addWidget(grp2)

        # Array
        grp3 = QGroupBox("Array")
        g3 = QGridLayout(grp3)
        self._add_row(g3, 0, "Tip",  "array_tip",  "")
        self._add_row(g3, 1, "Tilt", "array_tilt", "")
        root.addWidget(grp3)

        # Table
        grp4 = QGroupBox("Rotary Table")
        g4 = QGridLayout(grp4)
        self._add_row(g4, 0, "Position",       "pos_table",           "deg")
        self._add_row(g4, 1, "Cmd Position",    "cmd_position_table",  "deg")
        self._add_row(g4, 2, "Cmd Speed",       "cmd_speed_table",     "deg/s")
        self._add_row(g4, 3, "Set Position",    "set_pos_table",       "deg")
        self._add_row(g4, 4, "Cycle Start",     "cycle_start_table",   "deg")
        self._add_row(g4, 5, "Cycle End",       "cycle_end_table",     "deg")
        self._add_row(g4, 6, "Cycles Left",     "cycles_left_table",   "cycles")
        g4.addWidget(QLabel("At Target:"), 7, 0)
        g4.addWidget(self._at_target, 7, 1)
        root.addWidget(grp4)

        root.addStretch()

    def update_data(self, parsed: dict) -> None:
        for key, lbl in self._labels.items():
            val = parsed.get(key)
            if val is not None:
                lbl.setText(f"{val:.5f}" if isinstance(val, float) else str(val))
        at = parsed.get("at_target_table")
        if at is not None:
            self._at_target.set_value(at)


# ---------------------------------------------------------------------------
# GPS & ADC tab
# ---------------------------------------------------------------------------

class GPSWidget(QWidget):
    """GPS telemetry and ADC boxcar sizes."""

    def __init__(self, parent=None) -> None:
        super().__init__(parent)
        self._labels: dict[str, QLabel] = {}
        self._build_ui()

    def _add_row(self, grid: QGridLayout, row: int, label: str, key: str, unit: str = "") -> None:
        lbl = _value_label()
        self._labels[key] = lbl
        grid.addWidget(QLabel(f"{label}:"), row, 0)
        grid.addWidget(lbl, row, 1)
        grid.addWidget(QLabel(unit), row, 2)

    def _build_ui(self) -> None:
        root = QVBoxLayout(self)
        root.setAlignment(Qt.AlignmentFlag.AlignTop)
        root.setSpacing(10)

        grp = QGroupBox("GPS Status")
        g = QGridLayout(grp)
        self._add_row(g, 0, "Timestamp",  "timestamp_gps", "s")
        self._add_row(g, 1, "Latitude",   "lat_gps",       "")
        self._add_row(g, 2, "Longitude",  "lon_gps",       "")
        self._add_row(g, 3, "Altitude",   "alt_gps",       "")
        self._add_row(g, 4, "Baud Rate",  "baud_gps",      "baud")
        root.addWidget(grp)

        grp2 = QGroupBox("ADC Boxcar Sizes")
        g2 = QGridLayout(grp2)
        for i in range(NUM_PSS):
            key = f"boxcar_size_adc_{i}"
            lbl = _value_label()
            self._labels[key] = lbl
            g2.addWidget(QLabel(f"ADC {i}:"), i, 0)
            g2.addWidget(lbl, i, 1)
        root.addWidget(grp2)

        root.addStretch()

    def update_data(self, parsed: dict) -> None:
        for key, lbl in self._labels.items():
            val = parsed.get(key)
            if val is not None:
                lbl.setText(f"{val:.5f}" if isinstance(val, float) else str(val))


# ---------------------------------------------------------------------------
# Main window
# ---------------------------------------------------------------------------

class MainWindow(QMainWindow):
    def __init__(
        self,
        bind_ip: str = "10.0.0.1",
        bind_port: int = 53335,
        schema_path: Optional[str] = None,
    ) -> None:
        super().__init__()
        uic.loadUi(_UI_FILE, self)  # populates self with all named .ui widgets

        self._schema_path = schema_path
        self._worker: Optional[UDPWorker] = None
        self._packet_count = 0

        # -- Attach Python-built content to the three scroll areas from the .ui --
        self._overview = OverviewWidget()
        self.overviewScroll.setWidget(self._overview)

        pss_container = QWidget()
        pss_grid = QGridLayout(pss_container)
        pss_grid.setSpacing(6)
        self._pss_panels: list[PSSPanel] = []
        for i in range(NUM_PSS):
            panel = PSSPanel(i)
            self._pss_panels.append(panel)
            pss_grid.addWidget(panel, i // 3, i % 3)
        self.pssScroll.setWidget(pss_container)

        self._gps_widget = GPSWidget()
        self.gpsScroll.setWidget(self._gps_widget)

        # Apply any CLI overrides to the defaults already set in the .ui
        self.ipEdit.setText(bind_ip)
        self.portEdit.setText(str(bind_port))

        # Wire signals
        self.connectBtn.clicked.connect(self._toggle_connection)
        self.statusbar.showMessage("Disconnected")

    # ------------------------------------------------------------------
    # Connection management
    # ------------------------------------------------------------------

    def _toggle_connection(self, checked: bool) -> None:
        if checked:
            self._start_receiver()
        else:
            self._stop_receiver()

    def _start_receiver(self) -> None:
        ip = self.ipEdit.text().strip()
        try:
            port = int(self.portEdit.text().strip())
        except ValueError:
            self.statusbar.showMessage("Invalid port number")
            self.connectBtn.setChecked(False)
            return

        self._worker = UDPWorker(ip, port, self._schema_path)
        self._worker.packet_received.connect(self._on_packet)
        self._worker.status_changed.connect(self.statusbar.showMessage)
        self._worker.error_occurred.connect(self._on_error)
        self._worker.start()

        self.connectBtn.setText("Disconnect")
        self.ipEdit.setEnabled(False)
        self.portEdit.setEnabled(False)

    def _stop_receiver(self) -> None:
        if self._worker is not None:
            self._worker.stop()
            self._worker.wait(3000)
            self._worker = None
        self.connectBtn.setText("Connect")
        self.connectBtn.setChecked(False)
        self.ipEdit.setEnabled(True)
        self.portEdit.setEnabled(True)
        self.statusbar.showMessage("Disconnected")

    # ------------------------------------------------------------------
    # Data update
    # ------------------------------------------------------------------

    def _on_packet(self, parsed: dict) -> None:
        self._packet_count += 1
        ts = datetime.datetime.now().strftime("%H:%M:%S.%f")[:-3]
        self.packetLabel.setText(f"Packets: {self._packet_count}")
        self.timestampLabel.setText(f"Last: {ts}")

        self._overview.update_data(parsed)
        for panel in self._pss_panels:
            panel.update_data(parsed)
        self._gps_widget.update_data(parsed)

    def _on_error(self, msg: str) -> None:
        self.statusbar.showMessage(f"Error: {msg}")
        self._stop_receiver()

    def closeEvent(self, event) -> None:  # noqa: N802
        self._stop_receiver()
        super().closeEvent(event)


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def _parse_args() -> argparse.Namespace:
    p = argparse.ArgumentParser(description="Sun Sensor PyQt6 telemetry GUI")
    p.add_argument("--bind", "-b", default="10.0.0.1", help="IP to bind (default: 10.0.0.1)")
    p.add_argument("--port", "-p", type=int, default=53335, help="Port to bind (default: 53335)")
    p.add_argument("--schema", "-s", default=None, help="Path to table_parsed.json schema")
    return p.parse_args()


if __name__ == "__main__":
    args = _parse_args()
    app = QApplication(sys.argv)
    app.setStyle("Fusion")
    win = MainWindow(args.bind, args.port, args.schema)
    win.show()
    sys.exit(app.exec())
