//-----------------------------------------------------------------------------
// Author: Adam Strutt
// Creation date: 13/02/2017
// File: Pathfinding.cpp
// Description: Provides all the function need for an A* pathfinder.
//-----------------------------------------------------------------------------

#include "PathFinding.h"

//-----------------------------------------------------------------------------
// Name: PathFinding
// Description: Default constructor.
//-----------------------------------------------------------------------------
PathFinding::PathFinding()
{
	m_intializedStartToGoal = false;
	m_foundGoal = false;
}

//-----------------------------------------------------------------------------
// Name: findPath
// Description: If not already Initialized clears all of the main lists and 
//				initialize the start and goal position. Once Initialized it 
//				then calls the “continePath” passing in a pointer to the main 
//				map array.
//-----------------------------------------------------------------------------
void PathFinding::findPath(Vec3 currentPos, Vec3 targartPos, int(*map)[WORLDSIZE])
{
	if (!m_intializedStartToGoal) {
		for (int i = 0; i < m_openList.size(); i++) {
			delete m_openList[i];
		}
		m_openList.clear();

		for (unsigned int i = 0; i < m_visitedList.size(); i++) {
			delete m_visitedList[i];
		}
		m_visitedList.clear();

		for (unsigned int i = 0; i < m_pathToGoal.size(); i++) {
			delete m_pathToGoal[i];
		}
		m_pathToGoal.clear();

		// Initialize start
		SearchCell start;
		start.xCoord = currentPos.x;
		start.yCoord = currentPos.y;

		// Initialize goal
		SearchCell goal;
		goal.xCoord = targartPos.x;
		goal.yCoord = targartPos.y;

		setStartAndGoal(start, goal);
		m_intializedStartToGoal = true;
	}
	if (m_intializedStartToGoal) {
		continuePath(map);
	}
}

//-----------------------------------------------------------------------------
// Name: nextPathPos
// Description: Return the coordinates(Vec3) to move to and deletes the last 
//				position from the “m_pathToGoal”.
//-----------------------------------------------------------------------------
Vec3 PathFinding::nextPathPos(Vec3 Obj)
{
	if (!m_pathToGoal.empty()) {
		int index = 1;
		Vec3 nextPos = Vec3(0.0f, 0.0f, 0.0f);
		nextPos.x = m_pathToGoal[m_pathToGoal.size() - index]->x;
		nextPos.y = m_pathToGoal[m_pathToGoal.size() - index]->y;

		Vec3 distance = nextPos.operator-(Obj);	// Location of GameObj
		if (index < m_pathToGoal.size()) {
			if (distance.length() < 1.5) {	// Radius of GameObj(1.414 or greater)
				m_pathToGoal.erase(m_pathToGoal.end() - index);
			}
		}
		return nextPos;
	}
	else {
		return Obj;
	}
}

void PathFinding::clearOpenList()
{
	m_openList.clear();
}

void PathFinding::clearVisitedList()
{
	m_visitedList.clear();
}

void PathFinding::clearPathToGoal()
{
	m_pathToGoal.clear();
}

//-----------------------------------------------------------------------------
// Name: setStartAndGoal
// Description: Initializes the start and goal cell. Then saves them to 
//				the “m_openList”.
//-----------------------------------------------------------------------------
void PathFinding::setStartAndGoal(SearchCell start, SearchCell goal)
{
	m_startCell = new SearchCell(start.xCoord, start.yCoord, NULL);
	m_goalCell = new SearchCell(goal.xCoord, goal.yCoord, &goal);

	m_startCell->G = 0;
	m_startCell->H = m_startCell->manHattanDistance(m_goalCell);
	m_startCell->parent = 0;

	m_openList.push_back(m_startCell);
}

