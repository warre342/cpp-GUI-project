#pragma once
#include <vector>
#include "cell.h"
#include "GuiLogic/tileGrid.h";
/*
Rules:

Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
	
*/
using namespace std;

class GameManager {
private:

	vector<Cell> cells; 
	const static int screenSizeX = 1920;
	const static int screenSizeY = 1080; 
	const static int sideSize = 120;
	const static int aantalCells = 120;


public:
	//cells will be sideSize x SideSize
	GameManager() {//hardcoded 
		//cells.reserve(aantalCells);
		for (int x = 0; x < screenSizeX; x += sideSize) {
			for (int y = 0; y < screenSizeY; y += sideSize) {
				Cell blokje(x, y);
				if (x <= 960 + sideSize && x >= 960 -sideSize && y == 600-sideSize) { blokje.maakLevend(); }//hardcoded pattern
				else if (x <= 960 && x >= 960-2*sideSize && y == 600) { blokje.maakLevend(); }
				cells.push_back(blokje);
			}
		}	
	}

	GameManager(TileGrid & grid) {//using tileGrid
		for (int x = 0; x < screenSizeX; x += sideSize) {
			for (int y = 0; y < screenSizeY; y += sideSize) {
				Cell blokje(x, y);
				if (grid.getTile(x / sideSize, y / sideSize).isActive()) {
					blokje.maakLevend(); 
				}
				cells.push_back(blokje);

			}
		}
	
	}

	void nextTick(){

		vector<int> amountNeighboursAllCells;
		amountNeighboursAllCells.reserve(cells.size());

		for (const Cell &blokje : cells) {
			amountNeighboursAllCells.push_back(getNeighbours(blokje));
		}
		int teller = 0; 
		for (Cell &blokje : cells) {
			//check rule 1-4
			int amountAlive = amountNeighboursAllCells[teller];
			if (blokje.getAliveState()) {//levende cell
				//rule 1:
				if (amountAlive < 2) {
					blokje.setAliveState(false);
				}
				//rule 2:
				else if ((amountAlive == 2 )||( amountAlive == 3)) {//wordt nooit geroepen somehow
					//do nothing
				}
				//rule 3:
				else if (amountAlive > 3) {//wordt ook nooit geroepen
					blokje.setAliveState(false);
				}
			}
			else {//dode cell
				//rule 4:
				if (amountAlive == 3) {
					blokje.setAliveState(true);
				}
			}
			teller++;
		}
	}

	vector<Cell> getAllCells();
	float getSideSize();
	int getNeighbours(Cell cell);


};

vector<Cell> GameManager::getAllCells() {
	return this->cells;
}

float GameManager::getSideSize() {
	return sideSize + 0.0f;
}

int GameManager::getNeighbours(Cell cell) {
	int x = cell.getX();
	int y = cell.getY();
	int aliveTeller = 0;

	// Deze functie let niet op edge cases waar een cel al tegen de rand zit
	// Misschien als je tegen de rand zit de cel aan de andere kant van het scherm nemen
	// Over alle blokjes gaan in een 3x3 zonder de middelste te pakken
	for (int i = x - sideSize; i <= x + sideSize; i += sideSize) {
		for (int j = y - sideSize; j <= y + sideSize; j += sideSize) {
			for (Cell& el : this->cells) {
				if (el.getX() != x|| el.getY() != y) { // zolang we niet het middelste blokje hebben
					if (i == el.getX() && j == el.getY() && el.getAliveState()) {
						aliveTeller++;
					}
				}
			}
		}
	}
	return aliveTeller;
}






