//-----------------------------------------------------------------------------
// Author: Adam Strutt
// Creation date: 13/02/2017
// File: Pathfinding.h
// Description: Provides all the function need for an A* pathfinder.
//-----------------------------------------------------------------------------
#include <iostream>
#include <vector>

#include "search-cell.h"
#include "vector-maths.h"

class PathFinding {
public:
//-----------------------------------------------------------------------------
// Public Variables
//-----------------------------------------------------------------------------
	bool m_intializedStartToGoal;
	bool m_foundGoal;

//-----------------------------------------------------------------------------
// Public Functions
//-----------------------------------------------------------------------------

	PathFinding();

	void findPath(Vec3 currentPos, Vec3 targartPos, int (*map)[WORLDSIZE]);
	Vec3 nextPathPos(Vec3 Obj);
	void clearOpenList();
	void clearVisitedList();
	void clearPathToGoal();

private:
//-----------------------------------------------------------------------------
// Private Variables
//-----------------------------------------------------------------------------
	SearchCell *m_startCell;
	SearchCell *m_goalCell;
	std::vector<SearchCell*> m_openList;
	std::vector<SearchCell*> m_visitedList;
	std::vector<Vec3*> m_pathToGoal;

//-----------------------------------------------------------------------------
// Private Functions
//-----------------------------------------------------------------------------
	void setStartAndGoal(SearchCell start, SearchCell goal);
	void pathOpened(int x, int y, float newCost, SearchCell *parent, int(*map)[WORLDSIZE]);
	SearchCell *getNextCell();
	void continuePath(int (*map)[WORLDSIZE]);
};
