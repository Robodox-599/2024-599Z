#pragma once
#include "vex.h"
/*Created a PID class, this is to make my code more encapsulized and modular for my PID controller. 
This class can be used multiple times throughout the program whilest not loosing any of its functionality. 
This class is called PID and it defines public float datatypes to their default values in order to store 
values assigned by the user later on in the code. This class also creates 2 constructors each with their own
parameters. These constructors allow flexibility when creating instances of the PID class. Users can choose to
initialize the PID controller with different sets of parameters depending on their specific requirements and 
the available information about the system being controlled. */
class PID
{
public:
/* defines variables which may be redefined later on, this is done 
  to allow these variables to be passed into the constructors and 
  functions below.*/
/*These variables store the current error, the proportional, integral,
 and derivative constants, and the initial integral value respectively.*/
  float error = 0;
  float kp = 0;
  float ki = 0;
  float kd = 0;
  float starti = 0;
/*These represent parameters related to determining when the system has settled.*/
  float settle_error = 0;
  float settle_time = 0;
  float timeout = 0;
/*Used for storing cumulative and previous error values for control calculation.*/
  float accumulated_error = 0;
  float previous_error = 0;
/*Represents the calculated output of the PID controller.*/
  float output = 0;
/*Tracks time spent in settled and running states.*/
  float time_spent_settled = 0;
  float time_spent_running = 0;
/*Creates constructor to help control the PID controller,
  this was mainly implemented for the turnPid and swingPID functions 
  (shown later on in the program)*/
  PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);
/* creates constructor to help control the PID controller,
  this was mainly implemented for the drivePID function 
  (shown later on in the program)*/
  PID(float error, float kp, float ki, float kd, float starti);
/*A function that performs the PID calculations given a new error value and returns the controller's output.*/
  float calculate(float error);
/*A function to determine if the system has settled within a defined range/error threshold.*/
  bool settled();
};