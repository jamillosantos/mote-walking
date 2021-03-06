/**
 * @author J. Santos <jamillo@gmail.com>
 * @date September 20, 2016
 */

#ifndef WALKING_ENGINE_ROBOT_H
#define WALKING_ENGINE_ROBOT_H

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#include "../data/vector.h"
#include "../data/servo.h"
#include "../consts.h"
#include "ik.h"
#include "../configuration/configuration.h"

#define No_Motion                    0x64
#define Stop_Motion                  0x70

//internal motion number value
#define Stand_Up_Front               1
#define Stand_Up_Back                2
namespace mote
{
namespace walking
{
/*
class Ankle
{
public:
	Servo lateral;
	Servo frontal;
};

class Leg
{
public:
	Servo kneeLateral;
};

class Hip
{
public:
	Servo transversal;
	Servo lateral;
	Servo frontal;
};
*/

enum class RobotState
{
	FallenRight,
	FallenLeft,
	FallenBack,
	FallenFront,
	NormalStand
};

class Robot
{
private:
	std::unique_ptr<std::thread> _thread;

	Configuration &configuration;
	HumanoidPart _humanoid;
	HumanoidPart &_publicHumanoidPart;
	HumanoidIK ik;
	sensors::IMU& imu;

	int Check_Robot_Fall;

	/**
	 * The motion request
	 */
	int Motion_Ins;

	int System_Voltage;
	int Internal_Motion_Request;
	int Actuators_Update;

	volatile bool _running;
protected:
	int walkThreadCount;
	data::Vector3d odometer;

	RobotState getRobotState(double roll, double pitch);

	void standInitT(double speed);

	void omniGait(double vx, double vy, double vt);

	void checkRobotState();

	/**
	 * Updates internal head value.
	 *
	 * @param pan
	 * @param tilt
	 * @param panSpeed
	 * @param tiltSpeed
	 */
	void setHead(double pan, double tilt, double panSpeed, double tiltSpeed);

	void init();

public:
	Robot(Configuration &configuration, sensors::IMU &imu, HumanoidPart &humanoidPublished);

	data::Vector2td velocity;

	void start();
	void stop();

	void run();

	void updateTrajectory(double vx, double vy, double vt, double t);

	void nop(int times);
};
}
}


#endif //WALKING_ENGINE_ROBOT_H
