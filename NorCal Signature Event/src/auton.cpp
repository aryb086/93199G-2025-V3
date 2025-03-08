#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "robot.h"
#include <string>

void red_solo_awp(){
    

}

void blue_solo_awp(){
    armSensor.set_position(2950);
    lcd::print(7, "Blue Solo AWP");

    rotationPosition = -1;

    chassis.setPose(61, 10, 145);


    //scoring preload on alliance stake
    pros::delay(300);
    rotationPosition = 5;
    pros::delay(400);
    rotationPosition = 3;
    pros::delay(400);

    //clamping first mogo
    chassis.moveToPoint(22,24, 2000, {.forwards = false, .maxSpeed = 80}, false);
    pros::delay(50); //*********** */
    clamp.set_value(HIGH);
    pros::delay(150);

    //getting 2 rings in middle and scoring it
    intake.move(100);
    chassis.turnToPoint(3, 45 , 500);
    chassis.moveToPoint(-2.25,42, 800, {.forwards = true, .maxSpeed = 80}, false);
    //chassis.moveToPoint(-2.25,42, 800, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(2,38, 800, {.forwards = false, .maxSpeed = 80}, false);
    chassis.moveToPoint(2,50, 800, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(0, 50,500);
    chassis.moveToPoint(-2,59, 800, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(400);
    chassis.moveToPoint(1,53, 800, {.forwards = false, .maxSpeed = 80}, false);


    //getting 3rd ring in first mogo
    chassis.turnToPoint(23, 49 , 500);
    pros::delay(50); //****** */
    chassis.moveToPoint(23,49, 1000, {.forwards = true, .maxSpeed = 100}, false);
    //pros::delay(200);

    
    //getting 1st ring to collect on second mogo
    intake.move(127);
    intakePiston.set_value(HIGH);
    chassis.turnToPoint(41 , 25 , 500);
    pros::delay(50); //******* */
    chassis.moveToPoint(41,25, 1000, {.forwards = true, .maxSpeed = 127}, false);
    clamp.set_value(LOW);
    pros::delay(50); //******* */
    chassis.moveToPoint(41,-15, 1300, {.forwards = true, .maxSpeed = 60}, false);
    intakePiston.set_value(LOW);
    chassis.moveToPoint(41,0, 1000, {.forwards = false, .maxSpeed = 80}, false);
    pros::delay(200);
    intake.move(0);
    pros::delay(200);

    // clamping second mogo and scoring 1 ring
    chassis.turnToPoint(57, -1 , 700);
    pros::delay(50); //******* */
    chassis.moveToPoint(19,-17, 1000, {.forwards = false, .maxSpeed = 80}, false);
    pros::delay(200);
    clamp.set_value(HIGH);
    pros::delay(300);
    intake.move(127);
    chassis.moveToPoint(18 ,0, 1000, {.forwards = true, .maxSpeed = 127}, false);
    intake.move(0);

}


void red_pos(){
    lcd::print(7, "Red Pos");

    std::string target = "Red";
    int rotationPosition = -1;
    //Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    //Task colorSortTask(colorSort, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");


    chassis.setPose(-49, -59, 90);
	// clamp.set_value(HIGH);

    /////////////////// START OF SECOND AUTON PATH ///////////////////////////
    chassis.moveToPoint(-9,-59, 1000, {.forwards = true, .maxSpeed = 127}, false);
    chassis.turnToPoint(10, -50 , 500);
    doinker2.set_value(HIGH);
    chassis.moveToPoint(-40,-59, 1000, {.forwards = false, .maxSpeed = 127}, false);
    doinker2.set_value(LOW);
    chassis.turnToPoint(-65, -59 , 1000);
    pros::delay(500);
    chassis.moveToPoint(-13,-59, 1000, {.forwards = false, .maxSpeed = 60}, false);
    pros::delay(300);
    clamp.set_value(HIGH);
    intake.move(127);
    pros::delay(1000);

    chassis.turnToPoint(-20, -36 , 500);
    clamp.set_value(LOW);
    chassis.moveToPoint(-25,-36, 1000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(200);
    intake.brake();
    //chassis.turnToPoint(-23, -69 , 1000, {.forwards = false});
    chassis.moveToPoint(-23,-23, 1000, {.forwards = false, .maxSpeed = 80}, false);
    delay(400);
    clamp.set_value(HIGH);
    delay(400);
    intake.move(127);
    intakePiston.set_value(HIGH);
    chassis.turnToPoint(-53, 0 , 1000);
    chassis.moveToPoint(-53,4, 1000, {.forwards = true, .maxSpeed = 60}, false);
    chassis.turnToPoint(-23, -20 , 1000);
    chassis.moveToPoint(-23,-20, 1000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(-14, -10 , 1000);
    chassis.moveToPoint(-14, -10, 1000, {.forwards = true, .maxSpeed = 80}, false);
    // rotationPosition = 5;
    pros::delay(100);

    //////////////////// END OF SECOND AUTON PATH ///////////////////////////////////



    //////////////////// START OF FIRST AUTON PATH //////////////////////////////////
    // rotationPosition = 0;
    // chassis.moveToPoint(-10.5,-51.35, 1000, {.forwards = true, .maxSpeed = 90}, false);
    // intake.move(-60);
    // pros::delay(100);
    // rotationPosition = 5;
    // pros::delay(800);
    // chassis.turnToPoint(0, -80, 500);
    // chassis.moveToPoint(-15, -60, 2000, {.forwards = false}, false);
    // rotationPosition = 3;
    // pros::delay(500);

    // // rushing the mogo, lady browning it and tipping it
    // rotationPosition = 0;
    // intake.move(127);
    // chassis.moveToPoint(-14,-59, 1000, {.forwards = true, .maxSpeed = 100}, false);
    // pros::delay(100);
    // chassis.turnToHeading(74, 100);
    // chassis.moveToPoint(-10.5,-51.35, 1000, {.forwards = true, .maxSpeed = 90}, false);
    // intake.move(-60);
    // pros::delay(100);
    // rotationPosition = 5;
    // pros::delay(800);
    // chassis.turnToPoint(0, -80, 500);
    // chassis.moveToPoint(-15, -60, 2000, {.forwards = false}, false);
    // rotationPosition = 3;
    // pros::delay(500);


    // //getting first ring
    
    // intake.move(127);
    // chassis.turnToPoint(-21, -23, 500);
    // pros::delay(200);
    // intake.move(127);
    // chassis.moveToPoint(-25,-35, 500, {.forwards = true, .maxSpeed = 80}, false);
    // pros::delay(100);
    // intake.brake();

    // // getting mogo, clamping, and scoring one ring
    // chassis.turnToPoint(-28, -69, 800);
    // chassis.moveToPoint(-18 ,-25, 800, {.forwards = false, .maxSpeed = 80}, false);
    // pros::delay(200);
    // clamp.set_value(HIGH);
    // pros::delay(500);
    // intake.move(127);
    
    // //going to ladder
    // chassis.turnToPoint(-23, -19, 500);
    // chassis.moveToPoint(-19,-10,500, {.forwards = true, .maxSpeed = 90}, false);

    // // doinkering corner rings and scoring 2 rings
    // chassis.turnToPoint(-23, -64, 1000);
    // chassis.moveToPoint(-23,-64, 2000, {.forwards = true, .maxSpeed = 100}, false);
    // chassis.turnToPoint(-66, -67, 1000);
    // doinker2.set_value(HIGH);
    // chassis.moveToPoint(-50,-66, 2000, {.forwards = true, .maxSpeed = 127}, false);
    // chassis.turnToPoint(-59, 0, 500, {.forwards = true, .maxSpeed = 80}, false);
    // pros::delay(200);
    // doinker2.set_value(LOW);
    // chassis.turnToPoint(-65, -58, 500);
    // chassis.moveToPoint(-65,-58, 1000, {.forwards = true, .maxSpeed =127}, false);
    // chassis.turnToPoint(-66, -37, 500);
    // chassis.moveToPoint(-66,-37, 1000, {.forwards = true, .maxSpeed = 127}, false);

    // //going to ladder
    // chassis.turnToPoint(-23, -19, 500);
    // chassis.moveToPoint(-19,-14,500, {.forwards = true, .maxSpeed = 90}, false);
    // rotationPosition = 2;

    // /////////////////////// END OF FIRST AUTON PATH ///////////////////////


    // // colorSortTask.remove();

    //ladybrownTask.remove();
    
}


void red_neg(){
    lcd::print(7, "Red Neg");

    int rotationPosition = -1;
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");


    chassis.setPose(-58, 12, 225);
	// clamp.set_value(HIGH);

    // scoring preload using lady brown

    // pros::delay(2000);

    rotationPosition = 0;
    pros::delay(200);
    intake.move(127);
    pros::delay(800);
    intake.move(-80);
    pros::delay(80);
    rotationPosition = 5;
    pros::delay(500);
    rotationPosition = 3;
    pros::delay(100);
    intake.brake();
    

    // clamping first mogo
    chassis.turnToPoint(-68, -8, 500);
    chassis.moveToPoint(-25,17, 1200, {.forwards = false, .maxSpeed = 80}, false);
    pros::delay(400);
    clamp.set_value(HIGH);
    pros::delay(200);
    intake.move(127);

    ladybrownTask.remove();


    //scoring first ring onto mogo
    chassis.turnToPoint(-18, 52, 500);
    chassis.moveToPoint(-18,52, 1000, {.forwards = true, .maxSpeed = 90}, false);

    // scoring 2nd & 3rd rings onto mogo
    // intake.move(127);
    chassis.turnToPoint(4, 44, 500);
    chassis.moveToPoint(4,44, 1500, {.forwards = true, .maxSpeed = 90}, false);
    chassis.moveToPoint(-5, 37, 1000, {.forwards = false, .maxSpeed = 90}, false);
    chassis.turnToPoint(5, 32.5, 500);
    chassis.moveToPoint(5,32.5, 1000, {.forwards = true, .maxSpeed = 90}, false);

    // touching ladder
    // chassis.turnToPoint(-24, 13, 1000);
    chassis.moveToPoint(-24,13, 2000, {.forwards = false, .maxSpeed = 110}, false);
    chassis.turnToPoint(-44, -10, 1000);
    intakePiston.set_value(HIGH);
    chassis.moveToPoint(-44,-10, 1000, {.forwards = true, .maxSpeed = 110}, false);
    // rotationPosition = 2;
    pros::delay(200);
    intakePiston.set_value(LOW);
    chassis.turnToPoint(0, -10, 1000);
    chassis.moveToPoint(-20,-10, 3000, {.forwards = true, .maxSpeed = 80}, false);

    

    // // scoring 3rd ring onto mogo
    // chassis.turnToPoint(-23, 46, 1000);
    // chassis.moveToPoint(-23,46, 2000, {.forwards = true, .maxSpeed = 70}, false);

    // // scoring 4th ring onto mogo
    // chassis.turnToPoint(-66, 66, 1000);
    // chassis.moveToPoint(-66,66, 2000, {.forwards = true, .maxSpeed = 70}, false);
    // chassis.moveToPoint(-57,59, 2000, {.forwards = false, .maxSpeed = 70}, false);

    // // scoring 5th ring onto mogo
    // intakePiston.set_value(HIGH);
    // chassis.turnToPoint(-46, 0, 1000);
    // chassis.moveToPoint(-46,0, 1000, {.forwards = true, .maxSpeed = 70}, false);
    



}

void blue_pos(){
    lcd::print(7, "Blue Pos");

    chassis.setPose(57, -61, 90);


    // rushing the mogo, lady browning it and tipping it
    chassis.moveToPoint(14,-57, 1000, {.forwards = false, .maxSpeed = 127}, false);
    pros::delay(100);
    chassis.turnToPoint(0, -47, 100, {.forwards = true, .maxSpeed = 127}, false);
    doinker2.set_value(HIGH);
    chassis.moveToPoint(48,-60, 1000, {.forwards = true, .maxSpeed = 127}, false);
    doinker2.set_value(LOW);
    chassis.turnToPoint(69, -65, 200, {.forwards = true, .maxSpeed = 127}, false);
    chassis.moveToPoint(37,-54, 700, {.forwards = true, .maxSpeed = 127}, false);
    clamp.set_value(HIGH);
    intake.move(127);
    chassis.turnToPoint(66, -66, 100, {.forwards = true, .maxSpeed = 127}, false);
    chassis.moveToPoint(66,-66, 800, {.forwards = true, .maxSpeed = 100}, false);
    chassis.moveToPoint(56,-59, 200, {.forwards = true, .maxSpeed = 100}, false);
    chassis.turnToPoint(23, -47, 200, {.forwards = true, .maxSpeed = 127}, false);
    clamp.set_value(LOW);
    chassis.moveToPoint(21,-45, 1000, {.forwards = true, .maxSpeed = 100}, false);
    intake.move(0);
    chassis.turnToPoint(21, -69, 300, {.forwards = true, .maxSpeed = 127}, false);




    pros::delay(100);
    // doinker.set_value(HIGH);
    rotationPosition = 5;
    pros::delay(1500);
    chassis.moveToPoint(20,-55, 1000, {.forwards = false, .maxSpeed = 90}, false);
    chassis.turnToPoint(-5, -61, 1500);
    pros::delay(2000);
    rotationPosition = 3;
    pros::delay(500);


    // // getting first ring

    // chassis.turnToPoint(27, -39, 500);
    
    // intake.move(127);
    // chassis.moveToPoint(27,-33, 500, {.forwards = true, .maxSpeed = 70}, false);
    // pros::delay(100);
    // intake.brake();

    // // getting mogo, clamping, and scoring one ring
    // chassis.turnToPoint(28, -69, 800);
    // chassis.moveToPoint(18 ,-20, 800, {.forwards = false, .maxSpeed = 70}, false);
    // pros::delay(1000);
    // // doinker.set_value(LOW);
    // // pros::delay(300);
    // clamp.set_value(HIGH);
    // pros::delay(1000);
    // intake.move(127);
    // pros::delay(600);
    
    // //going to ladder
    // chassis.turnToPoint(9, -15, 500);
    // chassis.moveToPoint(9,-15,500, {.forwards = true, .maxSpeed = 90}, false);
    // // rotationPosition = 2;
    // pros::delay(500);

    // // // doinkering corner rings and scoring 2 rings
    // // chassis.turnToPoint(-23, -64, 1000);
    // // chassis.moveToPoint(-23,-64, 2000, {.forwards = true, .maxSpeed = 100}, false);
    // // chassis.turnToPoint(-66, -67, 1000);
    // // doinker2.set_value(HIGH);
    // chassis.moveToPoint(-50,-66, 2000, {.forwards = true, .maxSpeed = 127}, false);
    // chassis.turnToPoint(-59, 0, 500, {.forwards = true, .maxSpeed = 80}, false);
    // pros::delay(200);
    // doinker2.set_value(LOW);
    // chassis.turnToPoint(-65, -58, 500);
    // chassis.moveToPoint(-65,-58, 1000, {.forwards = true, .maxSpeed =127}, false);
    // chassis.turnToPoint(-66, -37, 500);
    // chassis.moveToPoint(-66,-37, 1000, {.forwards = true, .maxSpeed = 127}, false);

    // //going to ladder
    // chassis.turnToPoint(-23, -19, 500);
    // chassis.moveToPoint(-19,-14,500, {.forwards = true, .maxSpeed = 90}, false);
    // rotationPosition = 2;

    // colorSortTask.remove();

    // ladybrownTask.remove();
}

void blue_neg(){

    lcd::print(7, "Blue Neg");

    int rotationPosition = -1;
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    // pros::delay(3000);


    chassis.setPose(58, 12, 135);
	// clamp.set_value(HIGH);

    // scoring preload using lady brown
    rotationPosition = 0;
    pros::delay(200);
    intake.move(127);
    pros::delay(1200);
    intake.move(-80);
    pros::delay(30);
    rotationPosition = 5;
    pros::delay(500);
    rotationPosition = 3;
    pros::delay(100);
    intake.brake();


    // clamping first mogo
    chassis.turnToPoint(68, -8, 500);
    chassis.moveToPoint(11,20, 800, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(800);
    clamp.set_value(HIGH);
    pros::delay(200);
    intake.move(127);

    ladybrownTask.remove();


    //scoring first ring onto mogo
    chassis.turnToPoint(6, 63, 500);
    chassis.moveToPoint(6,63, 1000, {.forwards = true, .maxSpeed = 70}, false);

    // scoring 2nd & 3rd rings onto mogo
    // intake.move(127);
    chassis.turnToPoint(-10, 32, 500);
    chassis.moveToPoint(-10,32, 1500, {.forwards = true, .maxSpeed = 50}, false);
    chassis.moveToPoint(5,37, 1000, {.forwards = false, .maxSpeed = 70}, false);
    chassis.turnToPoint(-8, 25, 500);
    chassis.moveToPoint(-8,25, 1000, {.forwards = true, .maxSpeed = 60}, false);

    // touching ladder
    // chassis.turnToPoint(24, 13, 1000);
    // chassis.moveToPoint(24,13, 2000, {.forwards = false, .maxSpeed = 100}, false);
    // chassis.turnToPoint(15, 10, 1000);
    // chassis.moveToPoint(6,-3, 3000, {.forwards = true, .maxSpeed = 100}, false);
    // // rotationPosition = 1;
    // pros::delay(200);
    chassis.moveToPoint(24,13, 2000, {.forwards = false, .maxSpeed = 110}, false);
    chassis.turnToPoint(44, -10, 1000);
    intakePiston.set_value(HIGH);
    chassis.moveToPoint(44,-10, 1000, {.forwards = true, .maxSpeed = 110}, false);
    // rotationPosition = 2;
    pros::delay(200);
    intakePiston.set_value(LOW);
    chassis.turnToPoint(0, -20, 1000);
    chassis.moveToPoint(20,-20, 3000, {.forwards = true, .maxSpeed = 80}, false);

    // // scoring 3rd ring onto mogo
    // chassis.turnToPoint(-23, 46, 1000);
    // chassis.moveToPoint(-23,46, 2000, {.forwards = true, .maxSpeed = 70}, false);

    // // scoring 4th ring onto mogo
    // chassis.turnToPoint(-66, 66, 1000);
    // chassis.moveToPoint(-66,66, 2000, {.forwards = true, .maxSpeed = 70}, false);
    // chassis.moveToPoint(-57,59, 2000, {.forwards = false, .maxSpeed = 70}, false);

    // // scoring 5th ring onto mogo
    // intakePiston.set_value(HIGH);
    // chassis.turnToPoint(-46, 0, 1000);
    // chassis.moveToPoint(-46,0, 1000, {.forwards = true, .maxSpeed = 70}, false);
    


}

void skills1(){
    // skills
    int rotationPosition = -1;
    std::string target = "Red";
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    //Task colorSortTask(colorSort, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");

    chassis.setPose(0, 0, 0);
	// clamp.set_value(HIGH);
	intake.move(127);
	pros::delay(800);
	intake.brake();

	//go forward of alliance stake
	chassis.moveToPoint(0,15, 1000, {.forwards = true, .maxSpeed = 90}, false);

	//pick up first mogo
    chassis.moveToPoint(30, 15, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(100);
	clamp.set_value(HIGH);
	pros::delay(300);

	//pick up first ring and put in lady brown
    rotationPosition = 0;
    intake.move(127);
	chassis.moveToPoint(24,40, 3000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(500);
	chassis.moveToPoint(45,64.5, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(65, 64.5, 1000);   

    //score on high stake
    intake.move(-60);
    pros::delay(400);
    rotationPosition = 1;
    intake.move(127);
    chassis.moveToPoint(70, 64.5, 1000, {.forwards = true, .maxSpeed = 60}, false);
    rotationPosition = 5;
    pros::delay(800);
    intake.move(127);
    pros::delay(300);
    chassis.moveToPoint(53,64.5, 3000, {.forwards = false, .maxSpeed = 80}, false);
    rotationPosition = 3;
    pros::delay(200);
    rotationPosition = -1;

    //grab 3rd ring
    intake.move(127);
    chassis.turnToPoint(46, 92, 1000);
    chassis.moveToPoint(46, 92, 2000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(800);

    //put goal in corner with 6 rings
    chassis.moveToPoint(50,6, 3000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(600);
    chassis.moveToPoint(50,-4, 3000, {.forwards = true, .maxSpeed = 60}, false);
    delay(500);
    chassis.turnToPoint(65, 20, 1000);
    chassis.moveToPoint(65, 20, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(300);
    chassis.moveToPoint(60, 0, 2000, {.forwards = false}, false);
    pros::delay(200);
    clamp.set_value(LOW);

    //grab second ring for alliance stake
    chassis.turnToPoint(50, 90, 1000);
    chassis.moveToPoint(50, 90, 3000, {.forwards = true, .maxSpeed = 120}, true);
    
    //grab mogo with blue ring
    chassis.moveToPoint(20, 130, 2000, {.forwards = false, .maxSpeed = 70}, false);
    clamp.set_value(HIGH);
    pros::delay(100);

    //put in corner
    chassis.turnToPoint(70, 140, 1000, {.forwards = true, .maxSpeed = 90});
    doinker2.set_value(HIGH);
    chassis.moveToPoint(60, 130, 3000, {.forwards = true, .maxSpeed = 90}, false);
    intake.move(0);
    chassis.turnToPoint(90, 150, 1000, {.forwards = false, .maxSpeed = 70});
    pros::delay(200);
    doinker2.set_value(LOW);
    chassis.moveToPoint(70, 130, 1000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(LOW);
    pros::delay(200);
    

    //score on red alliance stake
    chassis.moveToPoint(30, 115, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.moveToPoint(17, 115, 3000, {.forwards = false, .maxSpeed = 70}, false);
    delay(200);
    clamp.set_value(HIGH);
    delay(400);
    intake.move(127);

    //filling up 3rd goal
    chassis.moveToPoint(40, 100, 4000, {.forwards = true}, false);
    chassis.moveToPoint(40, 85, 4000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(-36, 9, 1000);
    chassis.moveToPoint(-36, 9, 4000, {.forwards = true, .maxSpeed = 90}, false);
    delay(400);
    chassis.turnToPoint(-33, -5, 1000);
    chassis.moveToPoint(-33, -5, 4000, {.forwards = true, .maxSpeed = 60}, false);
    delay(800);
    //colorSortTask.remove();
    chassis.turnToPoint(-55, 8, 1000);
    chassis.moveToPoint(-55, 8, 2000, {.forwards = true, .maxSpeed = 60}, false);
    delay(600);
    chassis.moveToPoint(-60, 0, 1000, {.forwards = false, .maxSpeed = 80}, false);
    delay(300);
    clamp.set_value(LOW);
    intake.move(0);

    //get 4th goal
    chassis.moveToPoint(-40, 10, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-15, 13, 3000, {.forwards = false, .maxSpeed = 80}, false);
    delay(100);
    clamp.set_value(HIGH);
    delay(200);
    intake.move(127);

    //second high stake
    chassis.turnToPoint(-50, 32, 1000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-50, 32, 4000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(-50, 110, 1000);
   

    //fill up 4th goal put in corner
    chassis.moveToPoint(-50, 110, 4000, {.forwards = true, .maxSpeed = 80}, false);
    delay(300);
    chassis.moveToPoint(-50, 120, 4000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(300);
    intake.move(0);
    chassis.moveToPoint(-65, 130, 2000, {.forwards = false, .maxSpeed = 110}, false);
    clamp.set_value(LOW);
    pros::delay(400);
    chassis.moveToPoint(-40, 100, 4000, {.forwards = true, .maxSpeed = 80}, false);
}

void skills(){
    // skills
    rotationPosition = -1;
    targetColor = "None";
    //Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    //Task colorSortTask(colorSort, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");

    chassis.setPose(0, 0, 0);
	// clamp.set_value(HIGH);
	intake.move(127);
	pros::delay(500);
	intake.brake();

	//go forward of alliance stake
	chassis.moveToPoint(0,11, 1000, {.forwards = true, .maxSpeed = 127}, false);

	//pick up first mogo
    //chassis.turnToPoint(27, 11, 800, {.forwards = false, .maxSpeed = 100}, false);
    chassis.moveToPoint(29, 13, 3000, {.forwards = false, .maxSpeed = 110}, false);
    pros::delay(100);
	clamp.set_value(HIGH);
	pros::delay(100);

	//pick up first ring and put in goal and get second for ladybrown
    intake.move(127);
	chassis.moveToPoint(22,40, 3000, {.forwards = true, .maxSpeed = 120}, false);
	chassis.moveToPoint(48,64.5, 3000, {.forwards = true, .maxSpeed = 120}, false);
    rotationPosition = 0;
    chassis.turnToPoint(50, 95, 500); 
    chassis.moveToPoint(50, 95, 2000, {.forwards = true, .maxSpeed = 110}, false);

    //score on high stake
    pros::delay(200);
    chassis.moveToPoint(45,64, 3000, {.forwards = false, .maxSpeed = 110}, false);
    chassis.turnToPoint(70, 64, 600); 
    intake.move(-50);
    rotationPosition = 1;
    pros::delay(200);
    intake.move(100);
    chassis.moveToPoint(70, 64, 1000, {.forwards = true, .maxSpeed = 80}, false);
    rotationPosition = 5;
    pros::delay(600);
    chassis.moveToPoint(53,64, 3000, {.forwards = false, .maxSpeed = 110}, false);
    rotationPosition = 3;
    chassis.turnToPoint(53, 0, 800);

    //put goal in corner with 6 rings
    intake.move(127);
    chassis.moveToPoint(53,13, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.moveToPoint(53,-5, 3000, {.forwards = true, .maxSpeed = 110}, false);
    chassis.turnToPoint(68, 16, 600);
    chassis.moveToPoint(68, 16, 3000, {.forwards = true, .maxSpeed = 110}, false);
    chassis.moveToPoint(65, 0, 1000, {.forwards = false}, false);
    clamp.set_value(LOW);

    //grab second ring for alliance stake
    rotationPosition = 0;
    chassis.turnToPoint(50, 115, 600);
    chassis.moveToPoint(50, 115, 3000, {.forwards = true, .maxSpeed = 120}, false);
    
    //grab mogo with blue ring
    chassis.moveToPoint(30, 125, 2000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(HIGH);
    pros::delay(100);

    //put in corner
    chassis.turnToPoint(60, 130, 1000, {.forwards = true, .maxSpeed = 90}, true);
    doinker2.set_value(HIGH);
    chassis.moveToPoint(60, 130, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.turnToPoint(90, 150, 1000, {.forwards = false, .maxSpeed = 110});
    pros::delay(200);
    doinker2.set_value(LOW);
    chassis.moveToPoint(70, 130, 1000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(LOW);
    intake.move(0);
    

    //score on blue alliance stake
    chassis.moveToPoint(30, 115, 3000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.moveToPoint(11, 115, 3000, {.forwards = false, .maxSpeed = 80}, false);
    delay(100);
    clamp.set_value(HIGH);
    delay(100);
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(9, 121, 3000, {.forwards = true, .maxSpeed = 60}, false);
    intake.move(-60);
    rotationPosition = 5;
    pros::delay(800);
    chassis.moveToPoint(9, 115, 3000, {.forwards = false, .maxSpeed = 70}, false);
    rotationPosition = 3;

    //filling up 3rd goal
    intake.move(127);
    chassis.turnToPoint(38, 95, 1000);
    chassis.moveToPoint(38, 95, 4000, {.forwards = true, .maxSpeed = 90}, false);
    // chassis.turnToPoint(10, 60, 1000);
    // chassis.moveToPoint(10, 60, 4000, {.forwards = true, .maxSpeed = 90}, false);
    // delay(200);
    chassis.turnToPoint(-30, 13, 1000);
    chassis.moveToPoint(-30, 13, 4000, {.forwards = true, .maxSpeed = 100}, false);
    delay(200);
    chassis.turnToPoint(-53, 18, 1000);
    chassis.moveToPoint(-53, 18, 2000, {.forwards = true, .maxSpeed = 100}, false);
    delay(200);
    chassis.turnToPoint(-35, 2, 1000);
    chassis.moveToPoint(-35, 2, 4000, {.forwards = true, .maxSpeed = 100}, false);
    delay(300);
    //colorSortTask.remove();
    chassis.turnToPoint(-55, 0, 1000, {.forwards = false, .maxSpeed = 100}, false);
    clamp.set_value(LOW);
    intake.move(0);

    //get 4th goal
    chassis.moveToPoint(-40, 10, 3000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.moveToPoint(-10, 13, 3000, {.forwards = false, .maxSpeed = 80}, false);
    delay(100);
    clamp.set_value(HIGH);
    delay(200);
    intake.move(127);

    //second high stake
    rotationPosition = 0;
    chassis.turnToPoint(-50, 45, 1000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.moveToPoint(-50, 45, 4000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.turnToPoint(-35, 64, 600);
    chassis.moveToPoint(-35, 64, 4000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.turnToPoint(-70, 64, 1000);
    intake.move(-50);
    rotationPosition = 1;
    pros::delay(200);
    intake.move(100);
    chassis.moveToPoint(-70, 64, 1000, {.maxSpeed = 60}, false);
    rotationPosition = 5;
    pros::delay(600);
    chassis.moveToPoint(-40, 64, 4000, {.forwards = false, .maxSpeed = 80}, false);
    rotationPosition = 3;
   

    //fill up 4th goal put in corner
    targetColor = "Red";
    chassis.turnToPoint(-40, 110, 1000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-40, 110, 4000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-40, 120, 4000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(300);
    intake.move(0);
    chassis.moveToPoint(-65, 130, 2000, {.forwards = false, .maxSpeed = 110}, false);
    clamp.set_value(LOW);
    pros::delay(400);
    chassis.moveToPoint(-40, 100, 4000, {.forwards = true, .maxSpeed = 80}, false);
}
