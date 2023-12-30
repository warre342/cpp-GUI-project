#pragma once
#include <vector>
#include "cell.h"
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

public:
	//cells will be sideSize x SideSize
	GameManager() {
		for (int x = 0; x < screenSizeX; x += sideSize) {//somehow +1 zorgt ervoor dat ze er allemaal opstaan, momenteel geen zin om het uit te zoeken
			for (int y = 0; y < screenSizeY; y += sideSize) {//volgens berekeningen moeten het 144 objects zijn maar nu heb ik 170
				Cell blokje(x, y);
				if (x <= 960 + sideSize && x >= 960 -sideSize && y == 600) { blokje.maakLevend(); }
				else if (x <= 960 && x >= 960-2*sideSize && y == 600-sideSize) { blokje.maakLevend(); }
				cells.push_back(blokje);
			}
		}	
	}

	void nextTick(){
		for (Cell &blokje : cells) {
			//check rule 1-4
			vector<Cell> neighbours = getNeighbours(blokje);
			int amountAlive = 0;
			for (Cell& neighbour : neighbours) {
				if (neighbour.getAliveState()) {
					amountAlive++;
				}
			}
			if (blokje.getAliveState()) {//levende cell
				//rule 1:
				if (amountAlive < 2) {
					blokje.setAliveState(false);
				}
				//rule 2:
				else if (amountAlive == 2 || amountAlive == 3) {
					//do nothing
				}
				//rule 3:
				else if (amountAlive > 3) {
					blokje.setAliveState(false);
				}
			}
			else {//dode cell
				//rule 4:
				if (amountAlive == 3) {
					blokje.setAliveState(true);
				}
			}
		}
	}

	vector<Cell> getAllCells();
	float getSideSize();
	vector<Cell> getNeighbours(Cell cell);


};

vector<Cell> GameManager::getAllCells() {
	return this->cells;
}

float GameManager::getSideSize() {
	return sideSize + 0.0f;
}

vector<Cell> GameManager::getNeighbours(Cell cell) {
	vector<Cell> neighbour;
	int x = cell.getX();
	int y = cell.getY();
	//deze functie let niet op edge cases waar een cel al tegen de rand zit
	//mss als je tegen de rand zit de cel aan de andere kant van het scherm nemen
	for (int i = x - sideSize; i < x + sideSize; i += sideSize) {//over alle blokjes gaan in een 3x3 zonder de middelste te pakken
		for (int j = y - sideSize; j < y + sideSize; j+= sideSize) {
			if (i != x && j != y) {
				for (Cell &blokje : cells) {
					if (blokje.getX()==i && blokje.getY()==j) {
						neighbour.push_back(cell);
					}
				}
			}
		}		
	}
	return neighbour;
}







