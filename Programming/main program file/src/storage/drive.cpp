#include "vex.h"

float reduce_0_to_360(float angle) {
  /* Ensures angle is within the range [0, 360) degrees. Loops until the angle falls within the range.*/
  while(!(angle >= 0 && angle < 360)) {
    if(angle < 0) { angle += 360; }   // Shifts negative angles to positive by adding 360 degrees
    if(angle >= 360) { angle -= 360; } // Reduces angles exceeding 360 degrees by subtracting 360 degrees
  }
  return angle; // Returns the adjusted angle within the range [0, 360)
}

float reduce_negative_180_to_180(float angle) {
   /* Ensures angle is within the range [-180, 180) degrees. Loops until the angle falls within the range.*/
  while(!(angle >= -180 && angle < 180)) {
    if(angle < -180) { angle += 360; } // Shifts angles below -180 degrees to the positive range by adding 360 degrees
    if(angle >= 180) { angle -= 360; } // Reduces angles exceeding 180 degrees to the negative range by subtracting 360 degrees
  }
  return angle; // Returns the adjusted angle within the range [-180, 180)
}

float clamp(float input, float min, float max){
  /* Constrains input value within the specified range defined by min and max. Returns min if input is smaller than min, max if input is larger than max, else returns input.*/
  if( input > max ){ return(max); } // Returns max if input exceeds max
  if(input < min){ return(min); } // Returns 'min' if 'input' is smaller than min
  return(input); // Returns input within the range defined by min and max
}

Drive::Drive(motor_group DriveL, motor_group DriveR, int gyro_port, float wheel_diameter, float wheel_ratio, float gyro_scale):
/*This constructor initializes an instance of the Drive class with the provided parameters. It sets up the necessary properties 
  of the Drive object based on the arguments passed when an object of this class is created. Initializes class member variables 
  with the values provided in the constructor parameters.*/
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  gyro_scale(gyro_scale),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  DriveL(DriveL),
  DriveR(DriveR),
  Gyro(inertial(gyro_port))
{
}

void Drive::drive_with_voltage(float leftVoltage, float rightVoltage){
  /*Spins the drivebase left motor group or right motor group, based on the inputs passed in as parameters*/
  DriveL.spin(fwd, leftVoltage, volt); // spinning left side with a voltage of leftVoltage
  DriveR.spin(fwd, rightVoltage, volt); // spinning right side with a voltage of rightVoltage
}

void Drive::set_constants(
  /* Regular Turn Constants Parameters---------------------*/
  float turn_max_voltage, 
  float turn_kp, 
  float turn_ki, 
  float turn_kd, 
  float turn_starti, 

/* Regular Drive Constants Parameters--------------------*/
  float drive_max_voltage, 
  float drive_kp, 
  float drive_ki, 
  float drive_kd, 
  float drive_starti, 

/* Swing Turn Constants Parameters-----------------------*/
  float swing_max_voltage, 
  float swing_kp, 
  float swing_ki, 
  float swing_kd, 
  float swing_starti, 
  
/*Heading Constants Parameters---------------------------*/
  float heading_max_voltage, 
  float heading_kp,
  float heading_ki, 
  float heading_kd, 
  float heading_starti
  
)
  {

/* Regular Turn Constants being set to Parameters-----------*/
  this->turn_max_voltage = turn_max_voltage;
  this->turn_kp = turn_kp;
  this->turn_ki = turn_ki;
  this->turn_kd = turn_kd;
  this->turn_starti = turn_starti;

/* Regular Drive Constants  being set to Parameters---------*/
  this->drive_max_voltage = drive_max_voltage;
  this->drive_kp = drive_kp;
  this->drive_ki = drive_ki;
  this->drive_kd = drive_kd;
  this->drive_starti = drive_starti;

/*Swing Turn Constants being set to Parameters--------------*/
  this->swing_max_voltage = swing_max_voltage;
  this->swing_kp = swing_kp;
  this->swing_ki = swing_ki;
  this->swing_kd = swing_kd;
  this->swing_starti = swing_starti;

/*Heading Constants being set to Parameters------------------*/
  this->heading_max_voltage = heading_max_voltage;
  this->heading_kp = heading_kp;
  this->heading_ki = heading_ki;
  this->heading_kd = heading_kd;
  this->heading_starti = heading_starti;

}

void Drive::set_exit_conditions(
/*Regular Turn Conditions Parameters----------------------------------*/
  float turn_settle_error, 
  float turn_settle_time, 
  float turn_timeout, 
/*Swing Turn Conditions Parameters------------------------------------*/
  float swing_settle_error, 
  float swing_settle_time, 
  float swing_timeout,
/*Regular Drive Conditions Parameters---------------------------------*/ 
  float drive_settle_error, 
  float drive_settle_time, 
  float drive_timeout
){
/*Regular Turn Conditions being set to Parameters---------------------*/
  this->turn_settle_error = turn_settle_error;
  this->turn_settle_time = turn_settle_time;
  this->turn_timeout = turn_timeout;
/*Regular Drive Conditions being set to Parameters--------------------*/
  this->drive_settle_error = drive_settle_error;
  this->drive_settle_time = drive_settle_time;
  this->drive_timeout = drive_timeout;
/*Swing Turn Conditions being set to Parameters----------------------*/
  this->swing_settle_error = swing_settle_error;
  this->swing_settle_time = swing_settle_time;
  this->swing_timeout = swing_timeout;
}

float Drive::get_absolute_heading(){ 
  // Retrieves the raw rotation value from the Gyro sensor, scales it, and adjusts it within 0 to 360 degrees
  return( reduce_0_to_360( Gyro.rotation() * 360.0 / gyro_scale ) ); 
}

