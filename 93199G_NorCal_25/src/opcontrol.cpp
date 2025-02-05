#include "liblvgl/llemu.hpp"
#include "main.h"
#include "pros/adi.h"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "robodash/views/console.hpp"
#include "robot.h"
#include <algorithm>
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
    int rotationPostion = 0;
    ladyBrown.set_brake_mode(E_MOTOR_BRAKE_COAST);
    int initial = armSensor.get_angle();
    int pos1 = 4000;
    int pos2 = 4000;
    int pos3 = 1600;
    while(true){
        bool currentL1State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
        if (currentL1State){
            if(rotationPostion == 0){
                //arm_control(pos1);
                ladyBrown.move(80);
                rotationPostion = 1;
            }
            else if(rotationPostion == 1){
                //arm_control(pos2);
                ladyBrown.move(80);
                rotationPostion = 2;
            }
            else if(rotationPostion == 2){
                //intake.move(-10);
                //pros::delay(100);
                //intake.brake();
                //arm_control(pos3);
                ladyBrown.move(80);
                rotationPostion = 3;
            }
            else if(rotationPostion == 3){
                //arm_control(initial);
                ladyBrown.move(20);
                rotationPostion = 0;
            }
            else{
                currentL1State = false;
            }
            pros::delay(20);
        }
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