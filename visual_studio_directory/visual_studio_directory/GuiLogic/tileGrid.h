#pragma once
#include <vector>
#include <iostream>
#include "tile.h"

class TileGrid {
private:

	std::vector<std::vector<Tile>> grid;

public:	
	static const int xMax = 16;
	static const int yMax = 9; 
	
	
	TileGrid() {
		grid.resize(yMax);
		for (int i = 0; i < yMax; i++) {
			grid[i].resize(xMax);
			for (int j = 0; j < xMax; j++) {
				Tile driehoek; 
				grid[i][j]=driehoek;
			}		
		}
	}

	Tile& getTile(int x, int y) {
		return grid[y][x];
	}
	void printGrid() {
		for (int i = 0; i < yMax; i++) {
			for (int j = 0; j < xMax; j++) {
				std::cout<< grid[i][j]; 
			}
			cout << endl; 
		}
	}


};