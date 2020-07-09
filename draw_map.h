#ifndef DRAW_MAP_INCLUDED_H
#define DRAW_MAP_INCLUDED_H

#define X_MAX				61
#define Y_MAX				61
#define MAPPING_SCALE		((X_MAX - 1) / 2)

struct MyNodes
{
	int x;
	int y;
	int cost;
	int h; // heuristic cost
	int g; // g cost
	int f; // f cost
	bool b_obstacle = false;
	bool b_visited = false;
	int parentNode;
};

void initialize_map();
void read_map();
void printMap();

#endif // !DRAW_MAP_INCLUDED_H
