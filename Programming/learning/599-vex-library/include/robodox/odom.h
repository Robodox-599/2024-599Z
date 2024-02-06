#include "robodox/PRELUDE.hpp"
class chassisOdom{
    private:
        double wheel_diameter;
        double wheel_ratio;
        double trackWidth;
        float drive_in_to_deg_ratio;
        double start_heading;
        double x = 0;
        double y = 0;
    public: 
        std::shared_ptr<pros::Motor> leftMotor;
        std::shared_ptr<pros::Motor> rightMotor;
        std::shared_ptr<pros::IMU> IMU;
        chassisOdom(
        const pros::Motor& leftMotor,
        const pros::Motor& rightMotor,
        const pros::IMU& IMU,
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
        void resetEncoders();
        void lcdOut();
        void xCalc(float change_in_distance);
        void yCalc(float change_in_distance);
        void odometry();
};