//-----------------------------------------------------------------------------
// Name: pathOpened
// Description: It moves to the next cell(“getNextCell”) and makes that its 
//				current cell. If that is the goal cell it saves the route and 
//				returns. If it is not the final cell it scans all the cells 
//				around it and saves all the new ones to the “m_openList”.
//-----------------------------------------------------------------------------
void PathFinding::pathOpened(int x, int y, float newCost, SearchCell * parent, int(*map)[WORLDSIZE])
{
	if(map[y][x] == 2)
	{
		return;
	}
	int id = y * WORLDSIZE + x;
	for (unsigned int i = 0; i < m_visitedList.size(); i++) {
		if (id == m_visitedList[i]->id) {
			return;
		}
	}

	SearchCell* newChild = new SearchCell(x, y, parent);
	if (map[x][y] == 2)
	{
		return;
	}
	newChild->G = newCost;
	newChild->H = newChild->manHattanDistance(m_goalCell);
	for (unsigned int i = 0; i < m_openList.size(); i++) {
		if (id == m_openList[i]->id) {
			float newF = newChild->G + newCost + m_openList[i]->H;

			if (m_openList[i]->getF() > newF) {
				m_openList[i]->G = newChild->G + newCost;
				m_openList[i]->parent = newChild;
			}
			else {
				delete newChild;
				return;
			}
		}
	}
	m_openList.push_back(newChild);
}

//-----------------------------------------------------------------------------
// Name: getNextCell
// Description: Loops through the “m_openList” looking for the cell with the 
//				lowest F value. Creates pointer to that cell, stores it in 
//				“m_visitedList” and removes it from “m_openList”.
//-----------------------------------------------------------------------------
SearchCell * PathFinding::getNextCell()
{
	float bestF = 999999.0f;
	int cellIndex = -1;
	SearchCell* nextCell = NULL;

	for (unsigned int i = 0; i < m_openList.size(); i++) {
		if (m_openList[i]->getF() < bestF) {
			bestF = m_openList[i]->getF();
			cellIndex = i;
		}
	}
	if (cellIndex >= 0) {
		nextCell = m_openList[cellIndex];
		m_visitedList.push_back(nextCell);
		m_openList.erase(m_openList.begin() + cellIndex);
	}
	return nextCell;
}

//-----------------------------------------------------------------------------
// Name: continuePath
// Description: It moves to the next cell(“getNextCell”) and makes that its 
//				current cell. If that is the goal cell it saves the route and 
//				returns. If it is not the final cell it scans all the cells 
//				around it and saves all the new ones to the “m_openList”.
//-----------------------------------------------------------------------------
void PathFinding::continuePath(int (*map)[WORLDSIZE])
{
	while (!m_foundGoal) {
		if (m_openList.empty()) {
			return;
		}
		SearchCell* currentCell = getNextCell();
		if (currentCell->id == m_goalCell->id) {
			m_goalCell->parent = currentCell->parent;

			SearchCell* getPath;
			for (getPath = m_goalCell; getPath != NULL; getPath = getPath->parent)
			{
				m_pathToGoal.push_back(new Vec3(getPath->xCoord, getPath->yCoord, 0.0f));
			}

			m_foundGoal = true;
			return;
		}
		else {
			// Right cell
			pathOpened(currentCell->xCoord + 1, currentCell->yCoord, currentCell->G + 1, currentCell, map);
			// Left cell
			pathOpened(currentCell->xCoord - 1, currentCell->yCoord, currentCell->G + 1, currentCell, map);
			// Top cell
			pathOpened(currentCell->xCoord, currentCell->yCoord + 1, currentCell->G + 1, currentCell, map);
			// Bottom cell
			pathOpened(currentCell->xCoord, currentCell->yCoord - 1, currentCell->G + 1, currentCell, map);

			// Top-Right cell
			pathOpened(currentCell->xCoord + 1, currentCell->yCoord + 1, currentCell->G + 1.414f, currentCell, map);
			// Top-Left cell
			pathOpened(currentCell->xCoord - 1, currentCell->yCoord + 1, currentCell->G + 1.414f, currentCell, map);
			// Bottom-Right cell
			pathOpened(currentCell->xCoord + 1, currentCell->yCoord - 1, currentCell->G + 1.414f, currentCell, map);
			// Bottom-Left cell
			pathOpened(currentCell->xCoord - 1, currentCell->yCoord - 1, currentCell->G + 1.414f, currentCell, map);

			for (unsigned int i = 0; i < m_openList.size(); i++) {
				if (currentCell->id == m_openList[i]->id) {
					m_openList.erase(m_openList.begin() + i);
				}
			}
		}
	}
}
