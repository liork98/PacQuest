#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Utilities.h"
#include <stdlib.h>


using std::cout;

class Point
{
private:
	int x = 1, y = 1;

public:
	//constractor
	Point(int newX, int newY) : x(newX), y(newY) {};
	Point() = default;

	void draw(char ch) const;
	void fruitDraw(int number) const;
	void move(int direction);
	void setX(int newX) { x = newX; }
	int	getX() const;
	void setY(int newY) { y = newY; }
	int	getY() const;
	friend bool operator== (const Point& pointOne, const Point& pointTwo);
	friend bool operator!= (const Point& pointOne, const Point& pointTwo);
	Point& operator= (const Point& point);
};

#endif