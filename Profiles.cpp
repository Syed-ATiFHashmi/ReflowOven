#include "Profiles.h"

static const ProfileSegment defaultSegments[] = {
  {120000, 150.0f}, // preheat to 150°C in 2 minutes
  {90000, 180.0f},  // soak at 180°C for 90 seconds
  {60000, 220.0f},  // reflow to 220°C for 60 seconds
};

const ReflowProfile DEFAULT_PROFILE = {
  "Default",
  defaultSegments,
  sizeof(defaultSegments) / sizeof(defaultSegments[0])
};
