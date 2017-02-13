#pragma once
#include <iostream>
#include <vector>

#include "SearchCell.h"
#include "VectorMaths.h"

class PathFinding {
public:
	PathFinding();
	~PathFinding();

	bool m_intializedStartToGoal;
	bool m_foundGoal;

	void findPath(Vec3 currentPos, Vec3 targartPos, int (*map)[WORLDSIZE]);
	Vec3 nextPathPos(Vec3 Obj);
	void clearOpenList();
	void clearVisitedList();
	void clearPathToGoal();

private:
	void setStartAndGoal(SearchCell start, SearchCell goal);
	void pathOpened(int x, int y, float newCost, SearchCell *parent, int(*map)[WORLDSIZE]);
	SearchCell *getNextCell();
	void continuePath(int (*map)[WORLDSIZE]);

	SearchCell *m_startCell;
	SearchCell *m_goalCell;
	std::vector<SearchCell*> m_openList;
	std::vector<SearchCell*> m_visitedList;
	std::vector<Vec3*> m_pathToGoal;
};
