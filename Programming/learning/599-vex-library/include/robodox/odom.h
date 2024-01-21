#include "robodox/PRELUDE.hpp"
class Drive{
    private:
        double wheel_diameter;
        double wheel_ratio;
        int gyro_scale;
        double trackWidth;
        int rpm;
        float drive_in_to_deg_ratio;
        double start_heading;
    public: 
        pros::Motor_Group& leftMotors;
        pros::Motor_Group& rightMotors;
        pros::IMU& IMU;
        Drive::Drive(pros::Motor_Group& leftMotors, pros::Motor_Group& rightMotors, pros::IMU& IMU,  double wheel_diameter, double wheel_ratio, int gyro_scale, double trackWidth, double start_heading, int rpm);
        void drive_with_voltage(float leftVoltage, float rightVoltage);
        /*uses the gyroscope to get the absolute heading of the robot. */
        float get_absolute_heading();
        /*Uses built in motor encoders to find the input degrees of 
        the left motor group*/
        float get_left_position_in();
        /*Uses built in motor encoders to find the input degrees of 
        the right motor group*/
        float get_right_position_in();
        float distance_encoder_position();
        void odometry();
        float coordinatesX();
        float coordinatesY();
};

