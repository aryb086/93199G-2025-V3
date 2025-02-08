#include "main.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "robot.h"

void red_neg(){
    lcd::print(7, "Red Neg");
}

void red_pos(){
    lcd::print(7, "Red Pos");
}

void blue_neg(){
    lcd::print(7, "Blue Neg");

}

void blue_pos(){
    lcd::print(7, "Blue Pos");
}
void skills(){
    // skills
    int rotationPosition = -1;
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");

    chassis.setPose(0, 0, 0);
	clamp.set_value(HIGH);
	intake.move(127);
	pros::delay(800);
	intake.brake();

	//go forward of alliance stake
	chassis.moveToPoint(0,15, 3000, {.forwards = true, .maxSpeed = 90}, false);
	pros::delay(100);

	//pick up first mogo
    chassis.moveToPoint(30, 15, 3000, {.forwards = false, .maxSpeed = 90}, false);
	pros::delay(100);
	clamp.set_value(LOW);
	pros::delay(400);

	//pick up first ring and put in lady brown
    rotationPosition = 0;
    intake.move(127);
	chassis.moveToPoint(22,40, 3000, {.forwards = true, .maxSpeed = 80}, false);
	chassis.moveToPoint(48,63.5, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(65, 63.5, 1000);
    pros::delay(400);
    intake.move(-80);
    rotationPosition = 1;
    

    //score on high stake
    chassis.moveToPoint(67, 63.5, 1000, {.forwards = true, .maxSpeed = 70}, false);
    rotationPosition = 5;
    chassis.moveToPoint(69, 63.5, 1000, {.forwards = true, .maxSpeed = 70}, false);
    pros::delay(500);
    intake.move(127);
    chassis.moveToPoint(50,63.5, 3000, {.forwards = false, .maxSpeed = 80}, false);
    rotationPosition = 3;
    pros::delay(100);
    rotationPosition = -1;

    //grab 3rd ring
    intake.move(127);
    chassis.turnToPoint(49, 92, 1000);
    chassis.moveToPoint(49, 92, 1500, {.forwards = true, .maxSpeed = 70}, false);
    pros::delay(800);

    //put goal in corner with 6 rings
    chassis.moveToPoint(52,15, 3000, {.forwards = true, .maxSpeed = 100}, false);
    pros::delay(1200);
    chassis.moveToPoint(52,0, 3000, {.forwards = true, .maxSpeed = 70}, false);
    chassis.turnToPoint(65, 20, 1000);
    chassis.moveToPoint(65, 20, 3000, {.forwards = true, .maxSpeed = 90}, false);
    pros::delay(400);
    chassis.moveToPoint(70, 10, 1000, {.forwards = false}, false);
    pros::delay(500);
    clamp.set_value(HIGH);

    //grab second ring for alliance stake
    chassis.turnToPoint(48, 90, 1000);
    chassis.moveToPoint(48, 110, 3000, {.forwards = true, .maxSpeed = 70}, true);
    rotationPosition = 0;
    pros::delay(1000);
    
    //grab mogo with blue ring
    chassis.moveToPoint(15, 128, 2000, {.forwards = false, .maxSpeed = 70}, false);
    clamp.set_value(LOW);
    pros::delay(800);
    intake.move(-80);
    rotationPosition = 1;

    //put in corner
    pros::delay(200);
    intake.move(127);
    chassis.turnToPoint(70, 145, 1000, {.forwards = true, .maxSpeed = 70});
    chassis.moveToPoint(95, 140, 3000, {.forwards = true, .maxSpeed = 90}, false);
    intake.move(0);
    chassis.turnToPoint(48, 90, 1000, {.forwards = true, .maxSpeed = 70});
    chassis.turnToPoint(70, 145, 1000, {.forwards = true, .maxSpeed = 70});
    chassis.moveToPoint(85, 140, 3000, {.forwards = false, .maxSpeed = 90}, false);
    clamp.set_value(HIGH);
    pros::delay(200);

    //score on red alliance stake
    chassis.moveToPoint(0, 130, 500, {.forwards = true, .maxSpeed = 70}, false);
    chassis.moveToPoint(0, 115, 1000, {.forwards = false, .maxSpeed = 70}, false);
    clamp.set_value(LOW);
    pros::delay(500);
    chassis.turnToHeading(0, 1000);
    rotationPosition = 5;
    pros::delay(800);
    chassis.moveToPoint(0, 150, 3000, {.forwards = false, .maxSpeed = 40}, false);
 


}
