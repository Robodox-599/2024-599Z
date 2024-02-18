#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LB = motor(PORT10, ratio6_1, true);
motor RB = motor(PORT3, ratio6_1, false);
motor LF = motor(PORT7, ratio6_1, true);
motor RF = motor(PORT2, ratio6_1, false);
motor kickerMotor = motor(PORT8, ratio36_1, false);
motor intakeMotor = motor(PORT11, ratio6_1, false);
digital_out flapsPiston = digital_out(Brain.ThreeWirePort.A);
digital_out climbPiston = digital_out(Brain.ThreeWirePort.B);
motor LM = motor(PORT9, ratio6_1, true);
motor RM = motor(PORT1, ratio6_1, false);
inertial IMU = inertial(PORT12);
rotation rot = rotation(PORT4, false);
distance distanceSensor = distance(PORT21);

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