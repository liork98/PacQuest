#pragma once
#include "Point.h"

class Pacman
{
private:
	// Pacman data members
	Point pacmanBody;
	int score = 0;
	int scorePlusBonuses = 0;
	int life = 3;
	int direction = 4;
	Color color = Color::WHITE;

public:
	// Constractor
	Pacman(int newX, int newY) :pacmanBody(newX, newY) {};

	// Pacman functions
	void move();
	void draw() const;

	//Getters and setters
	int getDirection() const;
	void initPacman();
	void setDirection(int newDirection);
	int	getScore() const { return score; };
	int	getScorePlusBonuses() const { return scorePlusBonuses; };
	
	void setScore(int x) { score = x; };
	void setPlusScore() { score++; scorePlusBonuses++; }
	void setPlusFruitScore(int bonus) { scorePlusBonuses = getScorePlusBonuses() + bonus; } 
	int	getLife() const { return life; };
	void setLife(int newLife) { life = newLife; };
	Point getPacmanBody() const;
	void setPacmanBody(int x, int y);
	Color getColor() const { return color; };
	void setColor(Color color);
};

