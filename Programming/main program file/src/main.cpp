// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPiston          digital_out   A               
// climbPiston          digital_out   B               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      12              
// rot                  rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPiston          digital_out   A               
// climbPiston          digital_out   B               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      15              
// rot                  rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPiston          digital_out   A               
// climbPiston          digital_out   B               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      15              
// RotationSensor       rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPiston          digital_out   A               
// climbPistons         digital_out   D               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      15              
// RotationSensor       rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPistonLeft      digital_out   A               
// climbPistons         digital_out   D               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      15              
// RotationSensor       rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         10              
// RB                   motor         3               
// LF                   motor         7               
// RF                   motor         2               
// kickerMotor          motor         8               
// intakeMotor          motor         11              
// flapsPistonLeft      digital_out   A               
// flapsPistonRight     digital_out   B               
// climbPistons         digital_out   D               
// LM                   motor         9               
// RM                   motor         1               
// IMU                  inertial      15              
// RotationSensor       rotation      4               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LB                   motor         13              
// RB                   motor         12              
// LF                   motor         11              
// RF                   motor         2               
// kickerMotor          motor         14              
// intakeMotor          motor         10              
// flapsPistonLeft      digital_out   A               
// flapsPistonRight     digital_out   B               
// kickerSwitch         limit         C               
// climbPistons         digital_out   D               
// LM                   motor         21              
// RM                   motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----


#include "vex.h"
using namespace vex;
competition Competition;

//configuring chassis for auton
Drive chassis(

motor_group(LB, LM, LF), /* left motor group */

motor_group(RB, RM, RF), /* right motor group */

PORT12, /* inertial sensor port here */

2.75, /* wheel diameter*/

0.75, /*gear ratio after */

360/*Gyro scale, this is what the gyro/inertial reads when the robot is spun the robot 360 degrees.*/
);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  IMU.calibrate();
  default_constants();
}

