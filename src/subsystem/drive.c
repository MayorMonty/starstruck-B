/**
 * drive.c
 *
 *  Created On: Jan. 26 2017
 *  Author: Brendan McGuire
 *
 */

#include "subsystem/drive.h"
#include "main.h"
#include <math.h>

void DriveHeading(double heading, double speed, int rotation) {
	int X = cos(heading) * speed * 127,
		  Y = sin(heading) * speed * 127,
		  R = rotation;
	DriveDirect(X, Y, R);
}


void DriveDirect(int X, int Y, int R) {

  motorSet(DriveFrontLeft,  +Y + X + R);
  motorSet(DriveBackLeft,   +Y - X + R);
  motorSet(DriveFrontRight, -Y + X + R);
  motorSet(DriveBackRight,  -Y - X + R);

}
