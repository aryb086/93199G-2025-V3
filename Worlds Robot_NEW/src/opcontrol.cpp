
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

//intake front 
bool lastXState = false;

//intake back
bool lastUpState = false;


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

// Lady Brown States and Stops
double basePosition = 0;
int firstStopPosition = 1450;
int secondStopPosition = 6000;
int thirdStopPosition = 14000;


void intakeControl(bool dir){
        if(dir){
            back_intake.move(127);
            front_intake.move(127); //120 for skills, 100 for team
        }
        else{
            back_intake.move(-127);
            front_intake.move(-127);// -120
        }
}

void opcontrol() {
    //clamp.set_value(HIGH);
    int colorPosition = 0;
    targetColor = "Blue";
    rotationPosition = 0;

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

        bool currentUpState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);

        bool currentXState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);

        bool currentAState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);

        bool currentYState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);

        bool currentL1State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

        bool currentL2State = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);

        bool currentRightState = controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);

        bool intake_started = false;

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


        
        if(currentR1State && !lastR1State){
            intakeRunning = !intakeRunning;

            if(intakeRunning){
                front_intake.move(127);
                back_intake.move(127);
            }
            else{
                front_intake.brake();
                back_intake.brake();
                bool intake_running = true;

            }
        }

        //intake reverse
        if(currentR2State && !lastR2State){
            intakeRunning = !intakeRunning;
            if(intakeRunning){
                front_intake.move(-127);
                back_intake.move(-127);
            } 
            else {
                front_intake.brake();
                back_intake.brake();
                bool intake_running = true;
            }
        }

        //intake front
        if(currentUpState && !lastUpState){
            intakeRunning = !intakeRunning;
            if(intakeRunning){
                front_intake.move(127);
            } 
            else {
                front_intake.brake();
                bool intake_running = true;
            }
        }

        //intake back
        if(currentXState && !lastXState){
            intakeRunning = !intakeRunning;
            if(intakeRunning){
                back_intake.move(127);
            } 
            else {
                back_intake.brake();
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
            pros::lcd::print(5, "Rotational Position: %d", rotationPosition);

            if (rotationPosition == -1) {
                rotationPosition = 0;
            }
            else if (rotationPosition == 0 || rotationPosition == 6) {
                pros::Task task1([&]() {
                    //ladyBrownGoToPosition(firstStopPosition, 50);
                    ladyBrownGoToPositionPID(firstStopPosition, 0.035, 50);
                });
                rotationPosition = 1;
            }
            else if (rotationPosition == 1) {
                rollbackAndStopIntake();
                pros::Task task2([&]() {
                    //ladyBrownGoToPosition(secondStopPosition, 60);
                    ladyBrownGoToPositionPID(secondStopPosition, 0.02, 100);
                });
                rotationPosition = 2;
            }
            else if (rotationPosition == 2) {
                pros::Task task3([&]() {
                    //ladyBrownGoToPosition(thirdStopPosition, 80);
                    ladyBrownGoToPositionPID(thirdStopPosition, 0.02, 100);

                });
                rotationPosition = 3;
            }
        }

        if (currentL2State && !lastL2State) { 
            if (rotationPosition == -1 || rotationPosition == 0 || rotationPosition == 6) {
                front_intake.move(-80);
                back_intake.move(-80);
                pros::delay(25);
                front_intake.move(-127);
                back_intake.move(-127);                
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
            ladyBrownGoToBase(70);
        }

        if(currentYState && !lastYState){
            rotationPosition = 6;
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
        lastXState = currentXState;
        lastUpState = currentUpState;


        controller.print(1, 0, "Color: %s Clamp: %s" , targetColor.c_str(), clampStateString.c_str());
    }
}

void ladyBrownGoToPosition(int targetPosition, int speed){
    int currentPosition = armSensor.get_position() * -1;
    int timeout = 1000; // 1000 milliseconds
    uint32_t startTime = pros::millis(); // Get current time
    while(currentPosition < targetPosition && (pros::millis() - startTime) < timeout ){
        int error = targetPosition - currentPosition;
        if(abs(error) < 500){
            speed = speed / 2;
        }
        ladyBrown.move(speed);
        currentPosition = armSensor.get_position() * -1;
        pros::delay(20);
    }
    // Brake the motor
    ladyBrown.move(0);
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladyBrown.brake();
}

void ladyBrownGoToPositionPID(int targetPosition, double kp, int errorRange){
    int currentPosition = armSensor.get_position() * -1;
    int timeout = 2000; // 1000 milliseconds
    uint32_t startTime = pros::millis(); // Get current time
    int error = targetPosition - currentPosition;
    while(abs(error) > errorRange && (pros::millis() - startTime) < timeout ){
        int speed = error * kp;
        pros::lcd::print(6, "Speed: %d", speed);
        if (speed > 127) speed = 127;
        if (speed < -127) speed = -127;

        ladyBrown.move(speed);
        
        currentPosition = armSensor.get_position() * -1;
        pros::delay(20);
        error = targetPosition - currentPosition;
    }
    // Brake the motor
    ladyBrown.move(0);
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladyBrown.brake();
    displayArmPosition();
}

void ladyBrownGoToBase(int speed){
    int currentPosition = armSensor.get_position() * -1;
    int timeout = 1500; // 1000 milliseconds
    uint32_t startTime = pros::millis(); // Get current time
    while(currentPosition > 0 && (pros::millis() - startTime) < timeout ){
        int speed = currentPosition * 0.01;
        if (speed > 127) speed = 127;
        if (speed < -127) speed = -127;

        if(speed > 0) speed = speed * -1;

        ladyBrown.move(speed);
        currentPosition = armSensor.get_position() * -1;
        pros::delay(20);
    }
    // Brake the motor
    ladyBrown.move(0);
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    ladyBrown.brake();
    //reset arm sensor
    armSensor.set_position(0);
    rotationPosition = 0;
    displayArmPosition();
}

void rollbackAndStopIntake(){
    front_intake.move(-127);
    back_intake.move(-127);
    pros::delay(50);
    front_intake.move(0);
    back_intake.move(0);
}

void displayArmPosition(){
    pros::lcd::print(4, "Arm: %d", armSensor.get_position() * -1);
}
