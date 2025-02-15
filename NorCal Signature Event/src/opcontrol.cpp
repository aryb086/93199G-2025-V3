
#include "main.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "robot.h"
#include <string>

/** 
 * USER CONTROL (CONTROLLER MAPPING):
 * Drive: Tank
 * R1: Intake FWD
 * R2: Intake REV
 * 
 * L1: Ladybrown Macros
 * 
 * Button Down: Clamp
 * Button Left: Intake Piston
 * Button Right: Reset Lady Brown To Intial
 * Button B: Doinker
 * Button A: Color Switcher
 * 
 */

//intake fwd
bool lastR1State = false;
bool intakeRunning = false;

//intake reverse
bool lastR2State = false;

//lady brown
bool lastL1State = false;
bool lastL2State = false;
bool lastRightState = false;
bool lastYState = false;

//clamp
bool lastDownState = false;
bool clampState = HIGH;
std::string clampStateString = "LOCK";

//doinker 
bool lastBState = false;
bool doinkerState = LOW;

//intake piston
bool lastLeftState = false;
bool intakePistonState = LOW;

//color sort 
bool lastAState = false;

// true for forward, false for backward


void intakeControl(bool dir){
        if(dir){
            intake.move(127);
        }
        else{
            intake.move(-127);
        }
}

void opcontrol() {
    //clamp.set_value(HIGH);
    int colorPosition = 2;
    int rotationPosition = 3;

    std::string targetColor = "Red";

    //Task colorSorting(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");
    Task ladybrownTask(ladyBrownControl, &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");

    while(true){
        //movement
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        chassis.tank(leftY, rightY);

        bool currentR1State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

        bool currentR2State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

        bool currentDownState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

        bool currentBState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

        bool currentLeftState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

        bool currentAState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

        bool currentYState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

        bool currentL1State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

        bool currentL2State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

        bool currentRightState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

        bool intake_started = false;
        // dataFwd = {true, targetColor};

        //color switcher
        if (currentAState && !lastAState) { 
            if (colorPosition == 0) {
                targetColor = "Blue";
                colorPosition = 1;
            }
            else if (colorPosition == 1) {
                targetColor = "Red";
                colorPosition = 2;
            }
            else if (colorPosition == 2) {
                targetColor = "None";
                colorPosition = 0;
            }
        }

        //intake fwd
        if(currentR1State && !lastR1State){
            intakeRunning = !intakeRunning;
            if(intakeRunning){ 
                intakeControl(true);
            } else {
                intake.brake();
                bool intake_running = true;
            }
        }

        //intake reverse
        if(currentR2State && !lastR2State){
            intakeRunning = !intakeRunning;
            if(intakeRunning){
                intake.move(-127);
            } 
            else {
                intake.brake();
                bool intake_running = true;
            }
        }

        
        //clamp
        if(currentDownState && !lastDownState){
            clampState = !clampState;

            if(clampState){
                clamp.set_value(LOW);
                clampStateString = "LOCK";
            }
            else{
                clamp.set_value(HIGH);
                clampStateString = "LOCK";
            }
        }

        //lady brown
        if (currentL1State && !lastL1State) { 
            if (rotationPosition == -1) {
                rotationPosition = 0;
            }
            else if (rotationPosition == 0) {
                intake.move(-40);
                rotationPosition = 1;
            }
            else if (rotationPosition == 1) {
                rotationPosition = 2;
            }
            else if (rotationPosition == 2) {
                rotationPosition = 3;
            }
        }

        if (currentL2State && !lastL2State) { 
            if (rotationPosition == -1 || rotationPosition == 0) {
                intake.move(-40);
                rotationPosition = 4;
            }
            else if (rotationPosition == 4) {
                rotationPosition = 5;
            }
            else if (rotationPosition == 5) {
                rotationPosition = 3;
            }
        }

        if(currentRightState && !lastRightState){
            rotationPosition = 3;
        }

        if(currentYState && !lastYState){
            rotationPosition = 0;
        }

        //intake piston
        if(currentLeftState && !lastLeftState){
            intakePistonState = !intakePistonState;

            if(intakePistonState){
                intakePiston.set_value(HIGH);
            }
            else{
                intakePiston.set_value(LOW);
            }
        }


        //doinker
        if(currentBState && !lastBState){
            doinkerState = !doinkerState;

            if(doinkerState){
                doinker.set_value(HIGH);
            }
            else{
                doinker.set_value(LOW);
            }
        }
        pros::delay(25);

        lastR1State = currentR1State;
        lastR2State = currentR2State;
        lastBState = currentBState;
        lastDownState = currentDownState;
        lastAState = currentAState;
        lastYState = currentYState;
        lastLeftState = currentLeftState;
        lastL1State = currentL1State;
        lastL2State = currentL2State;

        controller.print(1, 0, "Color: %s Clamp: %s" , targetColor.c_str(), clampStateString.c_str());
    }
}
