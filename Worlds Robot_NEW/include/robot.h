#pragma once

#include "lemlib/api.hpp"
#include "pros/distance.hpp"
#include "pros/imu.h"
#include "pros/imu.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
using namespace pros;
using namespace lemlib;

extern Controller controller;
extern Chassis chassis;
extern Motor front_intake;
extern Motor back_intake;
extern Motor ladyBrown;
extern MotorGroup left;
extern MotorGroup right;
extern ADIDigitalOut clamp;
extern ADIDigitalOut intakePiston;
extern ADIDigitalOut doinker;
extern ADIDigitalOut doinker2;
extern Rotation armSensor;
extern Optical color;
extern Rotation hTracking;
extern Rotation vTracking;
extern Imu imu;
extern Distance distanceC;
