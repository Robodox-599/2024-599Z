using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LB;
extern motor RB;
extern motor LF;
extern motor RF;
extern motor kickerMotor;
extern motor intakeMotor;
extern digital_out flapsPistonLeft;
extern digital_out flapsPistonRight;
extern limit kickerSwitch;
extern digital_out climbPistons;
extern motor LM;
extern motor RM;
extern inertial IMU;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );