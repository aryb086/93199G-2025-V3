#include "liblvgl/llemu.hpp"
#include "pros/rtos.hpp"
#include "robot.h"
#include "main.h"
#include <cmath>
#include <string>

/**
 * PID Implementation for ladybrown for accurate, smooth, macro control
 */

// Updated PID constants
const double armkP = 0.05;   // Stronger correction
const double armkI = 0.001;  // Small Ki for steady-state correction
const double armkD = 0.005;  // Kd for damping oscillations

const double maxVoltage = 90;
const double minVoltage = -90;
const double tolerance = 5.0;      // Acceptable error range
const double maxIntegral = 5000.0; // Prevents integral windup

double restrict(double value, double min, double max) {
    return fmax(min, fmin(value, max));
}

void arm_control(double targetAngle) {
    double error = 0;
    double lastError = 0;
    double integral = 0;
    double derivative = 0;
    double power = 0;

    printf("Moving to Target: %.2f\n", targetAngle);

    while (true) {
        // Read current angle
        double currentAngle = static_cast<double>(armSensor.get_angle());

        // Calculate PID terms
        error = currentAngle - targetAngle;
        integral = restrict(integral + error, -maxIntegral, maxIntegral); // Prevent windup
        derivative = error - lastError;

        // Compute PID output
        power = (armkP * error) + (armkI * integral) + (armkD * derivative);

        // Limit power output
        power = restrict(power, minVoltage, maxVoltage);

        // Apply power to motor
        ladyBrown.move(power);

        // Break if within tolerance
        if (fabs(error) < tolerance) {
            ladyBrown.move(0);
            break;
        }

        // Store last error for derivative calculation
        lastError = error;

        // Delay to avoid excessive CPU usage
        pros::delay(20);
    }
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