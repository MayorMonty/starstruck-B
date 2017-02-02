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

#ifndef INCLUDE_XDRIVE_H_
#define INCLUDE_XDRIVE_H_

#define oneOverRootTwo 1 / sqrt(2);

typedef enum {
  TORQUE,
  HIGHSPEED,
  TURBO
} motorType;

typedef enum {
  INTEGRATED,
  QUAD
} encoderType;

typedef struct {
  // The address of the IME, from 0, the IME plugged into the cortex, up the daisy chain
  char address;

  // Value Storage
  int value;
  int lastValue;

} IME;

/**
 * Update an IME Struct to the current value, and update the last value
 * @method updateIME
 * @param  ime       The IME Struct
 * @return           Whether or not the operation was successful
 */
bool updateIME(IME *ime);


typedef struct {

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

/**
 * Just rotate the drive. Note: starts a task to control x drive, and stops it. THIS FUNCTION IS ASYNCHRONOUS
 * @method xdriveTurn
 * @param  strategy   The X-Drive Strategy Configuration to use
 * @param  heading    The number of radians to rotate
 * @param  callback   The function to call upon completion, which must accept one argument, elapsed, the number of milliseconds it took to complete the action
 */
void xdriveTurn(XDriveStrategy *strategy, double heading, void (*callback)(int elapsed));

/**
 * Just translate the drive. THIS FUNCTION IS ASYNCHRONOUS
 * @method xdriveTurn
 * @param  strategy   The X-Drive Strategy Configuration to use
 * @param  direction  A polar vector representing the direction and mangitude to travel, with the radius defined in inches
 * @param  callback   The function to call upon completion, which must accept one argument, elapsed, the number of milliseconds it took to complete the action
 */
void xdriveMove(XDriveStrategy *strategy, PolarVector direction, void (*callback)(int elapsed));


/** CONVERSION FUNCTIONS **/

/**
 * Convert ticks to rotations
 * @method ticksToRotations
 * @param  ticks           Ticks
 * @param  motor           The motor type
 * @return                 Rotations
 */
double ticksToRotations(int ticks, motorType motor);

/**
 * Converts rotations to ticks
 * @method rotationsToTicks
 * @param  rotations        Rotations
 * @param  motor            Motor Type
 * @return                  Ticks
 */
int rotationsToTicks(double rotations, motorType motor);

/**
 * Convert ticks to inches
 * @method ticksToInches
 * @param  ticks         Ticks
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Inches
 */
double ticksToInches(int ticks, double wheelDiameter, motorType motor);

/**
 * Convert inches to ticks
 * @method inchesToTicks
 * @param  inches        Inches
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Ticks
 */
int inchesToTicks(double inches, double wheelDiameter, motorType motor);


/** PID Control Tasks **/
void StrategyTaskXDriveRotate();
void StrategyTaskXDriveTranslate();

#endif /* INCLUDE_XDRIVE_H_ */
