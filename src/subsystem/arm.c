/*
 * arm.c
 *
 *  Created on: January 27, 2017
 *      Author: Brendan McGuire
 *
 *  Implementor for arm.h
 */

#include "subsystem/arm.h"

int armSpeed = 50;

void moveArm(int direction) {

  direction *= armSpeed;

  motorSet(ArmOuterLeft, direction);
  motorSet(ArmInnerLeft, -direction);
  motorSet(ArmInnerRight, -direction);
  motorSet(ArmOuterRight, direction);

}

int setArmSpeed(int speed) {
  armSpeed = speed;
  return speed;
}
