#pragma once
#include "Types.h"

void beginEngine();
void updateEngine();

bool startReflow();
void stopReflow();
ReflowState getReflowState();
const char* getReflowStateName();
float getReflowTarget();
int getReflowPower();
unsigned long getReflowElapsed();
