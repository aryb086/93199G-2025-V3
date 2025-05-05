#include "main.h"
#include "liblvgl/llemu.hpp"
#include "pros/adi.h"
#include "pros/colors.h"
#include "pros/colors.hpp"
#include "pros/llemu.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "robot.h"
#include "pros/misc.h"

int colorSelection = 0;
int rotationPosition = 0;
double basePositionDegrees = 0;
std::string targetColor = "Red";

void aliianceColor(){
	static int pressed = 0;
	if(pressed == 0) {
		pros::screen::set_pen(c::COLOR_RED); // Set pen color to red
		pros::screen::print(pros::E_TEXT_MEDIUM,5, "----Color: Red--");
		colorSelection = 1;
		pressed += 1;
		targetColor = "Red";
	}
	else if(pressed == 1){
		pros::screen::set_pen(c::COLOR_BLUE); // Set pen color to red
		pros::screen::print(pros::E_TEXT_MEDIUM,5, "----Color: Blue--");
		colorSelection = 2;
		pressed += 1;
		targetColor = "Blue";
	}
	else{
		pros::screen::set_pen(c::COLOR_CYAN); // Set pen color to red
		pros::screen::print(pros::E_TEXT_MEDIUM,5, "**** SKILLS *** ");
		pressed = 0;
		colorSelection = 0;
		targetColor = "Red";
	}

}


int negPositiveSelection = 0;
void negPos(){
	static int pressed = 0;
	if(pressed == 0) {
		pros::lcd::set_text(5, "--------------Negative--------------");
		negPositiveSelection = 1;
		pressed += 1;
	}
	else if(pressed == 1){
		pros::lcd::set_text(5, "---------------Postive--------------");
		pressed += 1;
		negPositiveSelection = 2;
	}
	else{
		pros::lcd::set_text(5, "--------------Solo AWP--------------");
		negPositiveSelection = 0;
		pressed = 0;
	}

}

/**()
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
bool selectionConfirmed = false;
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::clear_line(3);
		pros::lcd::set_text(3, "-----Press Again To Confirm Selection----");
		//pros::lcd::print(6, "NegPos: %d", negPositiveSelection);
	} else {
		pros::lcd::clear_line(3);
		pros::lcd::set_text(3, "---------Selection Confirmed-------");
		//pros::lcd::print(6, "NegPos: %d", negPositiveSelection);
		selectionConfirmed = true;
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	imu.reset(true);
	chassis.calibrate();
	chassis.setPose(42, -21, 35);
	//chassis.setPose(42, -21, 145);
	armSensor.reset_position();
	ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	basePositionDegrees = armSensor.get_position() / 100;
	Task colorSorting(colorSort, &targetColor, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Color Sort");
    //Task ladybrownTask(ladyBrownControl,  &rotationPosition, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm Control");

	pros::Task screen_task([&]() {
        while (true) {
			// print robot location to the brain screen
			pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
			pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
			pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
			pros::lcd::print(3, "Target Color: %s", targetColor); // heading
			// delay to save resources
			pros::delay(20);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::Task autonSelector([&]() {
        while (true) {
            if (!selectionConfirmed) {
				pros::lcd::register_btn0_cb(aliianceColor);
				pros::lcd::register_btn1_cb(on_center_button);
				pros::lcd::register_btn2_cb(negPos);
			}
            pros::delay(20);
        }
    }); 
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	red_solo_awp();
	/*
	if(colorSelection == 1){
		if(negPositiveSelection == 1){
			red_pos();
		}
		else if (negPositiveSelection == 2){
			red_neg();
		}
		else if (negPositiveSelection == 0){
			red_solo_awp();
		}
	}
	else if (colorSelection == 2){
		if(negPositiveSelection == 1){
			blue_pos();
		}
		else if (negPositiveSelection == 2){
			blue_neg();
		}
		else if (negPositiveSelection == 0){
			blue_solo_awp();
		}
	}
	else{
		skills();
	}
		*/
}

