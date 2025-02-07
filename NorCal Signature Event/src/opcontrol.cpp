
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

//clamp
bool lastDownState = false;
bool clampState = LOW;

//doinker 
bool lastBState = false;
bool doinkerState = LOW;

//intake piston
bool lastLeftState = false;
bool intakePistonState = LOW;

//color sort 
bool lastAState = false;

//lady brown control
void ladybrownHighStakes(void* param){
        int rotationPosition = 0;
        bool last_button_L1_state = false;
        ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        int firstStopPosition = 1500;//get ready to load ring
        int secondStopPosition = 3500;
        int thirdStopPosition = 20000;// put ring on to the goal 
        int lastStopPosition = 100;// arm coming back to rest
        int currentPosition = 0;

        while (true) {
            bool current_button_L1_state = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
            if (current_button_L1_state) {  
                if(rotationPosition == 0 ){
                    currentPosition = arm_control(currentPosition,firstStopPosition, 0.0235, 0.001, 0.04);
                    rotationPosition = 1;
                }else if(rotationPosition == 1 ){
                    intake.move(-10);
                    pros::delay(300);
                    intake.brake();
                    currentPosition = arm_control(currentPosition, secondStopPosition, 0.0235, 0.001, 0.04);  //0.004
                    rotationPosition = 2; 
                }else if(rotationPosition == 2 ){
                    currentPosition = arm_control(currentPosition, thirdStopPosition, 0.015, 0.0, 0.04);  //0.004
                    rotationPosition = 3; 
                }
                else if(rotationPosition == 3 ){
                    currentPosition = arm_control(currentPosition, lastStopPosition, 0.009, 0.0, 0.02);
                    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    ladyBrown.brake();
                    rotationPosition = 0;             
                }
                //last_button_L1_state = current_button_L1_state;
            } else {
                current_button_L1_state = false;
            }
            pros::delay(20);
        }
}

void ladybrownFlipping(void* param){
    int rotationPosition = 0;
    bool last_button_L2_state = false;
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    int firstStopPosition = 20000;//get ready to load ring
    int secondStopPosition = 26000;
    int lastStopPosition = 100;
    int currentPosition = 0;

    while (true) {
        bool current_button_L2_state = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2);
        if (current_button_L2_state) {  
            if(rotationPosition == 0 ){
                currentPosition = arm_control(currentPosition,firstStopPosition, 0.024, 0.0, 0.04);
                rotationPosition = 1;
            }else if(rotationPosition == 1 ){
                currentPosition = arm_control(currentPosition, secondStopPosition, 0.02, 0.0, 0.04);  //0.004
                rotationPosition = 2; 
            }else if(rotationPosition == 3 ){
                currentPosition = arm_control(currentPosition, lastStopPosition, 0.009, 0.0, 0.02);
                ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                ladyBrown.brake();
                rotationPosition = 0;             
            }
            else {
                current_button_L2_state = false;
            }
            pros::delay(20);
        }
    }
}


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
    clamp.set_value(HIGH);
    int colorPosition = 2;
    int rotationPosition = -1;

    std::string targetColor = "Red";

    Task colorSorting(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");
    //Task ladyBrownHighStakes(ladybrownHighStakes, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lady Brown");
    //Task ladyBrownFlipping(ladybrownFlipping, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lady BrownFlipping");
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
                controller.print(1, 5, "LOCK");
            }
            else{
                clamp.set_value(HIGH);
                controller.print(1, 5, "NO LOCK");
            }
        }

        //lady brown
        if (currentL1State && !lastL1State) { 
            if (rotationPosition == -1) {
                rotationPosition = 0;
            }
            else if (rotationPosition == 0) {
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
            if (rotationPosition == -1) {
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
        lastLeftState = currentLeftState;
        lastL1State = currentL1State;
        lastL2State = currentL2State;

        controller.clear_line(1);
        controller.print(1, 5, "Target: %s", targetColor.c_str());
    }
}
