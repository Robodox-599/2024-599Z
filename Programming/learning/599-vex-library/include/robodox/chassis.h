#include "robodox/PRELUDE.hpp"
class Drive{
    private:
        double wheel_diameter;
        double wheel_ratio;
        int gyro_scale;
        double trackWidth;
        int rpm;
    public: 
        pros::Motor_Group& leftMotors;
        pros::Motor_Group& rightMotors;
        pros::IMU& IMU;
        Drive::Drive(pros::Motor_Group& leftMotors, pros::Motor_Group& rightMotors, pros::IMU& IMU,  double wheel_diameter, double wheel_ratio, int gyro_scale, double trackWidth, int rpm);
};

