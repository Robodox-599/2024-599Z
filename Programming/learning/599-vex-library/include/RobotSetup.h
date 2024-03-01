#include "robodox/PRELUDE.hpp"
//All drive motors.
extern pros::Controller master;
extern pros::Motor RF;
extern pros::Motor RM;
extern pros::Motor RB;
extern pros::Motor LF;
extern pros::Motor LM;
extern pros::Motor LB; 
//All manipulator motors and pistons.
extern pros::Motor kickerMotor;
extern pros::Motor intakeMotor;
extern pros::ADIDigitalOut flapsPiston;
extern pros::ADIDigitalOut climbPiston;
//All sensors.
extern pros::IMU imu;
