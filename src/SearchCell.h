//-----------------------------------------------------------------------------
// Author: Adam Strutt
// Creation date: 13/02/2017
// File: SearchCell.h
// Description: Creates a Struct to so variable can be assigned to individual cells.
//-----------------------------------------------------------------------------
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
	bool Wall;				// Defines if the cell can be passed through

	SearchCell() : parent(0), Wall(false){}
	SearchCell(int x, int y, SearchCell *_parent = 0) : xCoord(x), yCoord(y), parent(_parent), id(y * WORLDSIZE + x), G(0), H(0), Wall(false) {};

	float getF() { return G + H; }
	float manHattanDistance(SearchCell *nodeEnd)
	{
		float x = (float)(fabs((float)this->xCoord - nodeEnd->xCoord));
		float y = (float)(fabs((float)this->yCoord - nodeEnd->yCoord));
		// Updated to include Diagonal Shortcut(more computational power)
		if (x > y) {
			return (1.414 * y) + (x - y);
		}
		else {
			return (1.414 * x) + (y - x);
		}
	}
	 
};
