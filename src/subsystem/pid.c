/*
 @file: pid.c
 *
 *  Created on: January 28, 2017
 *      Author: Brendan McGuire
 *
 * This is a generalized PID implementation, which takes a pregiven current value and caclulates motor values. This specifically
 * modularizes sensor information for implmeneting PIDs on places where you have to manipulate the sensor input, for example when
 * adding a PID to an X Drive, you must manipulate the IMEs or Encoder values to get the actual distance traveled in one direction.
 *
 * This implementation does not include any calculations of gear ratios, wheel sizes, or any other factor purely from transforming
 * the current value to an output. This is because different PIDs will want to do this differently. For example, a PID to maintain
 * a flywheel will have different objectives than an X Drive's instruction to move a certain direction at a specific heading. This
 * is where PID Strategies come in. PID Strategies are systems of functions that build upon this base module in order to target
 * more specific applications of the PID System. For example, one of the strategies implemented is a maintain strategy, to maintain
 * the delta value of a sensor. PID Strategies are located under the strategies/ subdirectory of include and src.
 */

#include "main.h"
#include "subsystem/pid.h"


PIDConfiguration resetPID(PIDConfiguration *pid) {
  pid -> lastError = 0;
  pid -> totalError = 0;

  return pid;
}

PIDConfiguration configurePID(PIDConfiguration *pid, float P, float I, float D) {

  pid -> P = P;
  pid -> I = I;
  pid -> D = D

  return pid;
}

PIDConfiguration calculatePID(PIDConfiguration *pid, float target, float value) {

  // Put the PID Configuration into local variables for convience
  float Kp, Ki, Kd =
    pid -> P, pid -> I, pid -> D;

  // The amount we are from our target
  float error = target - value;

  // The amount of wrong we are from our target, in general
  pid -> deltaError += error;

  float output = (Kp * error) +
         (Ki * pid -> deltaError) +
         (Kd * pid -> lastError);

  // The amount of wrong were just were
  pid -> lastError = error;

  return (int) output;

}
