/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "pid/pid.h"
#include "utility/drive.h"
#include "utility/motors.h"
#include "utility/vector.h"
#include "utility/arm.h"
#include "utility/units.h"
#include <API.h>

#define degreesToRadians(angleDegrees) (angleDegrees * PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / PI)

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

PIDConfiguration arm;
Encoder leftEncoder;
Encoder rightEncoder;


void autonomous() {

  for (int i = 0; i < 3; i++) {

    if (i != 0) {
      moveClaw(127);
      delay(800);
      DriveDirect(0, -127, 0);
    } else {
      moveClaw(127);
      DriveDirect(0, -127, 0);
    }

    delay(1000);
    moveClaw(0.75);

    delay(1500);

    DriveDirect(0, 0, 0);
    moveArm(1, 0);

    delay(1300);

    moveArm(-1, 0);
    moveClaw(-127);

    delay(300);

    DriveDirect(0, 127, 0);
    moveClaw(0);

    delay(500);

    moveArm(0, 0);
    moveClaw(-127);

    delay(300);
    moveClaw(0);
    delay(1000);
    DriveDirect(0, 0, 0);
    delay(500);

  }



    // DriveDirect(0, -80, 0);
    // delay(500);
    // moveArm(1, false);
    // delay(1400);
    // moveArm(0, false);
    // delay(1600);
    // DriveDirect(0, 0, 0);
    // Drive(0, -80, 0);
    // delay(1800);
    // moveArm(1, false);
    // delay(1000);
    // Drive(0, 127, 0);
    // moveArm(-1, false);
    // delay(1000);
    // moveArm(0, false);
    // delay(1800);
    // for (int i = 0; i < 3; i++) {
    //   Drive(0, -127, 0);
    //   delay(1800);
    //   moveArm(1, true);
    //   delay(1000);
    //   Drive(0, -127, 0);
    //   moveArm(-1, false);
    // }

}
