#include <conio.h>
#include "keyboard_control.h"
#include "robot_parameters.h"
#include "differential_robot_control.h"

extern "C" {
#include "extApi.h"
}

double robot_desired_velocity = 0.1;
extern bool isFinished;

void control_pioneer_robot(int clientID, int& rightMotorHandle, int& leftMotorHandle)
{
	char input_value = ' ';

	while (input_value = _getch())  // this waits until character enetered
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
			while (simxSetIntegerSignal(clientID, (simxChar*) "mySignal", 1, simx_opmode_oneshot));
			drive_robot(clientID, rightMotorHandle, leftMotorHandle, 0.0, 0.0);
			isFinished = true;
			break;
		}
	}
}