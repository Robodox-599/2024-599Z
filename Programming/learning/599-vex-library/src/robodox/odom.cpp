#include "robodox/PRELUDE.hpp"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/PID.h"

float reduce_0_to_360(float angle) {
  /* Ensures angle is within the range [0, 360) degrees. Loops until the angle falls within the range.*/
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { angle += 360; }   // Shifts negative angles to positive by adding 360 degrees
    if(angle >= 360) { angle -= 360; } // Reduces angles exceeding 360 degrees by subtracting 360 degrees
  }
  return angle; // Returns the adjusted angle within the range [0, 360)
}
chassisOdom::chassisOdom(
    pros::Motor&leftMotor,
    pros::Motor& rightMotor,
    pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio,
    double trackWidth,
    double start_heading):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  start_heading(start_heading),
  leftMotor(leftMotor),
  rightMotor(rightMotor),
  IMU(IMU)
{
 pros::Task odomLoop([this] { odometry(); }, TASK_PRIORITY_DEFAULT + 2);
}
float chassisOdom::get_absolute_heading(){ 
  // Retrieves the raw rotation value from the Gyro sensor, scales it, and adjusts it within 0 to 360 degrees
  return( reduce_0_to_360( IMU.get_rotation() * 360.0 / 360.0 ) ); 
}

float chassisOdom::get_left_position_in(){
  double left_pos;
  // Retrieves the position of the left motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
 std::vector<double> positions{ leftMotor.get_position()};
  for(double val : positions) {
    left_pos =+ val;
  }
  return( left_pos * drive_in_to_deg_ratio );
}
float chassisOdom::get_right_position_in(){
  double right_pos;
  // Retrieves the position of the right motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  std::vector<double> positions{  rightMotor.get_position() };
  for(double val : positions) {
    right_pos =+ val;
  }
  return( right_pos * drive_in_to_deg_ratio );
}

float chassisOdom::distance_encoder_position(){
  return ((get_right_position_in()+get_left_position_in())/2);
}
float chassisOdom::xVal(){
  return(x);
}
float chassisOdom::yVal(){
  return(y);
}
float chassisOdom::resetEncoders(){
  leftMotor.tare_position();
  rightMotor.tare_position();
}
float chassisOdom::lcdOut(){
  pros::lcd::print(0, "X Position: %3f", xVal());
  pros::lcd::print( 1, "Y Position: %3f", yVal());
}
float chassisOdom::xCalc(float change_in_distance){
  x += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
}
float chassisOdom::yCalc(float change_in_distance){
  y += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
}
float chassisOdom::updatePos(float previous_distance_traveled){
  previous_distance_traveled = distance_encoder_position();
}
void chassisOdom::odometry() {
  leftMotor.tare_position();
  rightMotor.tare_position();
  double previous_distance_traveled = 0;
  while (true) {   
    double change_in_distance = distance_encoder_position() - previous_distance_traveled;
    x += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
    y += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
    previous_distance_traveled = distance_encoder_position();
    pros::lcd::print(0, "X Position: %3f", xVal());
    pros::lcd::print( 1, "Y Position: %3f", yVal());
    PRINT("X Position: " + std::to_string(xVal()));
    PRINT("Y Position: " + std::to_string(yVal()));  
    PRINT("LEFT Position: " + std::to_string(get_left_position_in()));  
    PRINT("RIGHT Position: " + std::to_string(get_right_position_in()));
    pros::delay(10);
  }
}