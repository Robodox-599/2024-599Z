#include "robodox/PRELUDE.hpp"
#include "robodox/PID.h"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/util.h"
#include "RobotSetup.h"
#include "auto.h"

// constants and other useful functions for auton

/*==========================================================================================================*/
/*  REMINDER- RETUNE THESE ALL FOR DRIVEBASE WHEN RPM, GEAR RATIO, WHEEL SIZE, OR EVEN WEIGHT, ARE CHANGED  */
/*==========================================================================================================*/
void default_constants(){
  chassis.set_constants(  
    /*               max voltage   | kp constants  | ki constants  |    kd constants  |  start ki constants */
    /* turn  */         127        ,      0.4      ,     0.02       ,      4          ,         15          ,
    /* drive */         127        ,      3        ,       0        ,      1          ,         0           ,
    /* swing */         127        ,      .9       ,     0.015      ,      10.5       ,         15          , 
    /*heading*/         127        ,      .4       ,       0        ,      1          ,         0           ); 
    chassis.set_exit_conditions(
      /* settle error            |     settle time    |   timeout   */
      /*swing*/  1               ,        300         ,     2000    ,
      /*turn*/   1               ,        250         ,     1500    ,
      /*drive*/  1.5             ,        250         ,     4000    );
    }



    
    void intake(){
      intakeMotor.move(-127);
    }
    void outake(){
      intakeMotor.move(127);
    }
    
    void PID_test(){
      default_constants();
      chassis.turn_to_angle(90);
    }
    void e_Off(){
      outake();
      climbPiston.set_value(true);
      chassis.drive_distance(15);
      chassis.turn_to_angle(200);
      climbPiston.set_value(false);
      chassis.drive_distance(23);
      chassis.turn_to_angle(230);
      intake();
      chassis.drive_distance(26);
      pros::delay(250);
      chassis.drive_distance(-30);
      chassis.turn_to_angle(350);
      outake();
      chassis.drive_distance(40);
      chassis.drive_distance(-20);
      chassis.turn_to_angle(260);
      intake();
      chassis.drive_distance(60);
      chassis.drive_distance(-10);
      chassis.turn_to_angle(30);
      outake();
      pros::delay(250);
      chassis.turn_to_angle(285);
      intake();
      chassis.drive_distance(10);
      chassis.turn_to_angle(40);
      outake();
      flapsPiston.set_value(true);
      chassis.drive_distance(50);
    }
    
    void q_Off(){
      // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.p
      outake();
      pros::delay(250);
      intake(); //intake spins to hold alliance ball
      chassis.drive_distance(35); // chassis drives forward till in front of goal
      chassis.turn_to_angle(90, 8); // chassis turns to face goal
      outake(); // outakes alliance ball
      pros::delay(500);
      chassis.turn_to_angle(295); // resets chassis to orignal starting position
      intake(); // intakes further most triball
      chassis.drive_distance(23); // drives to furthermost triball 
      pros::delay(500);
      chassis.turn_to_angle(90, 8); // turns to face goal
      outake(); // outakes further most triball
      pros::delay(500);
      chassis.drive_distance(30); // turns to face 2nd long bar triball
      chassis.drive_distance(-5); //drives back
      chassis.turn_to_angle(230); // turns to face goal
      intake();
      chassis.drive_distance(30);
      pros::delay(500);
      chassis.drive_distance(-20);
      chassis.turn_to_angle(90,8);
      outake(); // outakes triball
      chassis.drive_distance(20);
    }
    
    void e_Def(){
      // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.g2b1d1d222ec_0_25
      outake();
      pros::delay(250);
      climbPiston.set_value(true);
      chassis.swing_max_voltage = 6; 
      chassis.right_swing_to_angle(260);
      pros::delay(500);
      chassis.drive_distance(-5);
      climbPiston.set_value(false);
      chassis.drive_distance(40);
      chassis.turn_to_angle(225);
      chassis.drive_distance(10);
      chassis.turn_to_angle(315);
      flapsPiston.set_value(true);
      chassis.drive_distance(15);
      flapsPiston.set_value(false);
      chassis.drive_distance(-15);
      chassis.turn_to_angle(255);
      chassis.drive_distance(-40);
      chassis.turn_to_angle(360); // turn to climb bar
      chassis.drive_distance(20);
      chassis.turn_to_angle(315);
      chassis.drive_distance(10); // drive to climb bar to get AWP
      flapsPiston.set_value(true);
      chassis.drive_distance(12); // drive to climb bar to get AWP
      outake(); // spin outake to not posses any triball
    }

    void q_Def(){
      // use slides for setup: https://docs.google.com/presentation/d/1BWDEv9SH7713jcnmh8PpuUGN7VEAN8xQHvmU4T035hI/edit#slide=id.g2b1d1d222ec_0_20
      outake();
      pros::delay(250);
      intake(); // spin outake to not posses any triball
      climbPiston.set_value(true);
      chassis.swing_max_voltage = 6; 
      chassis.right_swing_to_angle(260);
      pros::delay(500);
      chassis.drive_distance(-5);
      climbPiston.set_value(false);
      // chassis.drive_distance(5);
      chassis.turn_to_angle(315); // turn to climb bar
      chassis.drive_distance(10); // drive to climb bar to get AWP
      flapsPiston.set_value(true);
      chassis.drive_distance(20); // drive to climb bar to get AWP
      outake(); // spin outake to not posses any triball
      // total estimated points: 6pts
    }
    
    void auto_setup(){
      chassis.drive_distance(-25);
      chassis.drive_distance(10);
      chassis.turn_to_angle(270);
      chassis.drive_distance(8);
    }
    
    void auto_skills(){
      outake();
      auto_setup(); // first step for auto
      kickerMotor.move(55*127/100);
      pros::delay(25000); // kicking
      chassis.drive_max_voltage = 12; 
      chassis.swing_max_voltage = 10; 
      chassis.turn_max_voltage = 10; 
      kickerMotor.brake();
      chassis.drive_distance(-10);
      chassis.turn_to_angle(0);
      chassis.drive_distance(17.5);
      chassis.turn_to_angle(70);
      chassis.drive_distance(35);
      flapsPiston.set_value(true);
      chassis.drive_distance(30);
      flapsPiston.set_value(false);
      chassis.drive_distance(20);
      chassis.right_swing_to_angle(120);
      flapsPiston.set_value(true);
      chassis.drive_distance(18);
      flapsPiston.set_value(false);
      chassis.turn_to_angle(330);
      chassis.drive_distance(-15);
      chassis.drive_distance(15);
      chassis.drive_distance(-15);
      chassis.drive_distance(13);
      chassis.turn_to_angle(230);
      flapsPiston.set_value(true);
      chassis.drive_distance(25);
      flapsPiston.set_value(false);
      chassis.drive_distance(15);
      chassis.turn_to_angle(100);
      flapsPiston.set_value(true);
      chassis.drive_distance(35);
      flapsPiston.set_value(false);
      chassis.drive_distance(-35);
      chassis.turn_to_angle(153);
      chassis.drive_distance(35);
      chassis.turn_to_angle(63);
      flapsPiston.set_value(true);
      chassis.drive_distance(20);
      chassis.drive_distance(-20);
      chassis.drive_distance(20);
      chassis.drive_distance(-30);
      chassis.turn_to_angle(120);
      chassis.drive_distance(50);
      flapsPiston.set_value(false);
      chassis.turn_to_angle(180);
      chassis.drive_distance(-15);
      chassis.drive_distance(15);
      chassis.drive_distance(-15);
      chassis.drive_distance(15);
      flapsPiston.set_value(true);
    }