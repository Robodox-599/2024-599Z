#include "vex.h"


// constants and other useful functions for auton

/*==========================================================================================================*/
/*  REMINDER- RETUNE THESE ALL FOR DRIVEBASE WHEN RPM, GEAR RATIO, WHEEL SIZE, OR EVEN WEIGHT, ARE CHANGED  */
/*==========================================================================================================*/
void default_constants(){
  chassis.set_constants(  
          /* max voltage | kp constants | ki constants | kd constants |  start ki constants */
/* turn  */    12       ,      0.4      ,     0.02    ,      4        ,         15          ,
/* drive */    127        ,      3    ,       0      ,      1         ,         0           ,
/* swing */    127        ,      .9      ,     0.015     ,      10.5       ,         15          , 
/*heading*/    12        ,      .4      ,       0      ,      1       ,         0           ); 
  chassis.set_exit_conditions(
         /* settle error   |     settle time    |   timeout   */
/*swing*/  1               ,        300         ,     2000    ,
/*turn*/   1               ,        250         ,     1500    ,
/*drive*/  1.5             ,        250         ,     4000    );
}
motor_group DriveL = motor_group(LB, LM, LF);
motor_group DriveR = motor_group(RB, RM, RF);
void wings(bool val){
  flapsPistonLeft.set(val);
  flapsPistonRight.set(val);
}
void drive_percent(float per){ 
  DriveL.spin(fwd, per, percent);
  DriveR.spin(fwd, per, percent); 
}
void intake(){
  intakeMotor.spin(forward, -100, percent);
}
void outake(){
  intakeMotor.spin(forward, 100, percent);
}

void corner_score(int iterate){
  for(int i=0; i>iterate; i++){
  drive_percent(-100); // drives WITHOUT PID control loop at full speed backwards
  wait(150, msec); // waits 150 msec before driving forward again
  drive_percent(100);
  wait(150, msec);
  }
}
// autos will start below 
void PID_test(){
  default_constants();
  chassis.left_swing_to_angle(90);
}
void e_Off(){
  // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.g2b1d1d222ec_0_0
  intake(); //intake spins to hold climb triball
  chassis.drive_max_voltage = 1000; // changes drive_max_voltage to maximum value to drive as fast as possible
  chassis.drive_distance(5); // drives 5 inches forward into climb triball
  default_constants(); // resets constants back to default values
  chassis.drive_distance(-30); // chassis drives backwards till in front of matchload zone
  chassis.turn_to_angle(225); // chassis turns around to let wings access matchload zone
  outake(); // outakes climb triball
  flapsPistonLeft.set(true); // opens wing to flick out matchload triball
  chassis.drive_distance(15); // drives into matchload triball with wing extended to flick out matchload triball
  flapsPistonLeft.set(false); // closes left wing
  chassis.turn_to_angle(270); // turns robot around to use back of robot to push into goals
  corner_score(2); // does standard corner scoring procedure (driving back and forth at full speed to score)
  chassis.turn_to_angle(0); // reset back to orignal position
  intake(); // starts spinning intake to grab 2nd long bar triball
  chassis.drive_distance(50); // drive to 2nd long bar triball
  chassis.turn_to_angle(225); // turns to face goal
  outake(); // outakes 2nd long bar triball to goal
  chassis.turn_to_angle(90); // turn to first long bar triball
  intake(); // spin intake for first long bar triball
  chassis.drive_distance(20); // drives into first long bar triball
  chassis.turn_to_angle(180); // turns to face goal
  outake(); // outakes first long bar triball into 3rd longbar triball
  wings(true); // open both wings
  chassis.drive_distance(40); // drive into goal and score all balls
  //total estimated points: 30pts
}

void q_Off(){
  // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.p
  intake(); //intake spins to hold alliance ball
  chassis.drive_distance(36); // chassis drives forward till in front of goal
  chassis.turn_to_angle(90, 8); // chassis turns to face goal
  outake(); // outakes alliance ball
  wait(250, msec);
  chassis.turn_to_angle(305); // resets chassis to orignal starting position
  chassis.drive_distance(15); // drives to furthermost triball 
  intake(); // intakes further most triball
  wait(150, msec);
  chassis.turn_to_angle(90, 8); // turns to face goal
  outake(); // outakes further most triball
  wait(150, msec);
  chassis.turn_to_angle(180); // turns to face 2nd long bar triball
  // chassis.drive_distance(20); // drives to ball
  // intake(); // intakes tribal
  // wait(150, msec);
  // chassis.drive_distance(-20); //drives back
  // chassis.turn_to_angle(90); // turns to face goal
  // outake(); // outakes triball
  // wait(150, msec);
  // wings(true); //opens wings
  // chassis.drive_distance(40); // drives and scores all 4 balls
  // wings(false); // closes wings
  // chassis.drive_distance(-15); // drives out of goal
  // chassis.turn_to_angle(315);// turns to face climb bar
  // chassis.drive_distance(40); // drives into climb bar to assist in AWP
  // //totral estimated points: 20pts
}

void e_Def(){
  // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.g2b1d1d222ec_0_25
  outake(); // spin outake to not posses any triball
  flapsPistonLeft.set(true); // opens wing to flick out matchload triball
  chassis.drive_distance(5); // drives into matchload triball with wing extended to flick out matchload triball
  flapsPistonLeft.set(false); // closes wing
  chassis.drive_distance(-22); // drives backwards and scores alliance triball
  chassis.drive_distance(12); // drives back forwards 
  chassis.turn_to_angle(270); // turns to face long bar triballs
  chassis.drive_distance(50); // drives toward long bar triballs
  flapsPistonRight.set(true); // opens wedge wing
  chassis.turn_to_angle(315); // turns to face long bar triballs
  chassis.drive_distance(30); // disrupts with wedge wings
  flapsPistonRight.set(false); // closes wedge wing
  chassis.drive_distance(-30); // drives back 
  chassis.turn_to_angle(270); // turns to go back to matchload zone
  chassis.drive_distance(-50); // drives back to matchload zone
  chassis.turn_to_angle(0); // turns to original position
  chassis.drive_distance(15); // drives forward 
  chassis.turn_to_angle(135); // turns a little bit more
  chassis.drive_distance(30); // drives into climb bar to push 2 more balls over 
  // total estimated points: 13pts
}

void q_Def(){
  // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.g2b1d1d222ec_0_20
  outake(); // spin outake to not posses any triball
  flapsPistonLeft.set(true); // opens wing to flick out matchload triball
  chassis.drive_distance(5); // drives into matchload triball with wing extended to flick out matchload triball
  flapsPistonLeft.set(false); // closes wing
  chassis.drive_distance(-22); // drives backwards and scores alliance triball
  chassis.drive_distance(12); // drives back forwards 
  chassis.turn_to_angle(315); // turn to climb bar
  chassis.drive_distance(30); // drive to climb bar to get AWP
  // total estimated points: 9pts
}

// void auto_skills(){
//   chassis.drive_distance();

// }