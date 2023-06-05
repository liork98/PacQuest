#include "GoodGhost.h"
void GoodGhost::changePosition(Board& b, int& countGhostMove, Point PlayerLocation,unsigned char current)
{
	int x = this->getGhostBody().getX();
	int y = this->getGhostBody().getY();
	int direction = getGhostDirection();
	if (countGhostMove % 20 >= 0 && countGhostMove % 20 <= 5)
	{
		if (countGhostMove % 20 == 0)
			direction = rand() % 4;

		// If not valid get new random direction
		while (!checkGhostValidMove(x, y, direction, b))
			direction = rand() % 4;
		this->setGhostDirection(direction);
		move(current);
	}
	else
	{

		chaseAfterPacman(b, countGhostMove, PlayerLocation);

		while (!checkGhostValidMove(getGhostBody().getX(), getGhostBody().getY(), getGhostDirection(), b))
		{
			setGhostDirection(rand() % 4);
		}

		move(current);
		
	}
}