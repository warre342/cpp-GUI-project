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

using namespace std;

class Cell {
private: 
	bool levend=false;
	int x;
	int y; 
	const static int sideSize = 8;
	
public:
	Cell(int x, int y): x(x), y(y) {}

	void maakLevend() {
		this->levend = true;
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	}

};