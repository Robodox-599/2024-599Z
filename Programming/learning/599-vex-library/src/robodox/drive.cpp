#include "robodox/PRELUDE.hpp"
#include "robodox/PID.h"
#include "robodox/odom.h"
#include "robodox/drive.h"
#include "robodox/util.h"
Drive::Drive(
    std::shared_ptr<pros::MotorGroup> leftMotors,
    std::shared_ptr<pros::MotorGroup> rightMotors,
    const pros::IMU& IMU,  
    double wheel_diameter,
    double wheel_ratio):
  wheel_diameter(wheel_diameter),
  wheel_ratio(wheel_ratio),
  drive_in_to_deg_ratio(wheel_ratio/360.0*M_PI*wheel_diameter),
  leftMotors(leftMotors),
  rightMotors(rightMotors),
  IMU(std::make_shared<pros::IMU>(IMU))
{
    leftMotors->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
    rightMotors->set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
}


void Drive::drive_voltage(float left, float right){
  leftMotors->move(left);
  rightMotors->move(right);
}

void Drive::set_turn_constants(float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti){
  this->turn_max_voltage = turn_max_voltage;
  this->turn_kp = turn_kp;
  this->turn_ki = turn_ki;
  this->turn_kd = turn_kd;
  this->turn_starti = turn_starti;
} 

void Drive::set_drive_constants(float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti){
  this->drive_max_voltage = drive_max_voltage;
  this->drive_kp = drive_kp;
  this->drive_ki = drive_ki;
  this->drive_kd = drive_kd;
  this->drive_starti = drive_starti;
} 

void Drive::set_heading_constants(float heading_max_voltage, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
  this->heading_max_voltage = heading_max_voltage;
  this->heading_kp = heading_kp;
  this->heading_ki = heading_ki;
  this->heading_kd = heading_kd;
  this->heading_starti = heading_starti;
}

void Drive::set_swing_constants(float swing_max_voltage, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  this->swing_max_voltage = swing_max_voltage;
  this->swing_kp = swing_kp;
  this->swing_ki = swing_ki;
  this->swing_kd = swing_kd;
  this->swing_starti = swing_starti;
} 

void Drive::set_turn_exit_conditions(float turn_settle_error, float turn_settle_time, float turn_timeout){
  this->turn_settle_error = turn_settle_error;
  this->turn_settle_time = turn_settle_time;
  this->turn_timeout = turn_timeout;
}

void Drive::set_drive_exit_conditions(float drive_settle_error, float drive_settle_time, float drive_timeout){
  this->drive_settle_error = drive_settle_error;
  this->drive_settle_time = drive_settle_time;
  this->drive_timeout = drive_timeout;
}

void Drive::set_swing_exit_conditions(float swing_settle_error, float swing_settle_time, float swing_timeout){
  this->swing_settle_error = swing_settle_error;
  this->swing_settle_time = swing_settle_time;
  this->swing_timeout = swing_timeout;
}

float Drive::get_absolute_heading(){ 
  return( zero_to_360( IMU->get_rotation()) ); 
}

float Drive::get_left_position(){
    float encoder_position = 0 ;
    std::vector<double> left_positions = leftMotors->get_positions();
    for(double p : left_positions) {
        encoder_position += p;
    }
    return( encoder_position*drive_in_to_deg_ratio);
}
float Drive::get_right_position(){
    float encoder_position = 0 ;
    std::vector<double> left_positions = leftMotors->get_positions();
    for(double p : left_positions) {
        encoder_position += p;
    }
    return( encoder_position*drive_in_to_deg_ratio);
}


