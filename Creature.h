#pragma once
#include "Point.h"

class Creature
{
	Point p;
	char kind;

public:
	Creature() = default;
	Creature(Point& point, char k) { p = point, kind = k; };
	Point getPoint() { return p; };
	char getKind() { return kind; };
};

