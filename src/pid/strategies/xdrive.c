/*
 * @file xdrive.c
 * @created January 26, 2017
 * @author Brendan McGuire
 * @brief This PID Strategy is for x drives. There are three PIDs for X-Drives: one for x, one for y, and one for rotation
 */

#include "pid/strategies/xdrive.h"
#include <math.h>
#include "utility/drive.h"
#include "utility/vector.h"

// Update Functions
bool updateIME(IME *ime) {

  ime->lastValue = ime->value;
  return imeGet(ime->address, &ime->value);

}

// Convertions
double ticksToRotations(int ticks, motorType motor) {
  switch (motor) {
    case TORQUE:
      return (double) ticks / 627.2;
    case HIGHSPEED:
      return (double) ticks / 392;
    case TURBO:
      return (double) ticks / 261.333;
  }
  return 0;
}

int rotationsToTicks(double rotations, motorType motor) {
  switch (motor) {
    case TORQUE:
      return rotations * 627.2;
    case HIGHSPEED:
      return rotations * 392;
    case TURBO:
      return rotations * 261.333;
  }
  return 0;
}

double ticksToInches(int ticks, double wheelDiameter, motorType motor) {
    return ticksToRotations(ticks, motor) / wheelDiameter / M_PI;
}

int inchesToTicks(double ticks, double wheelDiameter, motorType motor) {
    return rotationsToTicks(ticks, motor) * wheelDiameter * M_PI;
}

// TASKS
void StrategyTaskXDriveRotate(XDriveStrategy *strategy, double heading, void (*callback)(int elapsed)) {
  // Start Time
  int start = millis();

  // Hold the configuration in a variable
  PIDConfiguration rotate = strategy->configR;
  double turnCircumfrence = strategy->turnDiameter * M_PI;
  // Ticks to begin a complete rotation
  int turnTicks = inchesToTicks(turnCircumfrence, strategy->motorType, strategy->wheelDiameter);
  int target = (int) turnTicks * 2 * M_PI / heading;
  while(!rotate.complete) {

    updateIME(&strategy->imeLeft);
    DriveDirect(0, 0,
      calculatePID(&rotate, target, strategy->imeLeft.value)
    );

  };
  // We're done, call the callback
  callback(
    millis() - start
  );
}

void StrategyTaskXDriveTranslate(XDriveStrategy *strategy, PolarVector direction, void (*callback)(int elapsed)) {

  // Start Time
  int start = millis();

  // The measured value from the tick value
  int ticksX, ticksY;

  IME imeLeft = strategy->imeLeft;
  IME imeRight = strategy->imeRight;

  int outX, outY;

  PIDConfiguration X = strategy->configX;
  PIDConfiguration Y = strategy->configY;

  CartesianVector target = PolarToCartesian(direction);

  while(true) {

    int leftValue  = imeLeft.value * oneOverRootTwo;
    int rightValue = imeRight.value * oneOverRootTwo;

    // One over root two is the shortcut value to get the x
    ticksY = leftValue + rightValue;
    ticksX = -leftValue + rightValue;

    outX = calculatePID(&X, target.x, ticksX);
    outY = calculatePID(&Y, target.y, ticksY);

    DriveDirect(outX, outY, 0);

  };
  callback(
    millis() - start
  );

}

void xdriveTurn(XDriveStrategy *strategy, double heading, void (*callback)(int elapsed)) {
  print("Begin PID Turn");
}
