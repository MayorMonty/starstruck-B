/**
 * drive.c
 *
 *  Created On: Jan. 26 2017
 *  Author: Brendan McGuire
 *
 */

#include "subsystem/drive.h"
#include "main.h"


void DriveHeading(double heading, double speed, int rotation) {
	int X = cos(heading) * speed * maxMotorSpeed,
		  Y = sin(heading) * speed * maxMotorSpeed,
		  R = rotation;
	DriveDirect(X, Y, R);
}


void DriveDirect(int X, int Y, int R) {

  motorSet(DriveFrontLeft,  +Y + X + R);
  motorSet(DriveBackLeft,   +Y - X + R);
  motorSet(DriveFrontRight, -Y + X + R);
  motorSet(DriveBackRight,  -Y - X + R);

}
