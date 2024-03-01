#include "robodox/PRELUDE.hpp"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/PID.h"

#define FLAPS_DIGITAL_SENSOR_PORT 'A'
#define CLIMB_DIGITAL_SENSOR_PORT 'B'

pros::Controller masterController (pros::E_CONTROLLER_MASTER);

pros::Motor LF(7, pros::E_MOTOR_GEARSET_06, true); // left front motor. reversed 
pros::Motor LM(9, pros::E_MOTOR_GEARSET_06, true); // left front motor. reversed 
pros::Motor LB(10, pros::E_MOTOR_GEARSET_06, true); // left front motor. reversed 

pros::Motor RF(2, pros::E_MOTOR_GEARSET_06); // right back motor.
pros::Motor RM(1, pros::E_MOTOR_GEARSET_06); // right back motor.
pros::Motor RB(3, pros::E_MOTOR_GEARSET_06); // right back motor.

std::shared_ptr<pros::MotorGroup> leftMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<pros::Motor>{LF, LM, LB});
std::shared_ptr<pros::MotorGroup> rightMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<pros::Motor>{RF, RM, RB});

pros::Motor kickerMotor(8, pros::E_MOTOR_GEARSET_36); // left front motor. reversed 
pros::Motor intakeMotor(10, pros::E_MOTOR_GEARSET_06); // left front motor. reversed 

pros::IMU imu(12); 

pros::ADIDigitalOut flapsPiston (FLAPS_DIGITAL_SENSOR_PORT);
pros::ADIDigitalOut climbPiston (CLIMB_DIGITAL_SENSOR_PORT);


chassisOdom odom(
	// L,
	// R,
	leftMotors,
	rightMotors,
	imu, /* inertial sensor port here */
	2.75, /* wheel diameter*/
	0.75, /*gear ratio after */
	10.5, /* track width */
	90 /* start heading */
);

Drive chassis(
	// L,
	// R,
	leftMotors,
	rightMotors,
	imu, /* inertial sensor port here */
	2.75, /* wheel diameter*/
	0.75, /*gear ratio after */
	10.5, /* track width */
	90 /* start heading */
);
