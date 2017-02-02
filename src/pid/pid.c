/*
 * @file: pid.c
 * @created January 28, 2017
 * @author Brendan McGuire
 *
 * This is a generalized PID implementation, which takes a pregiven current value and caclulates motor values. This
 * specifically modularizes sensor information for implmeneting PIDs on places where you have to manipulate the sensor input,
 * for example when adding a PID to an X Drive, you must manipulate the IMEs or Encoder values to get the actual distance
 * traveled in one direction.
 *
 * This implementation does not include any calculations of gear ratios, wheel sizes, or any other factor purely from
 * transforming the current value to an output. This is because different PIDs will want to do this differently. For example,
 * a PID to maintain a flywheel will have different objectives than an X Drive's instruction to move a certain direction at
 * a specific heading. This is where PID Strategies come in. PID Strategies are systems of functions that build upon this
 * base module in order to target more specific applications of the PID System. For example, one of the strategies
 * implemented is a maintain strategy, to maintain the delta value of a sensor. PID Strategies are located under the
 * strategies/ subdirectory of include and src.
 */

#include <main.h>
#include "pid/pid.h"

void resetPID(PIDConfiguration *pid) {
  pid -> lastError = 0;
  pid -> totalError = 0;
  pid -> complete = false;
}

void configurePID(PIDConfiguration *pid, double P, double I, double D) {

  resetPID(&pid);

  pid -> P = P;
  pid -> I = I;
  pid -> D = D;
}

int calculatePID(PIDConfiguration *pid, int target, double value) {

  // Put the PID Configuration into local variables for convience
  double Kp = pid -> P;
  double Ki = pid -> I;
  double Kd = pid -> D;

  // The amount we are from our target
  double error = target - value;

  // The amount of wrong we are from our target, in general
  pid -> totalError += error;

  double output = (Kp * error) +
         (Ki * pid -> totalError) +
         (Kd * pid -> lastError);

  // The amount of wrong were just were
  pid -> lastError = error;

  if (error == 0) {
    pid->complete = true;
  } else {
    pid->complete = false;
  }

  return (int) output;

}
