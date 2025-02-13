#pragma once

#include "lemlib/api.hpp"
#include "pros/imu.h"
#include "pros/imu.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
using namespace pros;
using namespace lemlib;

extern Controller controller;
extern Chassis chassis;
extern Motor intake;
extern Motor ladyBrown;
extern ADIDigitalOut clamp;
extern ADIDigitalOut intakePiston;
extern ADIDigitalOut doinker;
extern ADIDigitalOut doinker2;
extern Rotation armSensor;
extern Optical color;
extern Rotation hTracking;
extern Imu imu;
