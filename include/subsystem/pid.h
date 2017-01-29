/*
 * pid.h
 *
 *  Created on: January 28, 2017
 *      Author: Brendan McGuire
 *
 *  This is a generalized PID implementation, which takes a pregiven current value and caclulates motor values. This specifically modularizes sensor information for implmeneting PIDs on places where you have to manipulate the sensor input, for example when adding a PID to an X Drive, you must manipulate the IMEs or Encoder values to get the actual distance traveled in one direction
 */

#ifndef INCLUDE_PID_H_
#define INCLUDE_PID_H_

typedef struct {

  /** PID Variables **/
  int P;
  int I;
  int D;

  /** Long term, non configured, calculated variables **/
  int lastError;
  int deltaError;

} PIDConfiguration;


/**
 * Configures a PID
 * @method configurePID
 * @param  pid          The PID to configure
 * @param  P            The P value
 * @param  I            The I value
 * @param  D            The D value
 * @return              The PID Configured
 */
PIDConfiguration configurePID(PIDConfiguration *pid, float P, float I, float D);

/**
 * Calculates the correct motor value, based on a target
 * @method calculatePID
 * @param  pid          The pid configuration
 * @param  target       The target you wish to achieve
 * @param  value        The precalculated value from a sensor, or combination of sensors
 * @return              The output value
 */
int calculatePID(PIDConfiguration *pid, float target, float value);

/**
 * Resets the PID back to original configuration, for when you have a new "target"
 * @method resetPID
 * @param  pid      The PID Configuration to reset
 * @return          The aforementioned pid config that was reset
 */
PIDConfiguration resetPID(PIDConfiguration *pid);

#endif /* INCLUDE_PID_H_ */
