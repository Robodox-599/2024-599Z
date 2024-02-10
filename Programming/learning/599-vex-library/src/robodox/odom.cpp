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
    const pros::Motor& leftMotor,
    const pros::Motor& rightMotor,
    const pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio,
    double trackWidth,
    double start_heading):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  start_heading(start_heading),
  leftMotor(std::make_shared<pros::Motor>(leftMotor)),
  rightMotor(std::make_shared<pros::Motor>(rightMotor)),
  IMU(std::make_shared<pros::IMU>(IMU))
{
pros::Task odomTask([this]{this->odometry();});
}


float chassisOdom::get_absolute_heading(){ 
  // Retrieves the raw rotation value from the Gyro sensor, scales it, and adjusts it within 0 to 360 degrees
  return( reduce_0_to_360( IMU->get_rotation() * 360.0 / 360.0 ) ); 
}

float chassisOdom::get_left_position_in(){
  double left_pos;
  // Retrieves the position of the left motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
 std::vector<double> positions{ leftMotor->get_position()};
  for(double val : positions) {
    left_pos =+ val;
  }
  return(leftMotor->get_position()  * drive_in_to_deg_ratio );
}
float chassisOdom::get_right_position_in(){
  double right_pos;
  // Retrieves the position of the right motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  std::vector<double> positions{  rightMotor->get_position() };
  for(double val : positions) {
    right_pos =+ val;
  }
  return(rightMotor->get_position() * drive_in_to_deg_ratio );
}

float chassisOdom::distance_encoder_position(){
  return ((get_right_position_in()+get_left_position_in())/2);
}
float chassisOdom::xVal(){
  return x;
}
float chassisOdom::yVal(){
  return y;
}
void chassisOdom::resetEncoders(){
  leftMotor->tare_position();
  rightMotor->tare_position();
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

void chassisOdom::odometry() {
  float x = 0;
  float y = 0;
  // resetEncoders();
  double previous_distance_traveled = 0;
  printf(" reset previous_distance_traveled \n");
  leftMotor->tare_position();
  rightMotor->tare_position();
  printf("reset encoders \n");
  while (true) {   
    double absolute_heading = std::fmod((360 - IMU->get_heading()) + start_heading, 360);
    printf("absolute_heading: %lf\n", absolute_heading);
    double average_encoder_position = (leftMotor->get_position() + rightMotor->get_position()) / 2;
    printf("average_encoder_position: %lf\n", average_encoder_position);
    double distance_traveled = (average_encoder_position * 0.75 / 360.0 * M_PI * 2.75);
    printf("distance_traveled: %lf\n", distance_traveled);
    double change_in_distance = distance_traveled - previous_distance_traveled; 
    printf("change_in_distance: %lf\n", change_in_distance);  
    x += (change_in_distance * std::cos(absolute_heading * (M_PI /180)));
    printf("X Position: %lf\n", x);
    y += change_in_distance * std::sin(absolute_heading * (M_PI /180));
    printf("Y Position: %lf\n", y);  
    previous_distance_traveled = distance_traveled;
    printf("previous_distance_traveled: %lf\n", previous_distance_traveled);  
    pros::delay(10);
  }
}