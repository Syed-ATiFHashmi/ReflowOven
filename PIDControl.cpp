#include "PIDControl.h"
#include <Arduino.h>

static float Kp = 2.0f;
static float Ki = 0.03f;
static float Kd = 1.2f;
static float integral = 0.0f;
static float previousError = 0.0f;
static float dtSeconds = 0.25f;

void beginPID(float kp, float ki, float kd, float dtSecondsValue) {
  Kp = kp;
  Ki = ki;
  Kd = kd;
  dtSeconds = dtSecondsValue;
  integral = 0.0f;
  previousError = 0.0f;
}

int computePID(float setpoint, float actual) {
  float error = setpoint - actual;
  integral += error * dtSeconds;
  float derivative = (error - previousError) / dtSeconds;
  float output = Kp * error + Ki * integral + Kd * derivative;
  previousError = error;

  int pwmValue = (int)round(output);
  pwmValue = constrain(pwmValue, 0, 1023);
  return pwmValue;
}

void resetPID() {
  integral = 0.0f;
  previousError = 0.0f;
}
