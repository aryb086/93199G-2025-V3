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
int arm_control(int startingPosition, int targetPosition, double constantK) {
    int error = startingPosition - targetPosition;
    int speed = error * constantK;
    int i = 0;
    ladyBrown.move(speed*-1);
    while (error  > 50 || error < -50)
    {
        pros::lcd::print(3, "Error 0: %1d", i); // x
        pros::lcd::print(4, "Speed 0: %1f", speed);  // x
        i++;
        pros::delay(20);
        //startingPosition = rotational_sensor.get_position();
        error = armSensor.get_position()*-1 - targetPosition;
        speed = error * constantK;
        if(speed <20 && speed>0) {
            speed = 20;
        } else if (speed<0 && speed>-20) {
            speed = -20;
        }
        ladyBrown.move(speed*-1);
        if (i>1000){
            break;
        }
    }
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladyBrown.brake();
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
