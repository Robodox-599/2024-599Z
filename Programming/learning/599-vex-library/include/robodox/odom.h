#include "robodox/PRELUDE.hpp"
class chassisOdom{
    private:
        double wheel_diameter;
        double wheel_ratio;
        double trackWidth;
        float drive_in_to_deg_ratio;
        double start_heading;
        void odometry();  
        double x = 0;
        double y = 0;
    public: 
        pros::Motor_Group& leftMotors;
        pros::Motor_Group& rightMotors;
        pros::IMU& IMU;
        chassisOdom(
        pros::Motor_Group& leftMotors,
        pros::Motor_Group& rightMotors,
        pros::IMU& IMU,
        double wheel_diameter,
        double wheel_ratio, 
        double trackWidth,
        double start_heading);
        float get_absolute_heading();
        float get_left_position_in();
        float get_right_position_in();
        float distance_encoder_position();
        float yVal();
        float xVal();
        float resetEncoders();
        float lcdOut();
        float xCalc(float change_in_distance);
        float yCalc(float change_in_distance);
        float updatePos(float previous_distance_traveled);
};

