#include "robodox/chassis.h"
#include "robodox/PRELUDE.hpp"

Drive::Drive(
    pros::Motor_Group&leftMotors,
    pros::Motor_Group& rightMotors,
    pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio,
    int gyro_scale,
    double trackWidth,
    int rpm):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  gyro_scale(gyro_scale),
  leftMotors(leftMotors),
  rightMotors(rightMotors),
  IMU(IMU)
{
}
