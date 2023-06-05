#pragma once
#include <iostream>
#include <string.h>
#include "Utilities.h"
#include "Point.h"
#include <fstream>
#include "Creature.h"

class Board
{
    enum sizeEnum { WIDTH = 80, HIGHT = 24 };
    unsigned char board[HIGHT][WIDTH] = {};
    int boardWidth=0, boardHeight=0 ;
    Point pacmanStartingPosition;

public:

    void const printBoard() const;
    // This function return the value in the board of request place, the x and y that requested are opposite in the board
    unsigned char getBoardValFromPoint(int x, int y)const { return board[y][x]; };

    void setBoardValByPoint(int x, int y) { board[y][x] = boardGarbageVal; }; // Set garabge value
    void printPreviousBoard() const;
    void resetBoard();
    void setBoardLine(const char* currFileLine, int rowNum, std::vector<Creature>& objects, int* breadCrumbsLeft);
    void setBoardWidth(int width) { boardWidth = width; };
    void handlePacman(int boardHeight, int x);
    void handleGhost(int boardHeight, int x);
    unsigned char getPoint(int x, int y);
    void resetHeight();
};

