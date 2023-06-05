#include "BestGhost.h"


void BestGhost::changePosition(Board& b, int& countGhostMove, Point PlayerLocation, unsigned char current)
{
	// Change direction according to pacman type
	chaseAfterPacman(b, countGhostMove, PlayerLocation);

	while (!checkGhostValidMove(getGhostBody().getX(), getGhostBody().getY(), getGhostDirection(), b))
	{
		setGhostDirection(rand() % 4);
	}

	move(current);
}