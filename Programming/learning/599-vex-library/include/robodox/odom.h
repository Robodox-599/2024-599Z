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
        double previous_distance_traveled = 0;
    public: 
        std::shared_ptr<pros::Motor_Group> leftMotors;
        std::shared_ptr<pros::Motor_Group> rightMotors;
        std::shared_ptr<pros::IMU> IMU;
        chassisOdom(
        const pros::Motor_Group& leftMotors,
        const pros::Motor_Group& rightMotors,
        const pros::IMU& IMU,
        double wheel_diameter,
        double wheel_ratio, 
        double trackWidth,
        double start_heading);
        float get_absolute_heading();
        float average_encoder_position();
        float yVal();
        float xVal();
        float distance_traveled();
        void resetOdom();
        void lcdOut();
        void xCalc(float change_in_distance);
        void yCalc(float change_in_distance);
        void odometry();
};