void autonomous(void) {
  // autos will go here
  if(!IMU.isCalibrating()){
  winpoint();
  }  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used  to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
/*----------------------------------------------------------------*/
/*                           Variable Declaration Below                                                      */

/*Defining all global variables nessasary throughout the functions declared below*/

bool climbToggled = false; /*Wedge toggle variable used to track the state of the toggle wedge toggle function (declared later in the program)*/

bool flapsToggled = false; /*Flaps toggle variable used to track the state of the toggle Flaps toggle function (declared later in the program)*/

/*                               End Variable Declaration                                                       */
/*----------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*                           Function Declaration Below                                                                                           */
void kickerControl(){
 /*This is the Kicker Control Function, takes in no parameters*/
 if (Controller1.ButtonL1.pressing()){
    /* if l1 is being pressed it will spin the motors to shoot the kicker, then it will be
    reset using limit switch in the the following "else if" statement*/
    kickerMotor.spin(forward, 45, velocityUnits::pct); 
 } else if (!(50 < rot.angle() < 60)){
    kickerMotor.spin(forward, 45, velocityUnits::pct); 
 }
 else {
    // if there is no input then it will brake the kicker motor to reduce strain on motor
	  /*brakes motor using coast*/
    kickerMotor.stop(brakeType:: coast); 
 }
}

void intakeControls(){
 //intake control function
 if (Controller1.ButtonR1.pressing()){
    /* if r1 is being pressed then it will spin the iintake motor at 100% speed*/
    /* spins the intake Motor at 100% percent speed and spins it backward to intake the ball*/
    intakeMotor.spin(reverse, 100, velocityUnits::pct); 
} else if (Controller1.ButtonR2.pressing()) {
    /* if r2 is being pressed then it will spin the intake motor at 100% speed*/
    /* spins the intake Motor at 100% percent speed and spins it forward to outake the ball 
    from the intake*/
    intakeMotor.spin(forward, 100, velocityUnits::pct); 
 } else{
    // if there is no input then it will brake and hold the arm.
    /*sets brake type to Hold so then the Intake will keep the ball held into the intake*/
    intakeMotor.stop(brakeType:: hold);  }
}


void arcadeDrive(float fwdIn, float trnIn){
/*This is the arcade drive function. This uses the inputs passed in as parameters to calculate if there is turning or if there is regular driving. Overall this function was created in order to create modular code throughout the program.*/
 LB.spin(forward, (fwdIn + trnIn), percent); // uses parameters as input to determine the speed in percent for the motor
 RB.spin(forward, (fwdIn - trnIn), percent); // uses parameters as input to determine the speed in percent for the motor
 LF.spin(forward, (fwdIn + trnIn), percent); // uses parameters as input to determine the speed in percent for the motor
 RF.spin(forward, (fwdIn - trnIn), percent); // uses parameters as input to determine the speed in percent for the motor
}
void tankDrive(float leftIn, float rightIn){
/* This is the tank drive function. This uses the inputs passed in as parameters to drive the left or right motors. Overall this function was created in order to create modular code throughout the program.*/
  if (!(leftIn == 0)){
    LB.spin(forward, (leftIn), percent); // uses parameters as input to determine the speed in percent for the motor
    LM.spin(forward, (leftIn), percent); // uses parameters as input to determine the speed in percent for the motor
    LF.spin(forward, (leftIn), percent); // uses parameters as input to determine the speed in percent for the motor
  } else {
    LB.stop(brakeType::brake);
    LM.stop(brakeType::brake);
    LF.stop(brakeType::brake);
  }
   if (!(rightIn == 0)){
    RM.spin(forward, (rightIn), percent); // uses parameters as input to determine the speed in percent for the motor
    RB.spin(forward, (rightIn), percent); // uses parameters as input to determine the speed in percent for the motor
    RF.spin(forward, (rightIn), percent); // uses parameters as input to determine the speed in percent for the motor
   } else {
    RB.stop(brakeType::brake);
    RM.stop(brakeType::brake);
    RF.stop(brakeType::brake);
   }
}

void arcadeDriveControl(float fwdIn, float trnIn){
 /*This is the arcade Drive control function. This function takes in two inputs as the joystick turn and forward values. It will then put a deadzone on the joysticks and pass the new values into the Arcade Drive function where the robot will start to drive. */
 float fwdVal;
 float trnVal;
 if (fabs(fwdIn) >= 10 ){
   /* If the absolute value of the input is greater than 10% then the variable FwdVal will be changed to be 90% of the input from the user, this is used to set the deadzones. Also, this will apply the modifier in order to change the output to make sure that the slow toggle will limit the max speed to be the modifier value, which was defined in the toggle function*/
   fwdVal = fwdIn*.90;
 } else {
   /*If the absolute value of the input is less than 10% then the variable FwdVal will be changed to be 0, and ignore the input from the user. This is a part of the deadzones. */
   fwdVal = 0;
 }
 if(fabs(trnIn) >= 20 ){
    /* If the absolute value of the input is greater than 20% then the variable TrnVal will be changed to be 80% of the input from the user, this is used to set the deadzones. Also, this will apply the modifier in order to change the output to make sure that the slow toggle will limit the max speed to be the modifier value, which was defined in the toggle function*/
   trnVal = trnIn*.80;
 } else {
   /*If the absolute value of the input is less than 20% then the variable TrnVal will be changed to be 0, and ignore the input from the user. This is a part of the deadzones. */
   trnVal = 0;
 }
 /*After deadzones are calculated, these new Values will be passed into the Arcade Drive function in order to drive the robot*/
 arcadeDrive(fwdVal, trnVal);
}
void tankDriveControl(float leftIn, float rightIn){
 float leftVal;
 float rightVal;
 if (fabs(leftIn) >= 5 ){
    /* If the absolute value of the input is greater than 5% then the variable leftVal will be changed to be 95% of the input from the user, this is used to set the deadzones. Also, this will apply the modifier in order to change the output to make sure that the slow toggle will limit the max speed to be the modifier value, which was defined in the toggle function*/
   leftVal = leftIn*.95;
 } else {
   /*If the absolute value of the input is less than 5% then the variable leftVal will be changed to be 0, and ignore the input from the user. This is a part of the deadzones. */
   leftVal = 0;
 }
 if(fabs(rightIn) >= 10 ){
   /* If the absolute value of the input is greater than 10% then the variable rightVal will be changed to be 95% of the input from the user, this is used to set the deadzones. Also, this will apply the modifier in order to change the output to make sure that the slow toggle will limit the max speed to be the modifier value, which was defined in the toggle function*/
   rightVal = rightIn*.90;
 } else {
    /*If the absolute value of the input is less than 10% then the variable rightVal will be changed to be 0, and ignore the input from the user. This is a part of the deadzones. */
   rightVal = 0;
 }
 /*After deadzones are calculated, these new Values will be passed into the tankDrive function in order to drive the robot*/
 tankDrive(leftVal, rightVal);
}
void toggleFlaps(){
/*This is the toggleFlaps function, it takes in no parameters but uses the value of the flapsToggled in
order to determine if the flapsPiston should be set to true or false. It is called in the main function
as a callback for the .pressed() function. It will first switch the flapsToggled value to inverse it, then
check the state of the flapsToggled*/
 flapsToggled = !flapsToggled; // inverses state of flapsToggled
 if (flapsToggled){
   //if flapsToggled is true then it will switch the wedge piston to be the true
  flapsPiston.set(true);
   } else{
   //if flapsToggled is false then it will switch the wedge piston to be the false
  flapsPiston.set(false);
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
   climbPiston.set(true);
 } else{
   //if climbToggled is false then it will switch the climb pistons to be the false
   climbPiston.set(false);
 }
}
/*                         End Function Declarations                                             */
/*-----------------------------------------------------------------------------------------------*/


void usercontrol(void) {
  rot.resetPosition(); 
  while (1) {
    //drive controls
    //arcadeDriveControl(Controller1.Axis3.value(), Controller1.Axis1.value());
    tankDriveControl(Controller1.Axis3.value(), Controller1.Axis2.value());
    //kicker controls
    kickerControl();
    // flaps controls
    Controller1.ButtonB.pressed(toggleFlaps); // calls the toggle function for the flaps when the button is pressed
    //intake controls
    intakeControls();
    Controller1.ButtonY.pressed(toggleclimb);
    wait(20, msec); 
  }
}
//main function
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}

