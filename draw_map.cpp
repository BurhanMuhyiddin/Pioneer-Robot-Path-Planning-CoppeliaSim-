#include "draw_map.h"
#include <iostream>
#include <fstream>

using namespace std;

MyNodes* nodes = nullptr;

void initialize_map()
{
	nodes = new MyNodes[X_MAX * Y_MAX];

	read_map();
	//printMap();
}

void read_map()
{
	const char* path = "E:\\MyFolder\\C course\\CoppeliaSimRelated\\PioneerRobotPathPlanning\\pioneer_robot_path_planning\\pioneer_robot_path_planning\\map.txt";
	ifstream mapFile(path);
	int num = 0;

	for (int y = 0; y < Y_MAX; y++)
	{
		for (int x = 0; x < X_MAX; x++)
		{
			mapFile >> num;
			switch (num)
			{
			case 0:
				nodes[x*Y_MAX + y].x = x;
				nodes[x*Y_MAX + y].y = y;
				nodes[x*Y_MAX + y].b_obstacle = false;
				break;
			case 1:
				nodes[x*Y_MAX + y].x = x;
				nodes[x*Y_MAX + y].y = y;
				nodes[x*Y_MAX + y].b_obstacle = true;
				break;
			case 2:
				nodes[x*Y_MAX + y].x = x;
				nodes[x*Y_MAX + y].y = y;
				nodes[x*Y_MAX + y].b_obstacle = true;
				break;
			}
		}
	}
}

void printMap()
{
	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			cout << nodes[x*Y_MAX + y].x << "," << nodes[x*Y_MAX + y].y << " ";
		}
		cout << endl;
	}
}