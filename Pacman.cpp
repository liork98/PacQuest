#include "Pacman.h"

/* This function get the direction of the pacman*/
int Pacman::getDirection() const
{
	return direction;
}

/* This function set new direction of pacman*/
void Pacman::setDirection(int newDirection)
{
	direction = newDirection;
}

/* This function remove pacman from board and draw it in the new place by direction*/
void Pacman::move()
{
	pacmanBody.draw(space);
	pacmanBody.move(direction);
	draw();
}

/* This function draw the ghost in current location*/
void Pacman::draw() const
{
	setTextColor(color);
	pacmanBody.draw(pacmanIcon);
}

/* This function return pacman current location as Point (x,y)*/
Point Pacman::getPacmanBody() const
{
	return pacmanBody;
}

/* This function set pacman new location*/
void Pacman::setPacmanBody(int x, int y)
{
	pacmanBody.setX(x);
	pacmanBody.setY(y);
}

/* This function change pacman color*/
void Pacman::setColor(Color color)
{
	this->color = color;
}

/* This function init pacman after new game*/
void Pacman::initPacman()
{
	this->direction = 4;
	this->score = 0;
	this->life = 3;
}