#include "Fruit.h"

/* This function remove fruit from board and draw it in the new place by direction*/
void Fruit::move()
{
	fruitBody.draw(space);
	fruitBody.move(direction);
	draw();
}

int Fruit::getFruitNumber()
{
	return number;
}

/* This function draw the ghost in current location*/
void Fruit::draw() const
{
	setTextColor(color);
	fruitBody.fruitDraw(number);
}

void Fruit::renumber()
{
	number = 5 + rand() % 5;
}

/* This function get x,y and set it to ghost*/
void Fruit::setFruitBody()
{
	fruitBody.setX(1 + rand() % 77);
	fruitBody.setY(1 + rand() % 22);
}



/* This function return ghost Point (x,y)*/
Point Fruit::getFruitBody() const
{
	return fruitBody;
}

/* This function set ghost direction*/
void Fruit::setFruitDirection(int direction)
{
	this->direction = direction;
}

/* This function change ghost color*/
void Fruit::setColor(Color color)
{
	this->color = color;
}

/* This function init fruit*/
void Fruit::initFruit()
{
	this->color = Color::LIGHTRED;
	this->direction = 3;
	this->number = 5 + rand() % 5;
	
}

