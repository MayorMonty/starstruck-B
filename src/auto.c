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

void autonomous() {


  // near/far - relative to the hanging bar
  // 127 for red far, -127 for red near, 127 for blue near, -127 for blue far
  int moveTowardsCenter = 127;


  // for (int i = 0; i < 2; i++) {
  //   moveClaw(127);
  //   DriveDirect(0, -127, 0);
  //   delay(800);
  //   moveClaw(-127);
  //   DriveDirect(0, 0, 0);
  //   delay(1000);
  //   DriveDirect(0, -127, 0);
  //   delay(1300);
  //   moveArm(1, 0);
  //   delay(200);
  //   DriveDirect(0, 0, 0);
  //   delay(500);
  //   DriveDirect(0, 127, 0);
  //   delay(2500);
  // }

  // // Programming Skills
  // for (int i = 0; i < 2; i++) {
  //
  //   if (i != 0) {
  //     moveClaw(127);
  //     delay(800);
  //     DriveDirect(0, -127, 0);
  //   } else {
  //     moveClaw(127);
  //     DriveDirect(0, -127, 0);
  //   }
  //
  //   delay(1000);
  //   moveClaw(0.75);
  //
  //   delay(1500);
  //
  //   DriveDirect(0, 0, 0);
  //   moveArm(1, 0);
  //
  //   delay(1300);
  //
  //   moveArm(-1, 0);
  //   moveClaw(-127);
  //
  //   delay(300);
  //
  //   DriveDirect(0, 127, 0);
  //   moveClaw(0);
  //
  //   delay(500);
  //
  //   moveArm(0, 0);
  //   moveClaw(-127);
  //
  //   delay(300);
  //   moveClaw(0);
  //   delay(1000);
  //   DriveDirect(0, 0, 0);
  //   delay(500);
  //
  // }


    // Autonomous

    DriveDirect(0, -127, 0);
    delay(2500);
    // Stop moving the claw and drive, and move the Arm
    DriveDirect(0, 0, 0);
    moveArm(1, 0);
    moveClaw(127);
    delay(600);
    moveClaw(0);
    delay(1000);
    moveClaw(-127);
    moveArm(0, 0);
    delay(400);
    moveClaw(0);
    moveArm(-1, 0);
    delay(600);
    moveArm(0, 0);
    DriveDirect(0, 80, 0);
    delay(300);
    DriveDirect(0, 0, 0);
    delay(400);
    // // Section II: Translate the Drive until, we've reached the center
    // DriveDirect(moveTowardsCenter, 0, 0);
    // delay(1500);
    // DriveDirect(0, 0, 0);
    // delay(300);
    // // Section III: Pick up the cube and launch it
    // DriveDirect(0, 127, 0);
    // delay(600);
    // DriveDirect(0, 0, 0);
    // moveClaw(127);
    // delay(800);
    // DriveDirect(0, -127, 0);
    // moveClaw(127);
    // delay(800);
    // moveArm(1.27, 0);
    // delay(2000);
    // moveClaw(-127);
    // DriveDirect(0, 0, 0);
    // delay(600);
    // moveClaw(0);
}
