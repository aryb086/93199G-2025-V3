#include "liblvgl/llemu.hpp"
#include "pros/colors.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include "robot.h"
#include "main.h"
#include <cmath>
#include <memory>
#include <string>

/**
 * PID Implementation for ladybrown for accurate, smooth, macro control
 */
int arm_control(int startingPosition, int targetPosition, double kP, double kI, double kD, int errorRange) {
    int error = startingPosition - targetPosition;
    int lastError = error;
    int integral = 0;
    int derivative = 0;
    int speed = 0;
    int timeout = 0;

    while (abs(error) > errorRange && timeout < 1000) {  // Adjusted threshold and timeout
        // Proportional term
        int pTerm = error * kP;

        // Integral term with anti-windup
        integral += error;
        if (integral > 1000) integral = 1000;
        if (integral < -1000) integral = -1000;
        int iTerm = integral * kI;

        // Derivative term
        derivative = error - lastError;
        int dTerm = derivative * kD;

        // Calculate speed
        speed = pTerm + iTerm + dTerm;

        // Clamp speed to avoid stalling
        if (speed > 127) speed = 127;
        if (speed < -127) speed = -127;

        // Move the motor
        ladyBrown.move(speed*-1);

        // Update error
        lastError = error;
        error = armSensor.get_position() - targetPosition;

        // Debugging
        pros::lcd::print(0, "Error: %d", error);
        pros::lcd::print(1, "Speed: %d", speed);

        // Increment timeout
        timeout++;
        pros::delay(20);
    }

    // Brake the motor
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladyBrown.brake();

    // Debugging
    if (timeout >= 1000) {
        pros::lcd::print(5, "PID Timeout!");
    }

    return ladyBrown.get_position();
}

void intake_forward(){
    intake.move(127);
}

void intake_backward(){
    intake.move(-127);
}

// dir(true for fwd, false for rev), time(msec)
void intake_auton(bool dir, int time){
    if(dir){
        intake_forward();
        pros::delay(time);
        intake.brake();
    }
    else{
        intake_backward();
        pros::delay(time);
        intake.brake();
    }
}

/**
 * Color sort based on color we want to sort too
 */
std::string detect_color(){
    double hue = color.get_hue();
    double red = 20.0;
    double blue = 185.0;
    if(color.get_proximity() < 5){
        if(hue < red){
            return "Blue";
        }
        else if(hue > blue){
            return "Red";
        }
        return "";
    }
}

void colorSort(void* param){
    while(true){
        std::string targetColor = *static_cast<std::string*>(param);
        std::string currentColor = detect_color();
        if(currentColor == targetColor){
            if(intake.get_target_velocity() > 0){
                pros::delay(150);
                intake.move(-127);
                pros::delay(800);
                intake.move(0);
                pros::delay(100);
                intake.move(127);
            }
        }
        pros::delay(20);
    }
    
}

/* need to input rotation position:
0 for loading into ladybrown,
1 for holding up but intaking onto goal,
2 for scoring on high ladybrown highstakes,
3 for returning to starting,
4 for getting ready to unflip,
5 for unflip */
void ladyBrownControl(void* param) {
    int* rotationPositionPtr = static_cast<int*>(param);
    int firstStopPosition = 1800;
    int secondStopPosition = 6000;
    int thirdStopPosition = 16000;
    int fourthStopPostion = 18000;
    int fifthStopPostion = 25000;
    int lastStopPosition = 100;

    while (true) {
        int currentRotationPosition = *rotationPositionPtr; // Dereference each loop
        int currentPosition = armSensor.get_position();

        if (currentRotationPosition == 0) {
            currentPosition = arm_control(currentPosition, firstStopPosition, 0.025, 0.0, 0.02, 800);
            ladyBrown.brake();
            currentRotationPosition = 1;
        } else if (currentRotationPosition == 1) {
            currentPosition = arm_control(currentPosition, secondStopPosition, 0.03, 0.001, 0.04, 1500);
        } else if (currentRotationPosition == 2) {
            currentPosition = arm_control(currentPosition, thirdStopPosition, 0.015, 0.0, 0.04, 800);
        } else if (currentRotationPosition == 3) {
            currentPosition = arm_control(currentPosition, lastStopPosition, 0.02, 0.0, 0.02, 400);
            ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            ladyBrown.brake();
            *rotationPositionPtr = -1; // Update opcontrol's variable
        }
        else if (currentRotationPosition == 4) {
            intake.move(-80);
            currentPosition = arm_control(currentPosition, fourthStopPostion, 0.009, 0.0, 0.02, 1500);
            pros::delay(200);
            intake.move(127);
        }
        else if (currentRotationPosition == 5) {
            currentPosition = arm_control(currentPosition, fifthStopPostion, 0.009, 0.0, 0.02, 1500);
            ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            ladyBrown.brake();
        }

        pros::delay(20); // Prevent CPU hogging
    }
}

bool intakePistonState1 = false;
void intake_piston(){
    intakePistonState1 = !intakePistonState1;
    intakePiston.set_value(intakePistonState1);
}

bool doinkerState1 = false;
void doinker_control(){
    doinkerState1 = !doinkerState1;
    intakePiston.set_value(doinkerState1);
}

bool clampState1 = false;
void clamp_control(){
    clampState1 = !clampState1;
    intakePiston.set_value(clampState1);
}