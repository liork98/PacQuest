#pragma once
#include "Point.h"
#include "Board.h"
#include <random>


class Ghost
{
	enum sizeEnum { WIDTH = 80, HEIGHT = 24 };
	// Ghost data members
	Point ghostBody;
	Color color = Color::WHITE;
	int direction = 3;

public:
	// Constractor
	Ghost();
	Ghost(int newX, int newY) : ghostBody(newX, newY) {};
	virtual ~Ghost() {};
	// Ghost functions
	void move(unsigned char current);
	void draw() const;
	void setGhostBody(int newX, int newY);
	 Point getGhostBody() const;
	 int getGhostDirection() { return direction; };
	void setGhostDirection(int direction);
	Color getColor() const { return color; };
	void setColor(Color color);
	void initGhost();
	virtual void changePosition(Board& b, int& countPacmanMoves, Point PlayerLocation, unsigned char current) = 0;
	bool checkGhostValidMove(int x, int y, int dir, Board& board);
	void chaseAfterPacman(Board& b, int& countPacmanMoves, Point PlayerLocation);
	void ghostIlustrateNextMove(int& x, int& y, int dir);
};

