#include "robodox/odom.h"
#include "robodox/PRELUDE.hpp"
#include "main.h"
float reduce_0_to_360(float angle) {
  /* Ensures angle is within the range [0, 360) degrees. Loops until the angle falls within the range.*/
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { angle += 360; }   // Shifts negative angles to positive by adding 360 degrees
    if(angle >= 360) { angle -= 360; } // Reduces angles exceeding 360 degrees by subtracting 360 degrees
  }
  return angle; // Returns the adjusted angle within the range [0, 360)
}
Drive::Drive(
    pros::Motor_Group&leftMotors,
    pros::Motor_Group& rightMotors,
    pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio,
    int gyro_scale,
    double trackWidth,
    double start_heading,
    int rpm):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  gyro_scale(gyro_scale),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  start_heading(start_heading),
  leftMotors(leftMotors),
  rightMotors(rightMotors),
  IMU(IMU)
{
}
float Drive::get_absolute_heading(){ 
  // Retrieves the raw rotation value from the Gyro sensor, scales it, and adjusts it within 0 to 360 degrees
  return( reduce_0_to_360( IMU.get_rotation() * 360.0 / gyro_scale ) ); 
}

float Drive::get_left_position_in(){
  double left_pos;
  // Retrieves the position of the left motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  std::vector<double> positions = leftMotors.get_positions();
  for(double val : positions) {
    left_pos =+ val;
  }
  return( left_pos * drive_in_to_deg_ratio );
}
float Drive::get_right_position_in(){
  double right_pos;
  // Retrieves the position of the right motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  std::vector<double> positions = rightMotors.get_positions();
  for(double val : positions) {
    right_pos =+ val;
  }
  return( right_pos * drive_in_to_deg_ratio );
}

float Drive::distance_encoder_position(){
  return ((get_right_position_in()+get_left_position_in())/2);
}



constexpr double start_heading = 90;

double x = 0;
double y = 0;

void Drive::odometry() {
    leftMotors.tare_position();
    rightMotors.tare_position();

    double previous_distance_traveled = 0;

    while (true) {   
        double change_in_distance = distance_encoder_position() - previous_distance_traveled;
        
        x += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
        y += change_in_distance * std::sin(get_absolute_heading() * (M_PI / 180));

        // At the end of the loop, set previous_distance_traveled for the next loop iteration
        previous_distance_traveled = distance_encoder_position();

        pros::delay(10);
    }
}
float Drive::coordinatesX(){
  return(x);
}
float Drive::coordinatesY(){
  return(y);
}