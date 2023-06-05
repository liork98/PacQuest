#include "NoviceGhost.h"
void NoviceGhost::changePosition(Board& b, int& countGhostMove, Point PlayerLocation, unsigned char current)
{
	if (countGhostMove % 20 == 0)
	{
		setGhostDirection(rand() % 4);
	}
	while (!checkGhostValidMove(getGhostBody().getX(), getGhostBody().getY(), getGhostDirection(), b))
	{
		setGhostDirection(rand() % 4);
	}

	move(current);
}
