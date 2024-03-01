#include "robodox/PRELUDE.hpp"
#include "auto.h"
#include "RobotSetup.h"
bool climbToggled = false; 
bool flapsToggled = false; 
bool autoCount = true;
bool  kickerToggle = false;
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
	LF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	LM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	LB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	kickerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	imu.reset();
	pros::lcd::register_btn1_cb(on_center_button);
}

/*----------------------------------------------------------------------------------*/
/*                           Function Declaration Below                             */
void kickerControl(float controllerButton, float kickerPercent){
	/*This is the Kicker Control Function, takes in no parameters*/
	if (controllerButton){
		/* if l1 is being pressed it will spin the motors to shoot the kicker, then it will be
		reset using limit switch in the the following "else if" statement*/
		kickerMotor.move(kickerPercent*127/100); 
	}else {
		// if there is no input then it will brake the kicker motor to reduce strain on motor
		/*brakes motor using coast*/
		kickerMotor.brake(); 
	}
}

void toggleKicker(){
	/*This is the toggleclimb function, it takes in no parameters but uses the value of the climbToggled in
	order to determine if the climbPistons should be set to true or false. It is called in the main function
	as a callback for the .pressed() function. It will first switch the climbToggled value to inverse it, then
	check the state of the climbToggled*/
	kickerToggle = !kickerToggle; // inverses state of climbToggled
	if (kickerToggle){
		//if climbToggled is true then it will switch the climb pistons to be the true
		kickerMotor.move(55*127/100);
	} else{
		//if climbToggled is false then it will switch the climb pistons to be the false
		kickerMotor.brake(); 
	}
}

void intakeControls(float intake, float outake){
	//intake control function
	if (intake){
		/* if r1 is being pressed then it will spin the iintake motor at 100% speed*/
		/* spins the intake Motor at 100% percent speed and spins it backward to intake the ball*/
		intakeMotor.move(-127);
	} else if (outake) {
		/* if r2 is being pressed then it will spin the intake motor at 100% speed*/
		/* spins the intake Motor at 100% percent speed and spins it forward to outake the ball 
		from the intake*/
		intakeMotor.move(127);
	} else{
		// if there is no input then it will brake and hold the arm.
		/*sets brake type to Hold so then the Intake will keep the ball held into the intake*/
		intakeMotor.brake(); 
	}
}
void toggleFlaps(){
	/*This is the toggleFlaps function, it takes in no parameters but uses the value of the flapsToggled in
	order to determine if the flapsPiston should be set to true or false. It is called in the main function
	as a callback for the .pressed() function. It will first switch the flapsToggled value to inverse it, then
	check the state of the flapsToggled*/
	flapsToggled = !flapsToggled; // inverses state of flapsToggled
	if (flapsToggled){
		//if flapsToggled is true then it will switch the wedge piston to be the true
		flapsPiston.set_value(true);
	} else{
		//if flapsToggled is false then it will switch the wedge piston to be the false
		flapsPiston.set_value(false);
	}
}
void toggleclimb(){
	/*This is the toggleclimb function, it takes in no parameters but uses the value of the climbToggled in
	order to determine if the climbPistons should be set to true or false. It is called in the main function
	as a callback for the .pressed() function. It will first switch the climbToggled value to inverse it, then
	check the state of the climbToggled*/
	climbToggled = !climbToggled; // inverses state of climbToggled
	if (climbToggled){
		//if climbToggled is true then it will switch the climb pistons to be the true
		climbPiston.set_value(true);
	} else{
		//if climbToggled is false then it will switch the climb pistons to be the false
		climbPiston.set_value(false);
	}
}

void flapsControl(float toggleButton, float holdButton){
	if (toggleButton){
		toggleFlaps();
	} 
	if (holdButton){
		flapsPiston.set_value(true);
	} else{
		flapsPiston.set_value(false);
	}
}
void climbControl(float toggleButton){
	if (toggleButton){
		toggleclimb();
	}
}

void skillsSetup(){
	if(((!imu.is_calibrating())) && (autoCount == true)){
		auto_setup(); 
		autoCount = !autoCount;
	}
}

void tankDrive(int left, int right){
	LF = left;
	LM = left;
	LB = left;
	
	RF = right;
	RM = right;
	RB = right;
}

/*                         End Function Declarations                                             */
/*-----------------------------------------------------------------------------------------------*/


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
	// leftMotors->move(127);
	// rightMotors->move(127);
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
	while (true){
		flapsControl(master.get_digital_new_press(DIGITAL_B), master.get_digital_new_press(DIGITAL_L2));
		climbControl(master.get_digital_new_press(DIGITAL_X));
		intakeControls(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1), master.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
		kickerControl(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1), 55);
		skillsSetup();
		tankDrive(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		pros::delay(10);
	}
}

