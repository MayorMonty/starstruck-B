/*
 * @file sensor.h
 * @created Febuary 2, 2017
 * @author Brendan McGuire
 * @brief This abstraction represents a sensor
 */

#include "utility/sensor.h"


bool updateSensor(Sensor *sensor) {
  // Handle the sensor differently for different types
  switch (sensor->type) {
    case IME:
    default:
      return imeGet(sensor->port, &sensor->value)
  }
};
