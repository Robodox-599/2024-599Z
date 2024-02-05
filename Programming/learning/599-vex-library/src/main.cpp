#include "robodox/PRELUDE.hpp"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/PID.h"

// Controller 
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor LF(-13, pros::E_MOTOR_GEARSET_06); // left front motor. reversed
// pros::Motor LM(-5, pros::E_MOTOR_GEARSET_06); // left middle motor. reversed
// pros::Motor LB(-4, pros::E_MOTOR_GEARSET_06); // left back motor. reversed
// pros::Motor RF(3, pros::E_MOTOR_GEARSET_06); // right front motor. 
// pros::Motor RM(2, pros::E_MOTOR_GEARSET_06); // right middle motor. 
pros::Motor RB(20, pros::E_MOTOR_GEARSET_06); // right back motor.

// motor groups
pros::MotorGroup leftMotors({LF/*, LM, LB*/}); // left motor group
pros::MotorGroup rightMotors({/*RF, RM, */RB}); // right motor group

// IMU port 2
pros::IMU inert(21); // change number in parenthesis to change port, make sure it does not go to a port already taken

chassisOdom chassis(
leftMotors, /* left motor group */
rightMotors, /* right motor group */
inert, /* inertial sensor port here */
2.75, /* wheel diameter*/
0.75, /*gear ratio after */
10.5, /* track width */
90 /* start heading */);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
} 

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	inert.reset();
	pros::lcd::register_btn1_cb(on_center_button);
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() { // Start our odometry thread.
    // The odometry loop will run in the background while moving.
    // Spin our drivetrain forward for 2 seconds.
    leftMotors.move(127);
	rightMotors.move(127);

    pros::delay(1000);
	leftMotors.brake();
	rightMotors.brake();

    // Print where we ended up on the coordinate plane onto the brain screen.
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	autonomous();
	while (true) {

		// int left = master.get_analog(ANALOG_LEFT_Y);
		// int right = master.get_analog(ANALOG_RIGHT_Y);

		// left_mtr = left;
		// right_mtr = right;
		pros::delay(20);
	}
}
