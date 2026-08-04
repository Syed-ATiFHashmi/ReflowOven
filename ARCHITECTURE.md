# ESP8266 Reflow Oven Controller - Architecture

## Firmware

```
ReflowOven.ino
 ├── Temperature
 ├── ProfileManager
 ├── ReflowEngine
 ├── PID
 ├── Heater
 ├── WebServer
 └── GraphBuffer
```

## Data Flow

```
MAX6675
   ↓
Temperature
   ↓
Reflow Engine
   ↓
Target Temperature
   ↓
PID
   ↓
Heater Controller
   ├── Heater 1
   ├── Heater 2
   └── Fan
```

## Web UI

LittleFS serves:
- index.html
- style.css
- app.js
- profiles/*.json

REST API:
- /api/status
- /api/start
- /api/stop
- /api/reset
- /api/profile
- /api/history

Future:
- WebSocket live updates
- Profile editor
- CSV export
- OTA
