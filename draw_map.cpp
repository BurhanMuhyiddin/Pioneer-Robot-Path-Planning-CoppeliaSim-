#include "draw_map.h"
#include <iostream>

using namespace std;

MyNodes* nodes = nullptr;

void initialize_map()
{
	nodes = new MyNodes[X_MAX * Y_MAX];

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			nodes[x*Y_MAX + y].x = x;
			nodes[x*Y_MAX + y].y = y;
			nodes[x*Y_MAX + y].b_obstacle = false;
		}
	}

	//printMap();
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