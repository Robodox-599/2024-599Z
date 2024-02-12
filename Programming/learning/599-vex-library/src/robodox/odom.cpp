#include "robodox/PRELUDE.hpp"
#include "robodox/PID.h"
#include "robodox/odom.h"
#include "robodox/drive.h"

float reduce_0_to_360(float angle) {
  /* Ensures angle is within the range [0, 360) degrees. Loops until the angle falls within the range.*/
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { angle += 360; }   // Shifts negative angles to positive by adding 360 degrees
    if(angle >= 360) { angle -= 360; } // Reduces angles exceeding 360 degrees by subtracting 360 degrees
  }
  return angle; // Returns the adjusted angle within the range [0, 360)
}
chassisOdom::chassisOdom(
    const pros::Motor_Group& leftMotors,
    const pros::Motor_Group& rightMotors,
    const pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio,
    double trackWidth,
    double start_heading):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  start_heading(start_heading),
  leftMotors(std::make_shared<pros::Motor_Group>(leftMotors)),
  rightMotors(std::make_shared<pros::Motor_Group>(rightMotors)),
  IMU(std::make_shared<pros::IMU>(IMU))
{
pros::Task odomTask([this]{this->odometry();});
}


float chassisOdom::get_absolute_heading(){ 
  // Retrieves the raw rotation value from the Gyro sensor, scales it, and adjusts it within 0 to 360 degrees
  return(std::fmod((360 - IMU->get_heading()) + start_heading, 360)); 
}

float chassisOdom::average_encoder_position(){
  float encoder_position = 0 ;
  std::vector<double> left_positions = leftMotors->get_positions();
  std::vector<double> right_positions = rightMotors->get_positions();
  for(const int& i : right_positions){
  encoder_position += right_positions[i];
  } 
  for(const int& i : left_positions){
  encoder_position += left_positions[i];
  } 
  float avg_encoder_position = encoder_position /2;
  return (avg_encoder_position);
}
// float chassisOdom::average_encoder_position(){
//   float encoder_position = rightMotor->get_position() + leftMotor->get_position();
//   float avg_encoder_position = encoder_position /2;
//   return (avg_encoder_position);

// }
float chassisOdom::xVal(){
  return x;
}
float chassisOdom::yVal(){
  return y;
}
void chassisOdom::resetOdom(){
  leftMotors->tare_position();
  rightMotors->tare_position();
  previous_distance_traveled = 0;
  x = 0;
  y = 0;
}
void chassisOdom::lcdOut(){
  pros::lcd::print(0, "X Position: %3f", xVal());
  pros::lcd::print( 1, "Y Position: %3f", yVal());
}
void chassisOdom::xCalc(float change_in_distance){
  x += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
}
void chassisOdom::yCalc(float change_in_distance){
  y += change_in_distance * std::cos(get_absolute_heading() * (M_PI / 180));
}
float chassisOdom::distance_traveled(){
  return(average_encoder_position() * 0.75 / 360.0 * M_PI * 2.75);
}


void chassisOdom::odometry() {
  resetOdom();
  while (true) {
    if (!(IMU->is_calibrating())){
      double change_in_distance = distance_traveled() - previous_distance_traveled; 
      xCalc(change_in_distance);
      yCalc(change_in_distance);
      previous_distance_traveled = distance_traveled();
    }
    lcdOut();
    pros::delay(10);
  }
}