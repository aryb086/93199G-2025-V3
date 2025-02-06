#include "liblvgl/llemu.hpp"
#include "pros/colors.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "robot.h"
#include "main.h"
#include <cmath>
#include <memory>
#include <string>

/**
 * PID Implementation for ladybrown for accurate, smooth, macro control
 */
int arm_control(int startingPosition, int targetPosition, double kP, double kI, double kD) {
    int error = startingPosition - targetPosition;
    int lastError = error;
    int integral = 0; 
    int derivative = 0;
    int speed = 0;
    int i = 0;

    pros::lcd::print(2, "Initial Error: %1d", error);

    // Start moving the motor
    ladyBrown.move(speed * -1);

    // PID Loop
    while (error > 50 || error < -50) {
        pros::lcd::print(3, "Error: %1d", error);
        pros::lcd::print(4, "Speed: %1i", armSensor.get_position());

        i++;
        pros::delay(20);

        // Update error
        error = armSensor.get_position() - targetPosition;

        // Proportional term
        int pTerm = error * kP;

        // Integral term (with anti-windup)
        integral += error;
        int iTerm = integral * kI;
        // To avoid integral windup, we can clamp the integral term:
        if (iTerm > 1000) iTerm = 1000;
        else if (iTerm < -1000) iTerm = -1000;

        // Derivative term
        derivative = error - lastError;
        int dTerm = derivative * kD;

        // Combine all terms
        speed = pTerm + iTerm + dTerm;

        // Set a minimum speed threshold to avoid stalling
        if (speed < 20 && speed > 0) {
            speed = 20;
        } else if (speed < 0 && speed > -20) {
            speed = -20;
        }

        ladyBrown.move(speed * -1);

        // Save the last error for the next derivative calculation
        lastError = error;

        if (i > 1000) {
            break;
        }
    }

    // After reaching the position, brake
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladyBrown.brake();

    // Return the final position
    int position = ladyBrown.get_position();
    return position;
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
    if(color.get_proximity() < 10){
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
            pros::delay(170);
            intake.move(-127);
            pros::delay(700);
            intake.move(127);
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
void ladyBrownControl(void* param){
    int rotationPosition = *static_cast<int*>(param);
    int firstStopPosition = 1500;
    int secondStopPosition = 3500;
    int thirdStopPosition = 20000;
    int fourthStopPostion = 20000;
    int fifthStopPosition = 26000;
    int lastStopPosition = 100;
    while(true){
        int currentPosition = armSensor.get_position();
        if(rotationPosition == 0 ){
            currentPosition = arm_control(currentPosition,firstStopPosition, 0.0235, 0.001, 0.04);
        }else if(rotationPosition == 1 ){
            intake.move(-10);
            pros::delay(300);
            intake.brake();
            currentPosition = arm_control(currentPosition, secondStopPosition, 0.0235, 0.001, 0.04);  //0.004
        }else if(rotationPosition == 2 ){
            currentPosition = arm_control(currentPosition, thirdStopPosition, 0.015, 0.0, 0.04);  //0.004
        }
        else if(rotationPosition == 3 ){
            currentPosition = arm_control(currentPosition, lastStopPosition, 0.009, 0.0, 0.02);
            ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            ladyBrown.brake();
            rotationPosition = -1;
        }
        else if(rotationPosition == 4 ){
                currentPosition = arm_control(currentPosition,firstStopPosition, 0.024, 0.0, 0.04);
        }else if(rotationPosition == 5 ){
                currentPosition = arm_control(currentPosition, secondStopPosition, 0.02, 0.0, 0.04);  //0.004
        }
    }
}

bool intakePistonState = false;
void intake_piston(){
    intakePistonState = !intakePistonState;
    intakePiston.set_value(intakePistonState);
}

bool doinkerState = false;
void doinker_control(){
    doinkerState = !doinkerState;
    intakePiston.set_value(doinkerState);
}

bool clampState = false;
void clamp_control(){
    clampState = !clampState;
    intakePiston.set_value(clampState);
}