#include "vex.h" 
//This code implements the functionality of the PID class declared earlier. Let's go through each part of the code:
/*These are the implementations of the constructor functions for the PID class. They initialize the PID controller 
object with the provided parameters. The first constructor initializes a simpler version of the PID controller, while 
the second constructor provides more detailed parameters including settling criteria.*/
PID::PID(float error, float kp, float ki, float kd, float starti) :
  error(error),
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti)
{};

PID::PID(float error, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout) :
  error(error),
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti),
  settle_error(settle_error),
  settle_time(settle_time),
  timeout(timeout)
{};

float PID::calculate(float error){
  /*This is the Calculate Method in the PID class. This method performs the PID control calculation based on the provided
  error. It accumulates error within a certain range, resets accumulation on sign change, calculates the PID output, 
  updates settled time based on error threshold, and increments running time.*/
  if (fabs(error) < starti){
    /*If the absolute value of the error is less than the initial Integral value, then the error will be added to the 
    accumulated_error variable to track error. */
    accumulated_error+=error; //error is added to the accumulated_error variable
  }
  if ((error>0 && previous_error<0)||(error<0 && previous_error>0)){ 
    /*If the error is greater than 0, and the previous error is less than 0 or if the error is less than 0 and the previous
    error is greater than 0, then it will reset the accumulated_error back to 0 aka its default value */
    accumulated_error = 0; // sets accumulated_error back to its inital value
  }
  /*This is the PID output calculuation, it takes in all defined constants and errors to calculate the output.*/
  output = kp*error + ki*accumulated_error + kd*(error-previous_error); /*First mulitplies current error to the Potential, 
                                                                        then multiplies the accumulated error (defined earlier) 
                                                                        to the Integral, then mulitplies the Derivitative by the 
                                                                        difference between the error and the previous error. 
                                                                        Finally these are all added up and set equal to our output. */
  previous_error=error; // resets and redefines previous error as the new error. 

  if(fabs(error)<settle_error){
    /*if the absolute value of the error is less than the settle error, then it will add 10 to the time_spent_settled variable*/
    time_spent_settled+=10; // sets the time_spent_settled variable equal to the time_spent_settled variable plus 10
  } else {
    /*if the absolute value of the error is not less than the settle error, then it will make the time_spent_settled variable equal to 0*/
    time_spent_settled = 0; // sets the time_spent_settled variable equal to 0
  }
  time_spent_running+=10; // then adds 10 to the time spent running variable and returns the output to be used as control
  return output;
}

bool PID::settled(){
  /*This method checks whether the system has settled based on the accumulated running time and the settling criteria provided. 
  It returns true if either the timeout condition or the settle time condition is met, indicating that the system has settled.
  This code essentially defines the behavior of the PID controller, allowing it to calculate control signals based on errors 
  and determine if the system has settled within specified parameters.*/
  if (time_spent_running>timeout && timeout != 0){
    /*If time_spent_running is greater than timeout and the timeout is not 0, then return true*/
    return(true); //returns true
  }
  if (time_spent_settled>settle_time){
    /*If time_spent_settled is greater than the settle time then return true*/
    return(true); // returns true
  }
  /*Finally return false*/
  return(false); // returns false
}