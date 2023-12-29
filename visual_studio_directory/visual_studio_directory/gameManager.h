#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <stdexcept>
#include <memory>
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
	int amountOfCells=0;
	vector<Cell> cells; 
	const static int screenSizeX = 1920;
	const static int screenSizeY = 1080; 
	const static int sideSize = 8;




public:
	//cells will be 8 by 8
	GameManager() {
		for (int x = 0; x < screenSizeX; x += 8) {
			for (int y = 0; y < screenSizeY; y += 8) {
				Cell blokje(x, y);
				this->addCell(blokje);
			}
		}	
	}

	void nextTick(){
		for (Cell blokje : cells) {
			//check rule 1-4
		
		
		}
	
	
	}

	void addCell(Cell cell);
	vector<Cell> getAllCells();
	vector<Cell> getNeighbours(Cell cell);


};

vector<Cell> GameManager::getAllCells() {
	return cells;
}
void GameManager::addCell(Cell cell) {
	cells.push_back(cell);
	amountOfCells++;
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
				for (Cell &blokje : cells) {//todo:optimizen met const somehow
					if (blokje.getX()==i && blokje.getY()==j) {
						neighbour.push_back(cell);
					}
				}
			}
		}		
	}
}







