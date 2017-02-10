/*
 * @file xdrive.h
 * @created January 26, 2017
 * @author Brendan McGuire
 * @brief This PID Strategy is for x drives. There are three PIDs for X-Drives: one for x, one for y, and one for rotation
 */

#include <utility/vector.h>
#include <API.h>
#include <pid/pid.h>
#include <math.h>
#include "utility/sensors/ime.h"
#include "utility/units.h"

#ifndef INCLUDE_XDRIVE_H_
#define INCLUDE_XDRIVE_H_

#define oneOverRootTwo 1 / sqrt(2);

typedef enum {
  INTEGRATED,
  QUAD
} encoderType;


typedef struct XDriveStrategy {

  // Any multipliers to worry about when converting inches => ticks
  double wheelDiameter;
  double gearRatio;
  motorType motorType;

  // When calculating rotation with just IMEs, we need to know the turning diameter
  double turnDiameter;

  // PID Configurations for each of the three PIDs
  PIDConfiguration configX;
  PIDConfiguration configY;
  PIDConfiguration configR;

  // Sensors
  Gyro gyroscope;

  // @TODO: Add 4 IME support
  IME imeLeft;
  IME imeRight;

} XDriveStrategy;

extern XDriveStrategy driveStrategy;

/**
 * Just rotate the drive. Note: starts a task to control x drive, and stops it. THIS FUNCTION IS ASYNCHRONOUS
 * @method xdriveTurn
 * @param  strategy   The X-Drive Strategy Configuration to use
 * @param  heading    The number of radians to rotate
 * @param  callback   The function to call upon completion, which must accept one argument, elapsed, the number of milliseconds it took to complete the action
 */
TaskHandle xdriveTurn(XDriveStrategy *strategy, double heading, void (*callback)(int elapsed));

/**
 * Just translate the drive. THIS FUNCTION IS ASYNCHRONOUS
 * @method xdriveTurn
 * @param  strategy   The X-Drive Strategy Configuration to use
 * @param  direction  A polar vector representing the direction and mangitude to travel, with the radius defined in inches
 * @param  callback   The function to call upon completion, which must accept one argument, elapsed, the number of milliseconds it took to complete the action
 */
TaskHandle xdriveMove(XDriveStrategy *strategy, PolarVector direction, void (*callback)(int elapsed));


/** PID Control Tasks **/
void StrategyTaskXDriveRotate();
void StrategyTaskXDriveTranslate();

#endif /* INCLUDE_XDRIVE_H_ */
