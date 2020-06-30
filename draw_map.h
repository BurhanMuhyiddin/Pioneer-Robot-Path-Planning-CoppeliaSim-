#ifndef DRAW_MAP_INCLUDED_H
#define DRAW_MAP_INCLUDED_H

#define X_MAX				61
#define Y_MAX				61
#define MAPPING_SCALE		((X_MAX - 1) / 2)

struct MyNodes
{
	int x;
	int y;
	bool b_obstacle = false;
	int parentNode;
};

void initialize_map();
void printMap();

#endif // !DRAW_MAP_INCLUDED_H
