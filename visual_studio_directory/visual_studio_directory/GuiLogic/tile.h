#pragma once
#include <iostream>

using namespace std; 
class Tile {

private: 
	bool state;

public:
	Tile(): state(false) {}

	bool isActive ()const { return state; }
	void toggle() { state = !state; }

	friend ostream& operator<<(ostream& os, Tile const& t) {
		if (t.state) { return os << "- "; }
		else { return os << "x "; }
	}

};