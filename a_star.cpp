#include <iostream>
#include "a_star.h"
#include "auxiliary_functions.h"
#include "draw_map.h"
#include "robot_parameters.h"

extern "C" {
#include "extApi.h"
}

using namespace std;

int init_point, goal_point = 0;
extern MyNodes* nodes;

void init_a_star(int clientID)
{
	get_initial_and_goal_positions(clientID);

	// initialize cost of each node
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			nodes[x*Y_MAX + y].g = INF;
			nodes[x*Y_MAX + y].f = INF;
			nodes[x*Y_MAX + y].h = calculate_heuristic(x, y);
			nodes[x*Y_MAX + y].cost = abs(nodes[init_point].x - x) + abs(nodes[init_point].y - y);
		}
	}

	// g cost of start node has to be zero, so, f cost becomes eqaul to h cost. Because, f = g+h
	nodes[init_point].g = 0;
	nodes[init_point].f = calculate_heuristic(nodes[init_point].x, nodes[init_point].y);
}

void get_initial_and_goal_positions(int clientID)
{
	int res = 0;
	int pioneerRobotHandle, goalDummyHandle;
	float tempPos[3] = { 0.0 };

	res = simxGetObjectHandle(clientID, (simxChar*) "Pioneer_p3dx", &pioneerRobotHandle, simx_opmode_blocking);
	res = simxGetObjectHandle(clientID, (simxChar*) "goal_dummy", &goalDummyHandle, simx_opmode_blocking);

	res = simxGetObjectPosition(clientID, pioneerRobotHandle, -1, tempPos, simx_opmode_streaming);
	int tmpX = (int)floor(map(tempPos[0], 2.5, -2.5, 0.0, (X_MAX - 1)*1.0) + 0.5);
	int tmpY = (int)floor(map(tempPos[1], 2.5, -2.5, 0.0, (X_MAX - 1)*1.0) + 0.5);
	init_point = tmpX * X_MAX + tmpY;

	res = simxGetObjectPosition(clientID, goalDummyHandle, -1, tempPos, simx_opmode_streaming);
	tmpX = (int)floor(map(tempPos[0], 2.5, -2.5, 0.0, (X_MAX - 1)*1.0) + 0.5);
	tmpY = (int)floor(map(tempPos[1], 2.5, -2.5, 0.0, (X_MAX - 1)*1.0) + 0.5);
	goal_point = tmpX * X_MAX + tmpY;
}

int calculate_heuristic(int x, int y)
{
	int gX = nodes[goal_point].x;
	int gY = nodes[goal_point].y;

	return (abs(gX - x) + abs(gY - y));
}

int* calculate_min_f_cost() // returns minimum f cost
{
	int minFCost = INF;
	int index = 0;
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			int tmp = nodes[x*Y_MAX + y].f;
			if (tmp < minFCost)
			{
				minFCost = tmp;
				index = x * Y_MAX + y;
			}
		}
	}

	static int res[2] = { minFCost, index };
	return res;
}

bool check_node(int index)
{
	if (index != init_point && nodes[index].b_obstacle == false && 
		check_node_environment(index) && nodes[index].b_visited == false)		return true;

	return false;
}

bool check_node_environment(int index) // this is to check if there is obstacle near robot radius
{
	int tX = nodes[index].x, tY = nodes[index].y;
	for (int r = 1; r <= RADIUS; r++)
	{
		if (tY - 1 > 0)
		{
			for (int x = tX - r; x <= tX + r; x++)
			{
				if (x > 0 && x < X_MAX)
				{
					if (nodes[x*Y_MAX + tY - 1].b_obstacle)	return false;
				}
			}
		}
		if (tY + 1 < Y_MAX)
		{
			for (int x = tX - r; x <= tX + r; x++)
			{
				if (x > 0 && x < X_MAX)
				{
					if (nodes[x*Y_MAX + tY + 1].b_obstacle)	return false;
				}
			}
		}
		if (tX - 1 > 0)
		{
			for (int y = tY - r; y <= tY + r; y++)
			{
				if (y > 0 && y < Y_MAX)
				{
					if (nodes[(tX - 1)*Y_MAX + y].b_obstacle)	return false;
				}
			}
		}
		if (tX + 1 < X_MAX)
		{
			for (int y = tY - r; y <= tY + r; y++)
			{
				if (y > 0 && y < Y_MAX)
				{
					if (nodes[(tX + 1)*Y_MAX + y].b_obstacle)	return false;
				}
			}
		}
	}

	return true;
}

void update_costs(int current, int index)
{
	if (check_node(index))
	{
		int t = nodes[current].g + abs(nodes[current].cost - nodes[index].cost);
		if (t < nodes[index].g)
		{
			nodes[index].g = t;
			nodes[index].f = nodes[index].g + nodes[index].h;
			nodes[index].parentNode = current;
		}
	}
}

void solve_a_star(int clientID)
{
	while (true)
	{
		// get minimum f value
		int* tmp = calculate_min_f_cost();
		int minfValue = tmp[0];
		int current = tmp[1];

		// check whether you reached the goal
		if (current == goal_point)	break;

		// indicate current node as visited
		nodes[current].b_visited = true;

		// visit each neighbour
		// get x and y coordinates
		// neighbours: (x-1, y) (x+1, y) (x, y-1) (x, y+1)
		int x_ = nodes[current].x;
		int y_ = nodes[current].y;
		
		if (x_ > 0)						update_costs(current, (x_ - 1) * Y_MAX + y_);
		if (x_ < (X_MAX-1))				update_costs(current, (x_ + 1) * Y_MAX + y_);
		if (y_ > 0)						update_costs(current, x_ * Y_MAX + y_ - 1);
		if (y_ < (Y_MAX-1))				update_costs(current, x_ * Y_MAX + y_ + 1);

		nodes[current].f = INF;
	}	

}