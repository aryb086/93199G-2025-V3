#include "liblvgl/llemu.hpp"
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
#include "robot.h"
#include "main.h"
#include <cmath>
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

}

void intake_backward(){

}

void intake_auton(){

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

void color_sort(std::string target){
    intake.move(127);
    while(true){
        std::string color = detect_color();
        if(color.compare(target) == 0){

            /*
            pros::delay(280);
            intake.move(0);
            pros::delay(500);
            intake.move(127);
            */

            pros::delay(150);
            intake.move(-127);
            pros::delay(800);
            intake.move(127);

        }
        pros::delay(20);
    }
}

void intake_piston(){

}

void doinker_control(){

}
