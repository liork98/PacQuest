#pragma once
#include "Ghost.h"
#include <random>
class BestGhost :public Ghost
{
public:
	//Point getGhostBody() const override {};
	BestGhost(int x, int y) :Ghost(x, y) {};
	~BestGhost() override {}
	void changePosition(Board& b, int& countGhostMove, Point PlayerLocation, unsigned char current) override;
	
};