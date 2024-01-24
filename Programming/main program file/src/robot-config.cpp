#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LB = motor(PORT19, ratio6_1, true);
motor RB = motor(PORT11, ratio6_1, false);
motor LF = motor(PORT18, ratio6_1, true);
motor RF = motor(PORT3, ratio6_1, false);
motor kickerMotor = motor(PORT20, ratio36_1, true);
motor intakeMotor = motor(PORT12, ratio6_1, false);
digital_out flapsPistonLeft = digital_out(Brain.ThreeWirePort.A);
digital_out flapsPistonRight = digital_out(Brain.ThreeWirePort.B);
limit kickerSwitch = limit(Brain.ThreeWirePort.C);
digital_out climbPistons = digital_out(Brain.ThreeWirePort.D);
motor LM = motor(PORT10, ratio6_1, true);
motor RM = motor(PORT13, ratio6_1, false);
inertial IMU = inertial(PORT14);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}