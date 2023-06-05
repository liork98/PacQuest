#pragma once
#include "Ghost.h"

class NoviceGhost :public Ghost
{
public:
	NoviceGhost(int x, int y) :Ghost(x, y) {};
	~NoviceGhost() override {}
	void changePosition(Board& b, int& countGhostMove, Point PlayerLocation, unsigned char current) override;
};