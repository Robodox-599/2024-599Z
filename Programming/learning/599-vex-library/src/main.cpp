#include "robodox/PRELUDE.hpp"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/PID.h"

// Controller 
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor L(15, pros::E_MOTOR_GEARSET_06, true); // left front motor. reversed 
pros::Motor R(19, pros::E_MOTOR_GEARSET_06); // right back motor.

// motor groups
std::shared_ptr<pros::MotorGroup> leftMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<pros::Motor>{L});
std::shared_ptr<pros::MotorGroup> rightMotors = std::make_shared<pros::MotorGroup>(std::initializer_list<pros::Motor>{R});

// IMU port 2
pros::IMU inert(21); // change number in parenthesis to change port, make sure it does not go to a port already taken

chassisOdom chassis(
	// L,
	// R,
	leftMotors,
	rightMotors,
	inert, /* inertial sensor port here */
	2.75, /* wheel diameter*/
	0.75, /*gear ratio after */
	10.5, /* track width */
	90 /* start heading */
);

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
void autonomous() {
    pros::delay(1000);
    R.move(127);
    L.move(127);
    // pros::delay(1000);
    // R.brake();
    // L.brake();
    while(true){
	};
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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	while (true){
  		if (master.get_digital_new_press(DIGITAL_Y)){
			R.move(127);
    		L.move(127);
			}
		else if (master.get_digital_new_press(DIGITAL_X)){
			R.move(0);
   			L.move(0);
		}
		pros::delay(10);
	}
}

