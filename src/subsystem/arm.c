/*
 @file: arm.c
 *
 *  Created on: January 27, 2017
 *      Author: Brendan McGuire
 *
 *  Implementor for arm.h
 */

#include "subsystem/arm.h"

int armSpeedMoveUp = 60;
int armSpeedMoveDown = 40;

int armSpeedFling = 100;

void moveArm(int direction, bool fling) {
  if (direction == -1) {
    direction *= armSpeedMoveDown;
  } else {
    if (fling) {
      direction *= armSpeedFling;
    } else {
      direction *= armSpeedMoveUp;
    }
  }

  motorSet(ArmOuterLeft, direction);
  motorSet(ArmInnerLeft, -direction);
  motorSet(ArmInnerRight, -direction);
  motorSet(ArmOuterRight, direction);

}
