#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <thread>
#include <cstdio>
#include <ctime>
#include "robot_parameters.h"
#include "differential_robot_control.h"
#include "keyboard_control.h"
#include "draw_map.h"
#include "auxiliary_functions.h"

extern "C" {
#include "extApi.h"
}

extern MyNodes* nodes;

using namespace std;

/*

	(2, 2)    (2, -2)

	(-2, 2)   (-2, -2)

	*/

bool isFinished = false;

float pioneerPosition[3] = { 0.0 };
float detectedPoint[3] = { 0.0 };

extern double robot_desired_velocity;

int main(int argc, char** argv)
{
	int clientID = 0;
	unsigned char state = 0;
	int mySignal = 0;

	int pioneerRobotHandle = 0;
	int leftMotorHandle = 0;
	int rightMotorHandle = 0;
	int ultrasonicSensor5Handle = 0;

	simxFinish(-1);
	clientID = simxStart((simxChar*)"127.0.0.1", 19999, true, true, 5000, 5);
	Sleep(1);

	initialize_map();

	if (clientID != -1)
	{
		cout << "Connection status to Coppeliasim: SUCCESS" << endl << endl;

		int returnValue = 0;
		//float oX = 0.0, oY = 0.0;
		thread thread1(control_pioneer_robot, clientID, ref(rightMotorHandle), ref(leftMotorHandle));

		
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx", &pioneerRobotHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_rightMotor", &rightMotorHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_leftMotor", &leftMotorHandle, simx_opmode_blocking);
		returnValue = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx_ultrasonicSensor5", &ultrasonicSensor5Handle, simx_opmode_blocking);

		//simxGetObjectPosition(clientID, pioneerRobotHandle, -1, pioneerPosition, simx_opmode_streaming);
		//simxReadProximitySensor(clientID, ultrasonicSensor5Handle, &state, detectedPoint, NULL, NULL, simx_opmode_streaming);

		/*while (1)
		{
			cout << pioneerPosition[0] << " " << pioneerPosition[1] << endl;
			simxGetObjectPosition(clientID, pioneerRobotHandle, -1, pioneerPosition, simx_opmode_buffer);
			Sleep(50);
		}*/

		/*clock_t start;
		double duration;
		start = clock();*/

		/*while (duration < 200)
		{
			if (state == 1)
			{
				//cout << detectedPoint[0] << " " << detectedPoint[1] << endl;
				//cout << pioneerPosition[0] << " " << pioneerPosition[1] << endl;
				//cout << "Yes" << endl;
				oX = detectedPoint[0] - pioneerPosition[0];
				oY = detectedPoint[1] - pioneerPosition[1];
				cout << "oX: " << oX << ", oY: " << oY << endl;
				int inX = (int)map(oX, -2.50, 2.50, 0.0, 1.0 * (X_MAX-1.0));
				int inY = (int)map(oY, -2.50, 2.50, 0.0, 1.0 * (Y_MAX-1.0));
				//cout << "inX: " << inX << ", inY: " << inY << endl;

				nodes[inX*Y_MAX + inY].b_obstacle = true;
			}
			//cout << pioneerPosition[0] << " " << pioneerPosition[1] << endl;
			//simxGetObjectPosition(clientID, pioneerRobotHandle, -1, pioneerPosition, simx_opmode_buffer);
			//simxReadProximitySensor(clientID, ultrasonicSensor5Handle, &state, detectedPoint, NULL, NULL, simx_opmode_buffer);
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		}*/

		while (!isFinished);

		if (thread1.joinable())
		{
			thread1.detach();
		}
	}
	else
	{
		cout << "Connection status to Coppeliasim: FAILED" << endl;
	}

	return 0;
}