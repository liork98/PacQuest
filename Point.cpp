#include "Point.h"


void Point::draw(char ch)  const {
	gotoxy(x, y);
	cout << ch;
}


void Point::fruitDraw(int number) const {
	gotoxy(x, y);
	cout << number;
}

void Point::move(int dir) {
	switch (dir) {
	case 0: // LEFT
		--x;

		break;
	case 1: // RIGHT
		++x;

		break;
	case 2: // UP
		--y;

		break;
	case 3: // DOWN
		++y;
		break;
	case 4: //Nothing

		break;
	}
}


int Point::getX()  const
{
	return x;
}


int Point::getY()  const
{
	return y;
}

bool operator== (const Point& pointOne, const Point& pointTwo)
{
	return ((pointOne.getX() == pointTwo.getX()) && (pointOne.getY() == pointTwo.getY()));
}

bool operator!= (const Point& pointOne, const Point& pointTwo)
{
	return !(pointOne == pointTwo);
}


Point& Point:: operator= (const Point& point)
{
	this->setX(point.getX());
	this->setY(point.getY());
	return *this;
}