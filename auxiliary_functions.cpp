#include <iostream>
#include "auxiliary_functions.h"

using namespace std;

float calculate_distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}