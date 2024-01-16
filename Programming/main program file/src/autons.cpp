#include "vex.h"


// constants and other useful functions for auton

/*==========================================================================================================*/
/*  REMINDER- RETUNE THESE ALL FOR DRIVEBASE WHEN RPM, GEAR RATIO, WHEEL SIZE, OR EVEN WEIGHT, ARE CHANGED  */
/*==========================================================================================================*/
void default_constants(){
  chassis.set_constants(  
          /* max voltage | kp constants | ki constants | kd constants |  start ki constants */
/* turn  */    12        ,      .6      ,     .03      ,      6       ,         15          ,
/* drive */    12        ,      1.5     ,       0      ,      10      ,         0           ,
/* swing */    12        ,      .3      ,     .001     ,      2       ,         15          , 
/*heading*/    12        ,      .4      ,       0      ,      1       ,         0           ); 
  chassis.set_exit_conditions(
         /* settle error   |     settle time    |   timeout   */
/*swing*/  1               ,        300         ,     2000    ,
/*turn*/   1               ,        250         ,     1500    ,
/*drive*/  1.5             ,        250         ,     4000    );
}
// autos will start below 