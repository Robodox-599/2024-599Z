#pragma once
#include "vex.h"

class Drive{
/*This class, Drive, encapsulates functionalities and properties 
  related to controlling the robots autonomous driving function. 
  Using a class allows the programmer to grou related functionalities 
  together makes the code more readable, maintainable, and reusable. 
  Along with this other members can interact with the Drive class without
  worrying about the internal complexities of its functionalities.*/
private:
/*constants nesssasary for calculations, these are not defaulted 
  to any value so they must be set in the main file. These are hidden 
  from external access (hence the private)*/
  float wheel_diameter;
  float wheel_ratio;
  float gyro_scale;
  float drive_in_to_deg_ratio;
public: /*Externally accessible instances and functions to encapsulitate the drive*/
/*initializing drive train motor groups and inertial sensor*/
  motor_group DriveL;
  motor_group DriveR;
  inertial Gyro;
/*turn constants */
  float turn_max_voltage;
  float turn_kp;
  float turn_ki;
  float turn_kd;
  float turn_starti;
/*turn conditions*/
  float turn_settle_error;
  float turn_settle_time;
  float turn_timeout;
/*drive constants */
  float drive_max_voltage;
  float drive_kp;
  float drive_ki;
  float drive_kd;
  float drive_starti;
/*drive conditions*/
  float drive_settle_error;
  float drive_settle_time;
  float drive_timeout;
/*heading constants*/
  float heading_max_voltage;
  float heading_kp;
  float heading_ki;
  float heading_kd;
  float heading_starti;
/*swing turn constants*/
  float swing_max_voltage;
  float swing_kp;
  float swing_ki;
  float swing_kd;
  float swing_starti;
/*swing conditions*/
  float swing_settle_error;
  float swing_settle_time;
  float swing_timeout;
/*Desired heading for turn_to_angle() method,
 it is basically the variable which holds the 
 angle where you want to turn to */
  float desired_heading;
/*the initialization function which is set in the main file*/
  Drive(motor_group DriveL, motor_group DriveR, int gyro_port, float wheel_diameter, float wheel_ratio, float gyro_scale);
/*Very simple drive method which drives the motors
 forwards with certain voltages that are passed in 
 as parameters*/
  void drive_with_voltage(float leftVoltage, float rightVoltage);
/*uses the gyroscope to get the absolute heading of the robot. */
  float get_absolute_heading();
/*Uses built in motor encoders to find the input degrees of 
  the left motor group*/
  float get_left_position_in();
/*Uses built in motor encoders to find the input degrees of 
  the right motor group*/
  float get_right_position_in();
/*Defines constants for all PID uses in driving 
(Ex: turn, swing turn, drive)*/
  void set_constants(
/*Defines the parameters as the constants for turning*/
  float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, 

/*Defines the parameters as the constants for driving*/
  float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti,

/*Defines the parameters as the constants for swing turning*/
  float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti, 

/*Defines the parameters as the constants for the heading*/
  float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti
  ); 
  void set_exit_conditions(
/*Defines the parameters as the conditions for the swing turns*/
  float swing_settle_error, float swing_settle_time, float swing_timeout, 
/*Defines the parameters as the conditions for the regular turns*/
  float turn_settle_error, float turn_settle_time, float turn_timeout, 
/*Defines the parameters as the conditions for the regular drive*/
  float drive_settle_error, float drive_settle_time, float drive_timeout);
/*Method overloading to allow for certain combinations of parameters in the turn to angle methods, some are required as moving along*/
  void turn_to_angle(float angle);
  void turn_to_angle(float angle, float turn_max_voltage);
  void turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout);
  void turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti);
/*Method overloading to allow for certain combinations of parameters in the drive distance methods, some are required as moving along*/
  void drive_distance(float distance);
  void drive_distance(float distance, float heading);
  void drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage);
  void drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout);
  void drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti);
/*Method overloading to allow for certain combinations of parameters in the swing to angle methods, some are required as moving along*/
  void left_swing_to_angle(float angle);
  void left_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);
  void right_swing_to_angle(float angle);
  void right_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti);
};