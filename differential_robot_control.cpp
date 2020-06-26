#include <Windows.h>
#include "differential_robot_control.h"
#include "robot_parameters.h"

extern "C" {
#include "extApi.h"
}

void drive_robot(int clientID, int rightMotorHandle, int leftMotorHandle, double desiredVelocity, double desiredAngularVelocity)
{
	double rightWheelVelocity = desiredVelocity + (DISTANCE_BETWEEN_WHEELS) * desiredAngularVelocity;
	double leftWheelVelocity = desiredVelocity - (DISTANCE_BETWEEN_WHEELS) * desiredAngularVelocity;

	double rightAngularVelocity = rightWheelVelocity / WHEEL_RADIUS;
	double leftAngularVelocity = leftWheelVelocity / WHEEL_RADIUS;

	//if (b_is_first_time)
	//{
		//b_is_first_time = false;
		simxSetJointTargetVelocity(clientID, rightMotorHandle, rightAngularVelocity, simx_opmode_oneshot);
		simxSetJointTargetVelocity(clientID, leftMotorHandle, leftAngularVelocity, simx_opmode_oneshot);
	//}
	//else
	//{
		//simxSetJointTargetVelocity(clientID, rightMotorHandle, rightAngularVelocity, simx_opmode_buffer);
		//simxSetJointTargetVelocity(clientID, leftMotorHandle, leftAngularVelocity, simx_opmode_buffer);
	//}

	Sleep(50);
}