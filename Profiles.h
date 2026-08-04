#pragma once

struct ProfileSegment {
  unsigned long durationMs;
  float targetCelsius;
};

struct ReflowProfile {
  const char* name;
  const ProfileSegment* segments;
  int segmentCount;
};

extern const ReflowProfile DEFAULT_PROFILE;
