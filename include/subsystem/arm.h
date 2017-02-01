/*
 * arm.h
 *
 *  Created on: January 27, 2017
 *      Author: Brendan McGuire
 *
 *  This header file defines all functions which are related to the arm, right now just direct arm control
 */

#ifndef INCLUDE_ARM_H_
#define INCLUDE_ARM_H_

/**
 * @type armDirection
 * Possible Settings:
 *   UP      =  1
 *   DOWN    = -1
 *   NEUTRAL =  0
 */



/**
 * Moves the arm a certain direction in the preset speed (look at the define preprocessor instruction)
 * @method moveArm
 * @param direction The direction to move it in, see ArmDirection
 * @param fling     Whether you want to fling
 */
void moveArm(int direction, bool fling);

#endif /* INCLUDE_ARM_H_ */
