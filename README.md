# Network Scanner

A beginner ESP32-S3 project built with PlatformIO and the Arduino framework. The project scans for nearby Wi-Fi access points and prints the results to the serial monitor.

This scanner does not connect to any network, scan LAN devices, send probes to hosts, or attempt authentication. It only reports Wi-Fi access points visible to the ESP32.

## Hardware

- Board: ESP32-S3 DevKitC-1 N32R16V
- Flash: 32 MB
- PSRAM: 16 MB octal PSRAM
- Framework: Arduino
- Build system: PlatformIO
- Serial monitor speed: 115200 baud

The project is configured in `platformio.ini` under:

```ini
[env:esp32-s3-devkitc-1-n32r16v]
```

## Current Features

- Starts an asynchronous Wi-Fi scan at boot.
- Allows rescanning from the serial monitor with `r` or `R`.
- Ignores rescan requests while a scan is already running.
- Includes hidden networks in scan results.
- Prints hidden SSIDs as `<hidden>`.
- Shows RSSI, signal quality, channel, band label, security mode, BSSID, and SSID.
- Releases scan result memory after each completed scan.

## Example Output

```text
Board starting up...
Starting WiFi scan...
Scan started successfully.
Scan complete.
Number of networks found: 3
#  RSSI   Quality   CH  BAND     SECURITY       BSSID              SSID
-- ----- ---------- --- ----     -------------- ------------------ ----------------
1   -42   Excellent  6   2.4 GHz  WPA2-PSK       AA:BB:CC:DD:EE:FF HomeNetwork
2   -67   Fair       11  2.4 GHz  Open           11:22:33:44:55:66 GuestWiFi
3   -81   Very Weak  1   2.4 GHz  WPA2/WPA3-PSK  22:33:44:55:66:77 <hidden>
Scan results released
Press r to scan again
```

## Build

If `pio` is available on your PATH:

```powershell
pio run -e esp32-s3-devkitc-1-n32r16v
```

If PlatformIO is installed but `pio` is not on your PATH:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run -e esp32-s3-devkitc-1-n32r16v
```

## Upload

```powershell
pio run -e esp32-s3-devkitc-1-n32r16v -t upload
```

Or with the full PlatformIO path:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" run -e esp32-s3-devkitc-1-n32r16v -t upload
```

## Serial Monitor

```powershell
pio device monitor -b 115200
```

Or with the full PlatformIO path:

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\pio.exe" device monitor -b 115200
```

In the serial monitor:

- Type `r` and press Enter to scan again.
- Type `R` and press Enter to scan again.
- If a scan is already running, the board prints a wait message.

## Signal Quality Labels

RSSI is reported in dBm. Higher values are stronger, so `-40` is stronger than `-80`.

| RSSI range | Label     |
| ---------- | --------- |
| `>= -50`   | Excellent |
| `>= -60`   | Good      |
| `>= -70`   | Fair      |
| `>= -80`   | Weak      |
| `< -80`    | Very Weak |

## Notes

- ESP32-S3 Wi-Fi scans nearby access points. It is not a full network-mapping tool.
- The board is configured for station mode with `WiFi.mode(WIFI_STA)`.
- The project calls `WiFi.disconnect()` so it does not stay connected to a saved network.
- Scan results must be read before calling `WiFi.scanDelete()`.
- The ESP32-S3 is a 2.4 GHz Wi-Fi device. The band-label helper includes fallback labels, but normal results on this board should be 2.4 GHz channels.

## Project Structure

```text
network-scanner/
├── platformio.ini
├── src/
│   └── main.cpp
├── include/
├── lib/
└── test/
```
