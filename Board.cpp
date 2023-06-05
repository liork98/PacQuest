#include "Board.h"

/* This function print the board*/
void const Board::printBoard() const
{
    for (int i = 0; i < HIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            cout << board[i][j];
        }
            
        cout << endl;
    }
};
void Board::resetHeight()
{
    boardHeight = 0;
}
/* This function print the previous board before pausing*/
void Board::printPreviousBoard() const
{
    for (int i = 0; i < HIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == boardGarbageVal)
                cout << (char)space;
            else
                cout << board[i][j];
        }
        cout << endl;
    }
}

/* This function reset the board to the begining*/
void Board::resetBoard()
{

    for (int i = 0; i < HIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (board[i][j] == boardGarbageVal)
                board[i][j] = bc;
        }
    }


}

/* This function get the line from the board*/
void Board::setBoardLine(const char* currFileLine, int rowNum, std::vector<Creature>& objects, int* breadCrumbsLeft)
{
    Point tmp;
    Creature tmp2;
    for (int x = 0; x < WIDTH; x++)
    {
        if ((x==0 || x==79 || rowNum ==0 || rowNum == 23) && (currFileLine[x] ==space))
        {
               board[boardHeight][x] = space;
        }
        else if (currFileLine[x] == space) // BreadCrumb
        {
            board[boardHeight][x] = bc;
           (*breadCrumbsLeft)++;
        }
            else if (currFileLine[x] == static_cast<unsigned char>('#')) // Wall
                board[boardHeight][x] = w;
            else if (currFileLine[x] == static_cast<unsigned char>('%')) // Clean game area
                board[boardHeight][x] = space;
                
            else if (currFileLine[x] == static_cast<unsigned char>('$')) // Ghost
        {
            tmp = Point(x, boardHeight);
            tmp2 = Creature(tmp, 'G');
            objects.push_back(tmp2);
            handleGhost(boardHeight, x);
        }
            else if (currFileLine[x] == static_cast<unsigned char>('@')) // Pacman
        {
            tmp = Point(x, boardHeight);
            tmp2 = Creature(tmp, 'P');
            objects.push_back(tmp2);
             handlePacman(boardHeight, x);
        }
            else // Invalid char in the file
                cout << "Invalid char: " << currFileLine[x] << endl;
      
    }
    boardHeight++;
}


void Board::handleGhost(int boardHeight, int x)
{
    board[boardHeight][x] = ghostIcon;
}

/* This function handle getting pacman in file*/
void Board::handlePacman(int boardHeight, int x)
{
    pacmanStartingPosition = { x, boardHeight };
    // Updating the position of the pacman
    board[boardHeight][x] = pacmanIcon;
}



unsigned char Board::getPoint(int x, int y)
{
    return board[y][x];
}

