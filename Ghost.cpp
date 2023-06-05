#include "Ghost.h"

/* This function remove ghost from board and draw it in the new place by direction*/
void Ghost::move(unsigned char current)
{
	ghostBody.draw(current);
	ghostBody.move(direction);

	draw();
}

/* This function draw the ghost in current location*/
void Ghost::draw() const
{
	setTextColor(color);
	ghostBody.draw(ghostIcon);
}

/* This function get x,y and set it to ghost*/
void Ghost::setGhostBody(int newX, int newY)
{
	ghostBody.setX(newX);
	ghostBody.setY(newY);
}

/* This function return ghost Point (x,y)*/
Point Ghost::getGhostBody() const
{
	return ghostBody;
}

/* This function set ghost direction*/
void Ghost::setGhostDirection(int direction)
{
	this->direction = direction;
}

/* This function change ghost color*/
void Ghost::setColor(Color color)
{
	this->color = color;
}

/* This function init ghost*/
void Ghost::initGhost()
{
	this->color = Color::WHITE;
	this->direction = 3;
}

/* This function check if ghost next move is valid */
bool Ghost::checkGhostValidMove(int x, int y, int dir, Board& board)
{
	ghostIlustrateNextMove(x, y, dir);
	unsigned char charAtNextPoint = board.getBoardValFromPoint(x, y);

	// If the ghost out of board
	if ((x == 79) || (x == 0) || (y == 0) || (y == 24))
		return false;

	// If the next move is wall, tunnel or ghost this isn't valid move
	if ((charAtNextPoint == w) || (charAtNextPoint == space) || (charAtNextPoint == ghostIcon))
		return false;

	return true;
}

void Ghost::ghostIlustrateNextMove(int& x, int& y, int dir)
{
	switch (dir)
	{
	case 0: // LEFT
		x--;
		break;
	case 1: // RIGHT
		x++;
		break;
	case 2: // UP
		y--;
		break;
	case 3: // DOWN
		y++;
		break;
	}
}
	
	void Ghost::chaseAfterPacman(Board& b, int& countGhostMove, Point PlayerLocation)
	{
		int pacX = PlayerLocation.getX();
		int pacY = PlayerLocation.getY();
		
		if (pacX == this->ghostBody.getX())
		{ 
			if (pacY < ghostBody.getY())
			setGhostDirection(2);
			else
			setGhostDirection(3);

		}
		else
		{
			if (pacX < ghostBody.getX())
				setGhostDirection(0);
			else if (pacX > ghostBody.getX())
				setGhostDirection(1);

		}
	
	}
