#include "robot.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"

Controller controller(E_CONTROLLER_MASTER);
MotorGroup left({11, -7, -6}, MotorGearset::blue);
MotorGroup right({-3, 12, 8}, MotorGearset::blue);
Motor intake(-17, MotorGearset::blue);
Motor ladyBrown(19, MotorGearset::red);
ADIDigitalOut clamp('H');
ADIDigitalOut intakePiston('F');
ADIDigitalOut doinker('G');
ADIDigitalOut doinker2('E');
Imu imu(4);
Rotation hTracking(2);
// Rotation vTracking(20);
Rotation armSensor(-13);
Optical color(14);

lemlib::TrackingWheel horizontal_tracking_wheel(&hTracking, lemlib::Omniwheel::NEW_2, -2.5);
// lemlib::TrackingWheel vertical_tracking_wheel(&vTracking, lemlib::Omniwheel::NEW_2, -5.5);


Drivetrain drivetrain (
    &left,
    &right,
    8,
    Omniwheel::NEW_325,
    360,
    2
);

OdomSensors sensors(
    nullptr,//vertical_tracking_wheel,
    nullptr,
    &horizontal_tracking_wheel,
    nullptr,
    &imu
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     20, // minimum output where drivetrain will move out of 127 //10
                                     1.03 // expo curve gain //1.019
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  20, // minimum output where drivetrain will move out of 127 /10
                                  1.03 // expo curve gain //1.019
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP) //10
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors,
                        &throttle_curve, 
                        &steer_curve // odometry sensors
);
