#pragma once

class Cell {
private: 
	bool levend=false;
	int x;
	int y; 
	
public:
	Cell(int x, int y): x(x), y(y) {}

	void maakLevend() {
		this->levend = true;
	}

	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}

	void setXY(int x, int y) {
		this->x = x;
		this->y = y;
	}
	bool getAliveState() {
		return this->levend; 
	}
	void setAliveState(bool a) {
		this->levend = a;
	}

};