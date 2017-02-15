//-----------------------------------------------------------------------------
// Author: Adam Strutt
// Creation date: 13/02/2017
// File: Source.cpp
// Description: Main Loop for A* example
//-----------------------------------------------------------------------------

int sMap[20][20] = {
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 2, 2, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 },
	{ 2, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
};

#include <iostream>
#include "VectorMaths.h"
#include "PathFinding.h"

//-----------------------------------------------------------------------------
// Global variables and constants
//-----------------------------------------------------------------------------
Vec3 startPos = Vec3(18.0f, 1.0f, 0.0f);
Vec3 finishPos = Vec3(1.0f, 10.0f, 0.0f);
PathFinding path;

//-----------------------------------------------------------------------------
// Global functions
//-----------------------------------------------------------------------------
void render(void);
void menu(void);

//-----------------------------------------------------------------------------
// Name: Main
// Description: Calls the find path function. Loops until character reaches 
// the destination then prompts exit.
//-----------------------------------------------------------------------------
int main() {
	while (1) {
		path.clearOpenList();
		path.clearVisitedList();
		path.clearPathToGoal();
		menu();
		path.findPath(startPos, finishPos, sMap);
		while (!startPos.operator==(finishPos)) {
			startPos = path.nextPathPos(startPos);
			sMap[(int)startPos.y][(int)startPos.x] = 1;
			render();
		}

		char val = 'O';
		while (val != 'E') {
			std::cout << "Enter E then press Enter to Exit...\n";
			std::cin >> val;
			if (val == 'E') {
				return 0;
			}
			system("cls");
		}
	}
}

//-----------------------------------------------------------------------------
// Name: Render
// Description: Renders the map and the character’s movements. Refreshes on 
// the event of a key being pressed.
//-----------------------------------------------------------------------------
void render(void) {
	std::cin.get();
	system("cls");
	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			if (sMap[x][y] == 0) {
				std::cout << "  ";
			}
			else if (sMap[x][y] == 1) {
				std::cout << " O";
			}
			else {
				std::cout << " X";
			}
		}
		std::cout << std::endl;
	}		



}

//-----------------------------------------------------------------------------
// Name: Menu
// Description: Creates a basic start menu for the user to select the 
//				end point.
//-----------------------------------------------------------------------------
void menu(void) {
	int val;

	std::cout << "Start A* Search." << std::endl;
	while (1) {
		std::cout << "Choose your end position X coordinate (between 1 to 18): " << std::endl;
		std::cin >> val;
		finishPos.x = fabs(val);
		while (!(0 < val && val <= 18)) {
			std::cout << "Please, try again (between 1 to 18): " << std::endl;
			std::cin >> val;
			finishPos.x = fabs(val);
		}
		std::cout << "Now the Y coordinate(between 1 to 18): " << std::endl;
		std::cin >> val;
		finishPos.y = 19 - fabs(val);
		while (!(0 < val && val <= 18)) {
			std::cout << "Please, try again (between 1 to 18): " << std::endl;
			std::cin >> val;
			finishPos.y = 19 - fabs(val);
		}
		if (!(sMap[(int)finishPos.y][(int)finishPos.x] == 2)) {
			return;
		}
		system("cls");
		std::cout << "You have picked a wall please pick a new position." << std::endl;
	}
}