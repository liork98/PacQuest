#pragma once
#include "Ghost.h"

class GoodGhost :public Ghost
{
public:
	GoodGhost(int x, int y) :Ghost( x,  y) {};
	~GoodGhost() override {}
	void changePosition(Board& b, int& countGhostMove, Point PlayerLocation, unsigned char current);
}; 