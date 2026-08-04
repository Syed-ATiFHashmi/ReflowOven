#pragma once

void beginPID(float kp, float ki, float kd, float dtSeconds);
int computePID(float setpoint, float actual);
void resetPID();
