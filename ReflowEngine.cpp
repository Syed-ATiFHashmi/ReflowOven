#include "ReflowEngine.h"
#include "Temperature.h"
#include "Heater.h"
#include "PIDControl.h"
#include "Profiles.h"
#include <Arduino.h>

static ReflowState engineState = IDLE;
static const ReflowProfile* activeProfile = 0;
static int activeSegmentIndex = 0;
static unsigned long segmentStartMillis = 0;
static float currentTarget = 0.0f;
static int currentPower = 0;
static unsigned long reflowStartMillis = 0;

void beginEngine() {
  engineState = IDLE;
  activeProfile = &DEFAULT_PROFILE;
  activeSegmentIndex = 0;
  segmentStartMillis = 0;
  currentTarget = 0.0f;
  currentPower = 0;
  reflowStartMillis = 0;
  beginPID(2.0f, 0.03f, 1.2f, 0.25f);
}

bool startReflow() {
  if (engineState != IDLE && engineState != COMPLETE && engineState != ABORT) {
    return false;
  }

  engineState = PREHEAT;
  activeSegmentIndex = 0;
  segmentStartMillis = millis();
  reflowStartMillis = segmentStartMillis;
  currentTarget = activeProfile->segments[0].targetCelsius;
  resetPID();
  return true;
}

void stopReflow() {
  engineState = ABORT;
  currentPower = 0;
  setHeaterPower(0);
  setFan(false);
}

ReflowState getReflowState() {
  return engineState;
}

const char* getReflowStateName() {
  switch (engineState) {
    case IDLE: return "IDLE";
    case PREHEAT: return "PREHEAT";
    case SOAK: return "SOAK";
    case REFLOW: return "REFLOW";
    case COOL: return "COOL";
    case COMPLETE: return "COMPLETE";
    case ABORT: return "ABORT";
    default: return "UNKNOWN";
  }
}

float getReflowTarget() {
  return currentTarget;
}

int getReflowPower() {
  return currentPower;
}

unsigned long getReflowElapsed() {
  if (reflowStartMillis == 0) {
    return 0;
  }
  return millis() - reflowStartMillis;
}

static void advanceSegment() {
  if (activeSegmentIndex + 1 < activeProfile->segmentCount) {
    activeSegmentIndex++;
    segmentStartMillis = millis();
    currentTarget = activeProfile->segments[activeSegmentIndex].targetCelsius;
  } else {
    engineState = COOL;
    segmentStartMillis = millis();
    currentTarget = 0.0f;
  }
}

static void updateState() {
  if (engineState == IDLE || engineState == COMPLETE || engineState == ABORT) {
    return;
  }

  unsigned long now = millis();
  unsigned long duration = activeProfile->segments[activeSegmentIndex].durationMs;
  if (now - segmentStartMillis >= duration) {
    advanceSegment();
    if (engineState == COOL) {
      return;
    }
  }

  if (engineState == PREHEAT && activeSegmentIndex == 1) {
    engineState = SOAK;
  }
  if (engineState == SOAK && activeSegmentIndex == 2) {
    engineState = REFLOW;
  }
}

void updateEngine() {
  updateTemperature();
  updateState();

  float actualTemp = getTemperature();
  if (engineState == PREHEAT || engineState == SOAK || engineState == REFLOW) {
    currentPower = computePID(currentTarget, actualTemp);
    setHeaterPower(currentPower);
    setFan(false);
  } else if (engineState == COOL) {
    currentPower = 0;
    setHeaterPower(0);
    setFan(true);
    if (actualTemp < 60.0f) {
      engineState = COMPLETE;
      setFan(false);
    }
  } else {
    currentPower = 0;
    setHeaterPower(0);
    setFan(false);
  }
}
