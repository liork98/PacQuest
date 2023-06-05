#pragma once
#include <iostream>
#include "Board.h"
#include "Pacman.h"
#include "Board.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Utilities.h"
#include "Pacman.h"
#include "Point.h"
#include "Creature.h"
#include "BestGhost.h"
#include "NoviceGhost.h"
#include "GoodGhost.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;


class Game
{
private:
	enum initObjLocation {
		pacmanStartX = 1, pacmanStartY = 1,
		ghostOneStartX = 50, ghostOneStartY = 14,
		ghostTwoStartX = 10, ghostTwoStartY = 3,
		fruitStartX = 27, fruitStartY = 9
	};
	enum sleepEnum { shortPauseWindow = 2500, longPauseWindow = 4000, defalutGameSpeed = 300 };
	enum ghostLevel {novice=3, good=2, best=1};
	int userChoice = 4;
	int gameSpeedVal = 300;
	std::vector<Ghost*> ghosts;
	Fruit fruit = { fruitStartX, fruitStartY }; // NEW
	bool fruitAppear = true; // NEW
	Pacman player = { pacmanStartX , pacmanStartY };
	Board board;
	int boardToLoad = 1;
	int bcLeft = 0;
	std::vector<Creature> objects;
	std::vector<string> mapFiles = getScreenFiles();
	std::string currentMap;
	ghostLevel currentGhostLevel;

public:
	// Game functions
	void chooseGhostLevel();
	int menu();
	void printGameMenu()const;
	Game() = default;
	std::vector<string> getScreenFiles();
	bool noFiles(std::vector<string>& files);
	void handleFirstLine(size_t& currLineWidth, char& firstLetter);
	bool has_ending(std::string const& fullString, std::string const& ending);
	string chooseMap();
	bool checkValidUserInput(string userChoice)const;
	void const printInstructions();
	void initGame(string nameOfMap);
	void initGameObj();
	void initGhosts();
	void playGame(int kindOfGame, string nameOfMap, bool* ifLose);
	void playNewGame(int kind, bool* ifLose);
	void pauseGame();
	void printPreviousGame()const;
	bool checkWin()const;
	void winGame(int kindOfGame);
	void gameOver();
	void printLife()const;
	void resetPrintLife() const;
	void printScore()const;
	void printPlayerHitGhost()const;
	void removePrintPlayerHitGhost()const;
	void drawGameObj()const;
	void clearCenter()const;
	void resetGame();
	bool checkValidUserSettings(string& input) const;
	void handleGameMenuSettingsInput();
	int getGameSpeedVal() const { return gameSpeedVal; }
	char stringToChar(string& s)const;
	void fileToBoard(string nameOfMap);
	void handleObjects();
	void printScorePlusBonuses() const;
	void validFruitPoint();
	bool isLastMap(string nameOfMap);
	void resetFullGame();
	void printGarbageVal(int x, int y);

	// Ghosts functions
	bool ghostHit(Ghost& ghost);
	bool ghostsHit();
	void ghostRandomMove(Ghost& ghost);
	bool ifLastGhostPositionWasBreadcrumb(int x, int y);
	void printBreadCrumbs(int x, int y);
	void initGameAfterGhostHit();
	void ghostsMove(int countGhostMove);
	void removeGhosts();
	void removeGhost(Ghost& ghost);

	// Fruits functions
	bool fruitHitGhost(Ghost& ghost);
	bool fruitsHitGhost();
	bool fruitsHitPacman(Fruit& fruit);
	bool fruitsHitPacman();
	void fruitRandomMove(Fruit& fruit);
	void fruitIlustrateNextMove(int& x, int& y, int dir);
	bool ifLastFruitPositionWasBreadcrumb(int x, int y);
	void disappearFruit(Fruit& fruit);
	bool ifLastGhostPositionWasFruit(int x, int y);
	void fruitMove();
	bool checkFruitValidMove(int x, int y, int dir);
	void removeFruit();
	void removeFruit(Fruit& fruit);
	void printFruit(int x, int y);
	void initGameAfterFruitHit();

	// Pacman functions
	void pacmanMove();
	void getUserKeyboard();
	void removePacman();
	void setPlayerPosition(int x, int y);

};

