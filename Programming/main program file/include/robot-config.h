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
extern digital_out flapsPiston;
extern digital_out climbPiston;
extern motor LM;
extern motor RM;
extern inertial IMU;
extern rotation rot;
extern distance distanceSensor;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );