# ESP8266 Reflow Oven Controller - Implementation Plan

## Goal
Build a modular ESP8266-based reflow oven controller with:
- MAX6675 thermocouple
- Dual SSR heater outputs
- Cooling fan control
- LittleFS web UI
- JSON reflow profiles
- PID temperature control
- OTA updates
- Logging

## Repository Layout
```
src/
include/
lib/
data/
docs/
test/
```

## Development Phases
1. Project foundation
2. Temperature module
3. Web UI
4. Profile manager
5. Reflow engine
6. PID control
7. Safety
8. OTA & logging

## Modules
- Temperature
- Heater
- Fan
- Profile Manager
- Reflow Engine
- PID
- Web Server
- Graph Buffer
- Logger

## Safety
- Sensor fault
- Over-temperature
- Timeout
- Emergency stop
- Heater watchdog

## Coding Rules
- Non-blocking
- Modular
- Documented
- JSON configuration
- Browser assets stored in LittleFS
