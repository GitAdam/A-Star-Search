#pragma once
#include <math.h>

#define WORLDSIZE 20

struct SearchCell
{
public:
	int xCoord, yCoord;
	int id;

	SearchCell *parent;
	// Heuristic
	float G;				// Distance from the starting node
	float H;				// Distance from the end node
	bool Wall;

	SearchCell() : parent(0), Wall(false){}
	SearchCell(int x, int y, SearchCell *_parent = 0) : xCoord(x), yCoord(y), parent(_parent), id(y * WORLDSIZE + x), G(0), H(0), Wall(false) {};

	float getF() { return G + H; }
	float manHattanDistance(SearchCell *nodeEnd)
	{
		float x = (float)(fabs((float)this->xCoord - nodeEnd->xCoord));
		float y = (float)(fabs((float)this->yCoord - nodeEnd->yCoord));

		return x + y;
	}
	 
};
