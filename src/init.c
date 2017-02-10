 /* @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "pid/strategies/xdrive.h"
#include "pid/pid.c"

/*
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

XDriveStrategy driveStrategy;

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */
void initialize() {

  printf("Begin initalize()");

  setTeamName("3796B");

  imeInitializeAll();

  // Initalize the drive strategy
  driveStrategy.wheelDiameter = 4;
  driveStrategy.gearRatio = 1;
  driveStrategy.motorType = TORQUE;

  // The diameter of the turn circle
  driveStrategy.turnDiameter = 15;

  PIDConfiguration configX;
  PIDConfiguration configY;
  PIDConfiguration configR;

  configurePID(&configX, 0, 0, 0);
  configurePID(&configY, 0, 0, 0);
  configurePID(&configR, 0, 0, 0);


  driveStrategy.configX = configX;
  driveStrategy.configY = configY;
  driveStrategy.configR = configR;

  IME imeLeft;
  imeLeft.address = 0;
  IME imeRight;
  imeRight.address = 1;

  driveStrategy.imeLeft = imeLeft;
  driveStrategy.imeRight = imeRight;


}