void Drive::turn_to_angle(float angle){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout){
  turn_to_angle(angle, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
}

void Drive::turn_to_angle(float angle, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti){
  desired_heading = angle;
  PID turnPID(neg_180_to_180(angle - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
  while(turnPID.settled() == false){
    float error = neg_180_to_180(angle - get_absolute_heading());
    float output = turnPID.calculate(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    drive_voltage(output, -output);
	pros::delay(10);
  }
  leftMotors->brake();
  rightMotors->brake();
  }

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

void Drive::drive_distance(float distance, float heading, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
    desired_heading = heading;
    PID drivePID(distance, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
    PID headingPID(neg_180_to_180(heading - get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
    float start_average_position = (get_left_position()+get_right_position())/2.0;
    float average_position = start_average_position;
    while(drivePID.settled() == false){
        average_position = (get_left_position()+get_right_position())/2.0;
        float drive_error = distance+start_average_position-average_position;
        float heading_error = neg_180_to_180(heading - get_absolute_heading());
        float drive_output = drivePID.calculate(drive_error);
        float heading_output = headingPID.calculate(heading_error);
        
        drive_output = clamp(drive_output, -drive_max_voltage, drive_max_voltage);
        heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);
        
        drive_voltage(drive_output+heading_output, drive_output-heading_output);
        pros::delay(10);
    }
    leftMotors->brake();
    rightMotors->brake();
}

void Drive::left_swing_to_angle(float angle){
  left_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::left_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  desired_heading = angle;
  PID swingPID(neg_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.settled() == false){
    float error = neg_180_to_180(angle - get_absolute_heading());
    float output = swingPID.calculate(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    leftMotors->move(output);
    rightMotors->brake();
    pros::delay(10);
  }
    leftMotors->brake();
    rightMotors->brake();
}

void Drive::right_swing_to_angle(float angle){
  right_swing_to_angle(angle, swing_max_voltage, swing_settle_error, swing_settle_time, swing_timeout, swing_kp, swing_ki, swing_kd, swing_starti);
}

void Drive::right_swing_to_angle(float angle, float swing_max_voltage, float swing_settle_error, float swing_settle_time, float swing_timeout, float swing_kp, float swing_ki, float swing_kd, float swing_starti){
  desired_heading = angle;
  PID swingPID(neg_180_to_180(angle - get_absolute_heading()), swing_kp, swing_ki, swing_kd, swing_starti, swing_settle_error, swing_settle_time, swing_timeout);
  while(swingPID.settled() == false){
    float error = neg_180_to_180(angle - get_absolute_heading());
    float output = swingPID.calculate(error);
    output = clamp(output, -turn_max_voltage, turn_max_voltage);
    rightMotors->move(output);
    leftMotors->brake();
    pros::delay(10);
  }
    leftMotors->brake();
    rightMotors->brake();
}


// void Drive::position_track(){
//   while(1){
//     odom.update_position(get_ForwardTracker_position(), get_SidewaysTracker_position(), get_absolute_heading());
//     task::sleep(5);
//   }
// }

// void Drive::set_heading(float orientation_deg){
//   Gyro.setRotation(orientation_deg*gyro_scale/360.0, deg);
// }

// void Drive::set_coordinates(float X_position, float Y_position, float orientation_deg){
//   odom.set_position(X_position, Y_position, orientation_deg, get_ForwardTracker_position(), get_SidewaysTracker_position());
//   set_heading(orientation_deg);
//   odom_task = task(position_track_task);
// }

// float Drive::get_X_position(){
//   return(odom.X_position);
// }

// float Drive::get_Y_position(){
//   return(odom.Y_position);
// }

// void Drive::drive_to_point(float X_position, float Y_position){
//   drive_to_point(X_position, Y_position, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
// }

// void Drive::drive_to_point(float X_position, float Y_position, float drive_max_voltage, float heading_max_voltage){
//   drive_to_point(X_position, Y_position, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
// }

// void Drive::drive_to_point(float X_position, float Y_position, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout){
//   drive_to_point(X_position, Y_position, drive_max_voltage, heading_max_voltage, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
// }

// void Drive::drive_to_point(float X_position, float Y_position, float drive_max_voltage, float heading_max_voltage, float drive_settle_error, float drive_settle_time, float drive_timeout, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float heading_kp, float heading_ki, float heading_kd, float heading_starti){
//   PID drivePID(hypot(X_position-get_X_position(),Y_position-get_Y_position()), drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
//   PID headingPID(reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()))-get_absolute_heading()), heading_kp, heading_ki, heading_kd, heading_starti);
//   while(drivePID.is_settled() == false){
//     float drive_error = hypot(X_position-get_X_position(),Y_position-get_Y_position());
//     float heading_error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position()))-get_absolute_heading());
//     float drive_output = drivePID.compute(drive_error);

//     float heading_scale_factor = cos(to_rad(heading_error));
//     drive_output*=heading_scale_factor;
//     heading_error = reduce_negative_90_to_90(heading_error);
//     float heading_output = headingPID.compute(heading_error);
    
//     if (drive_error<drive_settle_error) { heading_output = 0; }

//     drive_output = clamp(drive_output, -fabs(heading_scale_factor)*drive_max_voltage, fabs(heading_scale_factor)*drive_max_voltage);
//     heading_output = clamp(heading_output, -heading_max_voltage, heading_max_voltage);

//     drive_with_voltage(drive_output+heading_output, drive_output-heading_output);
//     task::sleep(10);
//   }
//   desired_heading = get_absolute_heading();
//   DriveL.stop(hold);
//   DriveR.stop(hold);
// }

// void Drive::turn_to_point(float X_position, float Y_position){
//   turn_to_point(X_position, Y_position, 0, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
// }

// void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg){
//   turn_to_point(X_position, Y_position, extra_angle_deg, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
// }

// void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout){
//   turn_to_point(X_position, Y_position, extra_angle_deg, turn_max_voltage, turn_settle_error, turn_settle_time, turn_timeout, turn_kp, turn_ki, turn_kd, turn_starti);
// }

// void Drive::turn_to_point(float X_position, float Y_position, float extra_angle_deg, float turn_max_voltage, float turn_settle_error, float turn_settle_time, float turn_timeout, float turn_kp, float turn_ki, float turn_kd, float turn_starti){
//   PID turnPID(reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - get_absolute_heading()), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
//   while(turnPID.is_settled() == false){
//     float error = reduce_negative_180_to_180(to_deg(atan2(X_position-get_X_position(),Y_position-get_Y_position())) - get_absolute_heading() + extra_angle_deg);
//     float output = turnPID.compute(error);
//     output = clamp(output, -turn_max_voltage, turn_max_voltage);
//     drive_with_voltage(output, -output);
//     task::sleep(10);
//   }
//   desired_heading = get_absolute_heading();
//   DriveL.stop(hold);
//   DriveR.stop(hold);
// }