float Drive::get_left_position_in(){
  // Retrieves the position of the left motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  return( DriveL.position(deg) * drive_in_to_deg_ratio );
}
float Drive::get_right_position_in(){
  // Retrieves the position of the right motor group in degrees and converts it to inches using the drive_in_to_deg_ratio
  return( DriveR.position(deg) * drive_in_to_deg_ratio );
}
/*These methods in the Drive class are an example of method overloading. They provide different versions of the turn_to_angle() method with varying parameter combinations.*/
void Drive::turn_to_angle(float angle){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}
void Drive::turn_to_angle(float angle, float turn_max_voltage){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}
void Drive::turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}
/*These methods in the Drive class are an example of method overloading. They provide different versions of the drive_distance() method with varying parameter combinations.*/
void Drive::drive_distance(float distance){
  drive_distance(distance, desired_heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}
void Drive::drive_distance(float distance, float heading){
  drive_distance(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}
void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage){
  drive_distance(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}
void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout){
  drive_distance(distance, heading, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}
/*These methods in the Drive class are an example of method overloading. They provide different versions of the right_swing_to_angle() and left_swing_to_angle() methods with varying parameter combinations.*/
void Drive::right_swing_to_angle(float angle){
  right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}
void Drive::left_swing_to_angle(float angle){
  left_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti){
  /*This method orchestrates the robot's turning behavior by using a PID controller to regulate the robot's orientation. It continuously adjusts the motor voltages based on the PID-calculated output until the robot reaches the desired angle, then stops the motors once the robot settles at that angle. The PID controller helps in achieving accurate and controlled turning behavior by constantly correcting deviations from the desired angle.*/
  desired_heading = angle; //Sets the desired heading to the specified angle
  PID turnPID(reduce_negative_180_to_180(angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout); // Creates a PID controller turnPID for controlling the turning maneuver. The PID controller is initialized with the error between the desired angle and the current absolute heading obtained from get_absolute_heading(), along with the provided PID constants
  while(turnPID.settled() == false){// Enters a loop controlled by the PID controller's settling condition
    float error = reduce_negative_180_to_180(angle - get_absolute_heading()); //Retrieves the current error by calculating the difference between the desired angle and the current absolute heading.
    float output = turnPID.calculate(error); // Calculates the control output using the PID controller based on the current error:
    output = clamp(output, -turn_max_voltage, turn_max_voltage); //Limits the output to be within the range of -turn_max_voltage to turn_max_voltage.
    drive_with_voltage(output, -output); //Drives the motors (DriveL and DriveR) with the calculated output voltages in opposite directions to achieve the turning maneuver.
    task::sleep(10); // Delays the loop execution for a short duration to control the loop frequency.
  }
  //Pauses the loop when the PID controller indicates that the system has settled at the desired angle. Stops both motor groups (DriveL and DriveR) in a hold to cease all movement.
  DriveL.stop(hold);
  DriveR.stop(hold);
}

void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  /*This method orchestrates the movement of the robot to a specified distance and heading using two PID controllers—one for distance control and another for heading control.*/
  desired_heading = heading; //Sets the desired heading to the specified heading.
  PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout); // Initializes a PID controller drivePID for controlling the distance 
  PID headingPID(reduce_negative_180_to_180(heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti); // Initializes a PID controller headingPID for controlling the heading
  float start_average_position = (get_left_position_in()+get_right_position_in())/2.0; //Calculates the starting average position between the left and right motor groups.
  float average_position = start_average_position; // applies the starting average position to the average position variable
  while(drivePID.settled() == false){ //Enters a loop controlled by the drivePID's settling condition
    average_position = (get_left_position_in()+get_right_position_in())/2.0; // Retrieves the current average position.
    float drive_error = distance+start_average_position-average_position; //Calculates errors for distance. Drive_error: Represents the difference between the target distance and the current average position.
    float heading_error = reduce_negative_180_to_180(heading - get_absolute_heading()); // Calculates errors for heading. Heading_error: Represents the error between the desired heading and the current absolute heading.
    float drive_output = drivePID.calculate(drive_error); // Uses the drivePID to calculate the drive output based on the drive_error.
    float heading_output = headingPID.calculate(heading_error); // Uses the headingPID to calculate the heading output based on the heading_error.
    drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);// Limits drive output to its respective maximum voltage.
    heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);// Limits heading output to its respective maximum voltage.
    drive_with_voltage(drive_output+heading_output, drive_output-heading_output); // Adjusts motor voltages based on the calculated drive and heading outputs to move the robot while adjusting its heading.
    task::sleep(10); //Delays the loop execution for a short duration to control the loop frequency.
  }
  //Pauses the loop when the PID controller indicates that the system has settled at the desired angle. Stops both motor groups (DriveL and DriveR) in a hold to cease all movement.
  DriveL.stop(hold);
  DriveR.stop(hold);
}

void Drive::left_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  /*
This method, Drive::left_swing_to_angle, aims to turn the robot towards a specific angle using a PID controller specifically designed for a left swing turn. Let's break down this method:*/
  desired_heading = angle;
  PID swingPID(reduce_negative_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.settled() == false){
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = swingPID.calculate(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    DriveL.spin(fwd, output, volt);
    DriveR.stop(hold);
    task::sleep(10);
  }
  DriveL.stop(hold);
  DriveR.stop(hold);
}

void Drive::right_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  desired_heading = angle;
  PID swingPID(reduce_negative_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.settled() == false){
    float error = reduce_negative_180_to_180(angle - get_absolute_heading());
    float output = swingPID.calculate(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    DriveR.spin(reverse, output, volt);
    DriveL.stop(hold);
    task::sleep(10);
  }
  DriveL.stop(hold);
  DriveR.stop(hold);
}