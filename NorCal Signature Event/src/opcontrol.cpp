
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
bool armRunning = false;

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
void lady_brown_control(void* param){
        int rotationPosition = 0;
        bool last_button_L1_state = false;
        ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        int firstStopPosition = 1900;//get ready to load ring
        int secondStopPosition = 16000;// put ring on to the goal 
        int lastStopPosition = 3;// arm coming back to rest
        int currentPosition = 0;

        while (true) {
            bool current_button_L1_state = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
            if (current_button_L1_state) {  
                if(rotationPosition == 0 ){
                    currentPosition = arm_control(currentPosition, firstStopPosition, 0.03);
                    rotationPosition = 1;
                    controller.print(1, 5, "Hello");
                }else if(rotationPosition == 1 ){
                    intake.move(-10);
                    pros::delay(300);
                    intake.brake();
                    currentPosition = arm_control(currentPosition, secondStopPosition, 0.006);  //0.004
                    rotationPosition = 2; 
                }else if(rotationPosition == 2 ){
                    currentPosition = arm_control(currentPosition, lastStopPosition, 0.0067);
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

// true for forward, false for backward
void colorSort(void* param){
    while(true){
        std::string targetColor = *static_cast<std::string*>(param);
        std::string currentColor = detect_color();
        if(currentColor == targetColor){
            pros::delay(170);
            intake.move(-127);
            pros::delay(700);
            intake.move(127);
        }
        pros::delay(20);
    }
    
}

void intakeControl(bool dir, std::string targetColor){
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

    std::string targetColor = "Red";

    Task colorSorting(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");
    Task ladyBrown(lady_brown_control, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Lady Brown");
    
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

        bool arm_started = false;

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
                intakeControl(true, targetColor);
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
        
        controller.print(1, 5, "Target: %s", targetColor.c_str());
    }
}
