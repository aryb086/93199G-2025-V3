#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "robot.h"
#include <string>



void red_pos(){
    lcd::print(7, "Red Pos");
    
    int rotationPosition = -1;
    std::string targetColor = "Red";
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
   
    chassis.setPose(58, 24, 90);
	clamp.set_value(HIGH);
    rotationPosition = 0;

    // getting mogo #1
    chassis.moveToPoint(23,23, 3000, {.forwards = false, .maxSpeed = 70}, false);



}


void red_pos_2(){
    lcd::print(7, "Red Pos");

    int rotationPosition = -1;
    std::string targetColor = "Red";
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    //Task colorSortTask(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");

    chassis.setPose(-59, 12, 180);
	clamp.set_value(HIGH);
    rotationPosition = 0;
    intake.move(127);
    pros::delay(800);

    // scoring ring on alliance stake
    chassis.turnToPoint(-69,0, 3000, {.maxSpeed = 80}, false);
    pros::delay(200);
    intake.move(-80);
    rotationPosition = 5;
    pros::delay(1000);
   

    // clamping the mogo
    chassis.moveToPoint(-23,23, 3000, {.forwards = false, .maxSpeed = 70}, false);
    rotationPosition = 3;
    pros::delay(300);
    ladybrownTask.remove();
    clamp.set_value(LOW);
    pros::delay(600);
    intake.move(127);

    // scoring 1 rings in the center
    chassis.turnToPoint(-29,50, 1000);
    chassis.moveToPoint(-29,50, 3000, {.forwards = true, .maxSpeed = 70}, false);
    intake.move(127);
    chassis.turnToPoint(-12,50, 1000);
    chassis.moveToPoint(-12,50, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.moveToPoint(-30,58, 3000, {.forwards = false, .maxSpeed = 70}, false);

    //scoring 5th rings
    chassis.turnToPoint(-48,-3, 1000);
    intakePiston.set_value(HIGH);
    chassis.moveToPoint(-48,-3, 3000, {.forwards = true, .maxSpeed = 70}, false);
    pros::delay(200);
    intakePiston.set_value(LOW);

    //touching ladder 
    chassis.moveToPoint(-25,30, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(-25,10, 1000, {.forwards = true}, false);
    chassis.moveToPoint(-25,10, 3000, {.forwards = true, .maxSpeed = 90}, false);
    
    //colorSortTask.remove();
}

void red_neg(){
    lcd::print(7, "Red Neg");

    int rotationPosition = -1;
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");


    chassis.setPose(-58, -57, 90);
	clamp.set_value(HIGH);

    // rushing the mogo, lady browning it and tipping it
    rotationPosition = 0;
    intake.move(127);
    pros::delay(400);
    intake.brake();
	chassis.moveToPoint(-9,-53, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(9, -34, 1000);
    intake.move(-100);
    pros::delay(200);
    rotationPosition = 5;
    chassis.turnToPoint(-13, -69, 1000);
    
    // getting first ring
    chassis.turnToPoint(-23, -47, 1000);
    intake.move(127);
    chassis.moveToPoint(-23,-47, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(1000);
    intake.brake();

    // getting mogo, clamping, and scoring one ring
    chassis.turnToPoint(-23, -69, 1000);
    chassis.moveToPoint(-23,-23, 3000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(LOW);
    intake.move(127);

    // getting second ring
    chassis.turnToPoint(-23, -64, 1000);
    chassis.moveToPoint(-23,-24, 3000, {.forwards = false, .maxSpeed = 90}, false);






}

void blue_pos(){
   lcd::print(7, "Blue Pos");

    int rotationPosition = -1;
    std::string targetColor = "Blue";
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    //Task colorSortTask(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");

    chassis.setPose(59, 12, 180);
	clamp.set_value(HIGH);
    rotationPosition = 0;
    pros::delay(100);
    intake.move(127);
    pros::delay(500);

    // scoring ring on alliance stake
    chassis.turnToPoint(69,0, 3000, {.maxSpeed = 80}, false);
    pros::delay(200);
    intake.move(-80);
    pros::delay(400);
    rotationPosition = 5;
    pros::delay(1000);
   

    // clamping the mogo
    chassis.moveToPoint(20,28, 3000, {.forwards = false, .maxSpeed = 70}, false);
    rotationPosition = 3;
    pros::delay(300);
    ladybrownTask.remove();
    clamp.set_value(LOW);
    pros::delay(600);
    intake.move(127);

    // scoring 1 rings in the center
    chassis.turnToPoint(20,55, 1000);
    chassis.moveToPoint(20,55, 3000, {.forwards = true, .maxSpeed = 70}, false);
    intake.move(127);
    
    //scoring 5th rings
    chassis.turnToPoint(46,-3, 1000);
    intakePiston.set_value(HIGH);
    chassis.moveToPoint(46,-3, 3000, {.forwards = true, .maxSpeed = 70}, false);
    pros::delay(500);
    intakePiston.set_value(LOW);

    //touching ladder 
    chassis.moveToPoint(25,30, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(25,10, 1000, {.forwards = true}, false);
    chassis.moveToPoint(25,10, 3000, {.forwards = true, .maxSpeed = 90}, false);
    //ladybrownTask.remove();
    //colorSortTask.remove();
}

void blue_neg(){
    lcd::print(7, "Blue Neg");

    int rotationPosition = -1;
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");


    chassis.setPose(58, -53, 90);
	clamp.set_value(HIGH);

    // rushing the mogo and pulling it back
	chassis.moveToPoint(9,-53, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(-9, -34, 1000);
    doinker.set_value(HIGH);
    chassis.moveToPoint(28,-63, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(1000);
    doinker.set_value(LOW);

    //clamping rushed mogo
    chassis.turnToPoint(12,-58, 3000, {.forwards = false, .maxSpeed = 90}, false);
    chassis.moveToPoint(12,-58, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(200);
    clamp.set_value(LOW);
    pros::delay(400);

    // scoring preload on first mogo
    intake.move(127);
    
    // dropping 1st mogo and picking up 2nd one
    clamp.set_value(HIGH);
    chassis.turnToPoint(23,-23, 3000);
    chassis.moveToPoint(23,-39, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(1000);
    intake.brake();
    chassis.turnToPoint(23,-23, 3000, {.forwards = false, .maxSpeed = 90}, false);
    chassis.moveToPoint(23,-23, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(200);
    clamp.set_value(LOW);
    pros::delay(400);


    // scoring a ring on 2nd mogo
    intake.move(127);

    // touching the ladder
    chassis.turnToPoint(12,-13, 3000);
    chassis.moveToPoint(12,-13, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(300);
    rotationPosition = 2;
}


void skills(){
    // skills
    int rotationPosition = -1;
    std::string target = "Red";
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");
    Task colorSortTask(colorSort, &target, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");

    chassis.setPose(0, 0, 0);
	clamp.set_value(HIGH);
	intake.move(127);
	pros::delay(800);
	intake.brake();

	//go forward of alliance stake
	chassis.moveToPoint(0,15, 1000, {.forwards = true, .maxSpeed = 90}, false);

	//pick up first mogo
    chassis.moveToPoint(30, 15, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(100);
	clamp.set_value(LOW);
	pros::delay(300);

	//pick up first ring and put in lady brown
    rotationPosition = 0;
    intake.move(127);
	chassis.moveToPoint(22,40, 3000, {.forwards = true, .maxSpeed = 80}, false);
    pros::delay(500);
	chassis.moveToPoint(45,63.5, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(65, 63.5, 1000);   

    //score on high stake
    chassis.moveToPoint(67, 63.5, 1000, {.forwards = true, .maxSpeed = 60}, false);
    intake.move(-90);
    pros::delay(200);
    rotationPosition = 5;
    pros::delay(800);
    intake.move(127);
    pros::delay(300);
    chassis.moveToPoint(50,63.5, 3000, {.forwards = false, .maxSpeed = 80}, false);
    rotationPosition = 3;
    pros::delay(200);
    rotationPosition = -1;

    //grab 3rd ring
    intake.move(127);
    chassis.turnToPoint(46, 92, 1000);
    chassis.moveToPoint(46, 92, 2000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(800);

    //put goal in corner with 6 rings
    chassis.moveToPoint(50,6, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(500);
    chassis.moveToPoint(50,0, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.turnToPoint(65, 20, 1000);
    chassis.moveToPoint(65, 20, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(300);
    chassis.moveToPoint(60, 0, 2000, {.forwards = false}, false);
    pros::delay(200);
    clamp.set_value(HIGH);

    //grab second ring for alliance stake
    chassis.turnToPoint(48, 90, 1000);
    chassis.moveToPoint(48, 115, 3000, {.forwards = true, .maxSpeed = 110}, true);
    rotationPosition = 0;
    pros::delay(1000);
    
    //grab mogo with blue ring
    chassis.moveToPoint(20, 130, 2000, {.forwards = false, .maxSpeed = 70}, false);
    clamp.set_value(LOW);
    pros::delay(100);

    //put in corner
    chassis.turnToPoint(70, 140, 1000, {.forwards = true, .maxSpeed = 90});
    doinker2.set_value(HIGH);
    chassis.moveToPoint(60, 130, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(90, 150, 1000, {.forwards = false, .maxSpeed = 70});
    doinker2.set_value(LOW);
    chassis.moveToPoint(70, 125, 2000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(HIGH);
    intake.move(0);
    pros::delay(200);

    //score on red alliance stake
    chassis.moveToPoint(30, 115, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.moveToPoint(15, 115, 3000, {.forwards = false, .maxSpeed = 70}, false);
    clamp.set_value(LOW);
    pros::delay(500);
    chassis.turnToHeading(7, 1000);
    chassis.moveToPoint(15, 120, 3000, {.forwards = true, .maxSpeed = 40}, false);
    rotationPosition = 5;
    pros::delay(800);
    chassis.moveToPoint(15, 115, 2000, {.forwards = false, .maxSpeed = 70}, false);
    rotationPosition = 3;
    pros::delay(200);
    rotationPosition = -1;

    //filling up 3rd goal
    intake.move(127);
    chassis.moveToPoint(40, 100, 4000, {.forwards = true, .maxSpeed = 90, .minSpeed = 20, .earlyExitRange = 10}, false);
    chassis.moveToPoint(40, 85, 4000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(-33, 13, 1000);
    chassis.moveToPoint(-33, 13, 4000, {.forwards = true, .maxSpeed = 90}, false);
    delay(200);
    chassis.turnToPoint(-33, 0, 1000);
    chassis.moveToPoint(-33, 0, 4000, {.forwards = true, .maxSpeed = 60}, false);
    delay(600);
    colorSortTask.remove();
    chassis.turnToPoint(-50, 10, 1000);
    chassis.moveToPoint(-50, 10, 2000, {.forwards = true, .maxSpeed = 60}, false);
    delay(600);
    chassis.moveToPoint(-55, 0, 1000, {.forwards = false, .maxSpeed = 80}, false);
    delay(300);
    clamp.set_value(HIGH);

    //get 4th goal
    chassis.moveToPoint(-30, 10, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-10, 10, 3000, {.forwards = false, .maxSpeed = 80}, false);
    delay(100);
    clamp.set_value(LOW);
    delay(200);

    //fill up 4th goal
    chassis.moveToPoint(-45, 30, 4000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(-45, 100, 1000);
    chassis.moveToPoint(-45, 110, 4000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.moveToPoint(-65, 140, 4000, {.forwards = false}, false);
    clamp.set_value(HIGH);
    pros::delay(200);
    chassis.moveToPoint(-40, 100, 4000, {.forwards = true, .maxSpeed = 80}, false);
}
