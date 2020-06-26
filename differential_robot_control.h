#ifndef DIFFERENTIAL_ROBOT_CONTROL_H
#define DIFFERENTIAL_ROBOT_CONTROL_H

static bool b_is_first_time = true;

void drive_robot(int clientID, int rightMotorHandle, int leftMotorHandle, double desiredVelocity, double desiredAngularVelocity);
void stop_robot(int clientID, int rightMotorHandle, int leftMotorHandle);

#endif // !DIFFERENTIAL_ROBOT_CONTROL_H
