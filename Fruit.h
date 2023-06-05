#ifndef _FRUIT_H_
#define _FRUIT_H_
#include "Point.h"
#include "Fruit.h"

class Fruit
{
	// Fruit data members
	Point fruitBody;
	Color color = Color::LIGHTRED;
	int direction = 3;
	int number;
public:
	// Constractor
	Fruit();
	Fruit(int newX, int newY) : fruitBody(newX, newY) {};

	// Fruit functions
	void move();
	void draw() const;
	void renumber();
	void setFruitBody();
	Point getFruitBody() const;
	void setFruitDirection(int direction);
	Color getColor() const { return color; };
	void setColor(Color color);
	void initFruit();
	int getFruitNumber();
};

#endif