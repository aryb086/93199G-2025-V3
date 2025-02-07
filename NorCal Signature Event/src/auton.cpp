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
    chassis.moveToPoint(35, 15, 3000, {.forwards = false, .maxSpeed = 90}, false);
	pros::delay(100);
	clamp.set_value(LOW);
	pros::delay(200);

	//pick up first ring and put in lady brown
    rotationPosition = 0;
    intake.move(127);
	chassis.moveToPoint(22,40, 3000, {.forwards = true, .maxSpeed = 80}, false);
	chassis.moveToPoint(48,63, 3000, {.forwards = true, .maxSpeed = 80}, false);
    chassis.turnToPoint(65, 63, 1000);
    pros::delay(200);
    rotationPosition = 1;
    

    //score on high stake
    chassis.moveToPoint(65, 63, 1000, {.forwards = true, .maxSpeed = 70}, false);
    rotationPosition = 5;
    chassis.moveToPoint(67, 63, 1000, {.forwards = true, .maxSpeed = 70}, false);
    pros::delay(800);
    intake.move(127);
    chassis.moveToPoint(50,62, 3000, {.forwards = false, .maxSpeed = 80}, false);
    rotationPosition = 3;
    pros::delay(100);
    rotationPosition = -1;

    //grab 3rd ring
    chassis.turnToPoint(48, 90, 1000);
    chassis.moveToPoint(48, 90, 1000, {.forwards = true, .maxSpeed = 70}, false);

    //put goal in corner with 6 rings
    chassis.moveToPoint(50,15, 3000, {.forwards = true, .maxSpeed = 100}, false);
    pros::delay(500);
    chassis.moveToPoint(50,0, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(65, 20, 1000);
    chassis.moveToPoint(65, 20, 3000, {.forwards = true, .maxSpeed = 90}, false);
    chassis.turnToPoint(22, 40, 100, {.forwards = true}, false);
    pros::delay(200);
    clamp.set_value(HIGH);

    //grab second mogo
    chassis.moveToPoint(-35, 15, 3000, {.forwards = false, .maxSpeed = 90}, false);
    pros::delay(100);
	clamp.set_value(LOW);
	pros::delay(200);
}
