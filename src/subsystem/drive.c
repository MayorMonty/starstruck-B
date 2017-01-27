/**
 * drive.c
 *
 *  Created On: Jan. 26 2017
 *  Author: Brendan McGuire
 *
 */

#include "subsystem/drive.h"
#include "main.h"


void Drive(double heading, double speed, int rotation) {




}


void DriveDirect(int X, int Y, int R) {

  motorSet(DriveFrontLeft,  +Y + X + R);
  motorSet(DriveBackLeft,   +Y - X + R);
  motorSet(DriveFrontRight, -Y + X + R);
  motorSet(DriveBackRight,  -Y - X + R);

}
