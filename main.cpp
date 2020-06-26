#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "robot_parameters.h"
#include "differential_robot_control.h"

extern "C" {
#include "extApi.h"
}

using namespace std;

int leftMotorHandle = 0;
int rightMotorHandle = 0;

double robot_desired_velocity = 0.1;
// double robot_desired_angular_velocity = PI/-30.0;

int main(int argc, char** argv)
{
	int clientID = 0;
	char input_value = ' ';

	simxFinish(-1);
	clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 5000, 5);
	Sleep(1);

	if (clientID != -1)
	{
		cout << "Connection status to Coppeliasim: SUCCESS" << endl;
		int returnValue = 0;

		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_rightMotor", &rightMotorHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_leftMotor", &leftMotorHandle, simx_opmode_blocking);

		//drive_robot(clientID, rightMotorHandle, leftMotorHandle, robot_desired_velocity, robot_desired_angular_velocity);
		//Sleep(5000);
		//drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);

		while ( input_value = _getch() )  // this waits until character enetered
		{
			if (input_value == '+') // increase linear speed
			{
				if (robot_desired_velocity < MAX_VELOCITY)	robot_desired_velocity += VELOCITY_STEP;
			}
			else if (input_value == '-') // decrease linear speed
			{
				if (robot_desired_velocity > MIN_VELOCITY)	robot_desired_velocity -= VELOCITY_STEP;
			}
			else if (input_value == 'f')
			{
				// drive forward
				//drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, robot_desired_velocity, 0.0);
			}
			else if (input_value == 'b')
			{
				// drive backward
				//drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, -1.0 * robot_desired_velocity, 0.0);
			}
			else if (input_value == 'r')
			{
				// turn right
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, -1.0 * STEER_ANGLE);
			}
			else if (input_value == 'l')
			{
				// turn left
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, STEER_ANGLE);
			}
			else if (input_value == 's')
			{
				// stop robot
				drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
			}
			else if (input_value == 'q')
			{
				//save map 
				break;
			}
		}
	}
	else
	{
		cout << "Connection status to Coppeliasim: FAILED" << endl;
	}
	return 0;
}