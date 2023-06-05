#include "Game.h"


/* This function get user choice of menu*/
int Game::menu()
{
	printGameMenu();
	string input;
	//getchar();
	getline(cin, input);
	/* If the user enter invalid option clear and ignore cin input */
	while (!checkValidUserInput(input))
	{
		clearScreen();
		
		cout << "You enterd incorrect option, please choose again.\n\n";
		printGameMenu();
		getline(cin, input);
	}
	userChoice = stoi(input);

	return userChoice;
}

void Game::printGameMenu() const
{
	cout << "Welcome to PacmanGame \n"
		"(1) Start a new game\n"
		"(2) choose specific map\n"
		"(8) Present instructions and keys\n"
		"(9) EXIT\n";
}

// This function get data from th screen file and put the data in the right objects
void Game::fileToBoard(string nameOfMap)
{

	board.resetHeight();
	std::ifstream inputFile;
	inputFile.open(nameOfMap);
	size_t currLineWidth = 0;
	int rowHightInFile = 0;
	string currLine;
	string emptyLine = "                                                                                ";
	while (std::getline(inputFile, currLine))
	{
		currLineWidth = currLine.length();

		// Get the width of the board by the first line of the file
		if (rowHightInFile == 0)
		{
			handleFirstLine(currLineWidth, currLine[0]);
			board.setBoardWidth(currLineWidth);
		}

		if (currLineWidth != 0)
			board.setBoardLine(currLine.c_str(), rowHightInFile, objects, &bcLeft);
		else // emptyLine
			board.setBoardLine(emptyLine.c_str(), rowHightInFile, objects, &bcLeft);
		rowHightInFile++;

	}
	handleObjects();
	inputFile.close();
}

void Game::handleObjects()
{
	std::vector<Creature>::iterator itr = objects.begin();
	std::vector<Creature>::iterator itrEnd = objects.end();

	int arrrSize = objects.size();
	if (arrrSize != 0)
	{
		
		for (auto it = itr; it != itrEnd; ++it)
		{
			if ((*it).getKind() == 'P')
			{
				player = { (*it).getPoint().getX(), (*it).getPoint().getY() };
			}
			else if ((*it).getKind() == 'G') // "B" // Best ghost
			{
				Ghost* curGhost;
				if (currentGhostLevel == 1)
				{
					curGhost = new BestGhost((*it).getPoint().getX(), (*it).getPoint().getY());
				}
				if (currentGhostLevel == 2)
				{
					curGhost = new GoodGhost((*it).getPoint().getX(), (*it).getPoint().getY());
				}
				if (currentGhostLevel == 3)
				{
					curGhost = new NoviceGhost((*it).getPoint().getX(), (*it).getPoint().getY());
				}
				ghosts.push_back(curGhost);


			
			}
		}
	}

}
void Game::handleFirstLine(size_t& currLineWidth, char& firstLetter)
{
	// If the first line of the screen is \n
	if (currLineWidth == 0)
	{
		cout << "The width of the screen is too short, moving to the next screen" << endl;
		Sleep(2500);
	}
	else if ((currLineWidth == 1))
		currLineWidth = 24;
	// If the first line is more than 80 chars limit it to 80
	else if (currLineWidth > 80)
		currLineWidth = 80;
}


/* This function handle the game*/
void Game::playGame(int kindOfGame, string nameOfMap, bool* ifLose)
{
	currentMap = nameOfMap;
	int countGhostMove = 0;
	int countFruitMove = 0;
	int countPacmanMove = 0;
	int countTimeDisappearing = 0;
	bool b_won = false;


	initGame(nameOfMap);

	while ((player.getLife() > 0) && (!b_won))
	{
		countTimeDisappearing++;
		printScore();
		if (ghostsHit())
			initGameAfterGhostHit();
		else if (fruitsHitPacman())
		{
			if (fruitAppear)
			{
				initGameAfterFruitHit();
				countTimeDisappearing = 0;
				fruit.initFruit();
				validFruitPoint();
			}

		}
		else if (fruitsHitGhost())
		{
			removeFruit();
			countTimeDisappearing = 0;
			fruit.initFruit();
			validFruitPoint();
			fruitAppear = false;
			fruitMove();
		}
		if (countGhostMove == 2) // Control speed
		{
			ghostsMove(countGhostMove);
			countGhostMove = 0;
			fruitMove();
			countFruitMove = 0;
			
		}
		if (!fruitAppear)
		{
			disappearFruit(fruit);
		}
		if (countTimeDisappearing == 25 && !fruitAppear)
		{
			fruitAppear = true;
			countTimeDisappearing = 0;
			fruit.initFruit();
			validFruitPoint();
			
		}
		if (countTimeDisappearing == 25 && fruitAppear)
		{
			countTimeDisappearing = 0;
			fruit.initFruit();
			fruitAppear = false;
			fruitMove();
		}
		//else
		{
			Sleep(gameSpeedVal);
			pacmanMove();
			countPacmanMove++;
			countGhostMove++;
			countFruitMove++;
		}
			

		if (checkWin())
		{
			b_won = true;
			printScore();
			printScorePlusBonuses();

			winGame(kindOfGame);

		}
	}

	// If lose
	if (player.getLife() == 0)
	{
		gameOver();
		*ifLose = true;

	}
		
}

void Game::playNewGame(int kind, bool* ifLose)
{
	std::vector<string>::iterator itr = mapFiles.begin();
	std::vector<string>::iterator itrEnd = mapFiles.end();
	for (auto it = itr; it != itrEnd && !(*ifLose); ++it)
	{
		playGame(0, (*it), ifLose);
	}
}


std::vector<string> Game::getScreenFiles()
{
	std::vector<string> result;
	std:: vector<string>::iterator resultitr = result.begin();
	for (const auto& entry : fs::directory_iterator(".")) {
		if (has_ending(entry.path().string(), "screen")) {
			std::string filePath = entry.path().string();
			if (filePath.length() > 2) {
				result.push_back(filePath.substr(2)); // Append substring starting from the 3rd character
			}
		}
	}
	return result;
}

bool Game::has_ending(std::string const& fullString, std::string const& ending) {
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

/* This fnction init the game*/
void Game::initGame(string nameOfMap)
{
	clearScreen();
	fileToBoard(nameOfMap);
	board.printBoard();
	initGameObj();
	drawGameObj();
	printScore();
	printLife();
}

/* This function init the game after ghost hit pacman*/
void Game::initGameAfterGhostHit()
{
	player.setLife(player.getLife() - 1);
	printLife();

	if (player.getLife() > 0)
	{
		printPlayerHitGhost();
		Sleep(shortPauseWindow);
		removePrintPlayerHitGhost();
		removeGhosts();
		removePacman();
		player.setPacmanBody(player.getPacmanBody().getX(), player.getPacmanBody().getY());
		player.setDirection(4);

		std::vector<Ghost*>::iterator itr = ghosts.begin();
		std::vector<Ghost*>::iterator itrEnd = ghosts.end();

		for (auto it = itr; it != itrEnd; ++it)
		{
			(**it).setGhostBody((**it).getGhostBody().getX(), (**it).getGhostBody().getY());
			ghostRandomMove((**it));
			ghostRandomMove((**it));
		}
		
		drawGameObj();
	}
}

/* This function init the game after pacman hit fruit*/
void Game::initGameAfterFruitHit()
{
	player.setPlusFruitScore(fruit.getFruitNumber());
	printScore();
	removeFruit();
	fruitAppear = false;
	
}



void Game::printPlayerHitGhost() const
{
	
	setTextColor(Color::RED);
	gotoxy(26, 29);
	cout << "You hit the ghost!" << endl;
}

void Game::removePrintPlayerHitGhost() const
{
	gotoxy(26, 29);
	cout << "                     ";
}

/* This function remove pacman last character after ghost hit*/
void Game::removePacman()
{
	gotoxy(player.getPacmanBody().getX(), player.getPacmanBody().getY());
	cout << (char)space;
}

/* This function remove ghosts last character after pacman hit*/
void Game::removeGhosts()
{
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		removeGhost(**it);
	}
	

}

/* This function remove fruit last character after pacman hit*/
void Game::removeFruit()
{
	removeFruit(fruit);
}

/* This function remove ghost last character after pacman hit*/
void Game::removeGhost(Ghost& ghost)
{
	int x = ghost.getGhostBody().getX();
	int y = ghost.getGhostBody().getY();
	gotoxy(x, y);
	if (ifLastGhostPositionWasBreadcrumb(x, y))
		printBreadCrumbs(x, y);
	else
		cout << (char)space;
}

/* This function remove fruit last character after hitted*/
void Game::disappearFruit(Fruit& fruit)
{
	int x = fruit.getFruitBody().getX();
	int y = fruit.getFruitBody().getY();
	gotoxy(x, y);
	if (ifLastFruitPositionWasBreadcrumb(x, y))
		printBreadCrumbs(x, y);
	else
		cout << (char)space;
}

/* This function remove fruit last character after pacman hit*/
void Game::removeFruit(Fruit& fruit)
{
	int x = fruit.getFruitBody().getX();
	int y = fruit.getFruitBody().getY();
	gotoxy(x, y);
	if (ifLastGhostPositionWasBreadcrumb(x, y))
		printBreadCrumbs(x, y);
	else
		cout << (char)space;
	fruit.renumber(); // New random 5-9 number
}

/* This function get the user key board hit*/
void Game::getUserKeyboard()
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();

		// Down
		if ((ch == 'x') || (ch == 'X'))
			player.setDirection(3);

		// UP
		else if ((ch == 'w') || (ch == 'W'))
			player.setDirection(2);

		// Left
		else if ((ch == 'a') || (ch == 'A'))
			player.setDirection(0);

		// Right
		else if ((ch == 'd') || (ch == 'D'))
			player.setDirection(1);

		// Stay
		else if ((ch == 's') || (ch == 'S'))
			player.setDirection(4);

		// ESC 
		else if (ch == 27)
		{
			pauseGame();
			printPreviousGame();
		}
	}
}

/* This function handle paused game*/
void Game::pauseGame()
{
	char ch = 0;
	bool b_Continue = false;

	setTextColor(Color::WHITE);
	clearCenter();
	gotoxy(27, 9);
	cout << "Game paused!";
	gotoxy(27, 11);
	cout << "Press ESC to continue";

	while (!b_Continue)
	{
		if (_kbhit())
		{
			ch = _getch();
			if (ch == 27)
				b_Continue = true;
		}
	}
}

/* This function handle pacman move*/
void Game::pacmanMove()
{
	getUserKeyboard();

	int x = player.getPacmanBody().getX();
	int y = player.getPacmanBody().getY();

	Point nextPos = player.getPacmanBody();
	nextPos.move(player.getDirection());


	unsigned char charAtnextPoint = board.getBoardValFromPoint(nextPos.getX(), nextPos.getY());
	unsigned char charAtPoint = board.getBoardValFromPoint(x, y);

	// If player is going through tunnel
	if (charAtnextPoint == space)
	{
		if (charAtPoint == bc) // if there was at curr pos then raise score
		{
			player.setPlusScore();
			player.setPlusFruitScore(0);
			board.setBoardValByPoint(x, y);
		}

		if (x == 1) {
			player.getPacmanBody().draw(space);
			player.setPacmanBody(79, y);
		}

		else if (x == 78) {
			player.getPacmanBody().draw(space);
			player.setPacmanBody(0, y);
		}
		else if (y == 1)
		{
			player.getPacmanBody().draw(space);
			player.setPacmanBody(x, 23);
		}
		else if (y == 22)
		{
			player.getPacmanBody().draw(space);
			player.setPacmanBody(x, 0);
		}
		player.move();
	}

	// if there is wall in the next move
	else if (charAtnextPoint == w)
		player.setDirection(4);
	else
	{
		// if there breadcrumb
		if (charAtPoint == bc)
		{
			player.setPlusScore();
			player.setPlusFruitScore(0);
		}
		board.setBoardValByPoint(x, y);
		player.move();
	}
}

/* This function check if the ghost hit the pacman*/
bool Game::ghostsHit()
{
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		if (ghosts.size() == 1)
			return (ghostHit(**it));
		if (ghosts.size() == 2)
			return (ghostHit(**it) || ghostHit(**(++it)));
		if (ghosts.size() == 3)
			return (ghostHit(**it) || ghostHit(**(++it)) || ghostHit(**(++it)));
		if (ghosts.size() == 4)
			return (ghostHit(**it) || ghostHit(**(++it)) || ghostHit(**(++it)) || ghostHit(**(++it)));
	}
}

/* This function check if the fruit hit the pacman*/
bool Game::fruitsHitPacman()
{
	return(fruitsHitPacman(fruit));
}

/* This function check if the fruit hit a ghost*/
bool Game::fruitsHitGhost()
{
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		if (ghosts.size() == 2)
			return (fruitHitGhost(**it) || fruitHitGhost(**(++it)));
		if (ghosts.size() == 3)
			return (fruitHitGhost(**it) || fruitHitGhost(**(++it)) || fruitHitGhost(**(++it)));
		if (ghosts.size() == 4)
			return (fruitHitGhost(**it) || fruitHitGhost(**(++it)) || fruitHitGhost(**(++it)) || fruitHitGhost(**(++it)));
	}
	
}


/* This function handle ghost hit*/
bool Game::ghostHit(Ghost& ghost)
{
	if (ghost.getGhostBody() == player.getPacmanBody())
		return true;
	return false;
}

/* This function handle ghost and fruit hit*/
bool Game::fruitHitGhost(Ghost& ghost)
{
	if (ghost.getGhostBody() == fruit.getFruitBody())
		return true;
	return false;
}

/* This function handle fruit hit*/
bool Game::fruitsHitPacman(Fruit& fruit)
{
	if (fruit.getFruitBody() == player.getPacmanBody())
		return true;
	return false;
}

/* This function handle ghosts move*/
void Game::ghostsMove(int countGhostMove)
{
	unsigned char current;
	int numOfGhosts = ghosts.size();
	int countMoves = countGhostMove;
	Point PlayerLocation = { player.getPacmanBody().getX(), player.getPacmanBody().getY() };

	std::vector<Ghost*>::const_iterator itr = ghosts.begin();
	std::vector<Ghost*>::const_iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		if (ifLastGhostPositionWasBreadcrumb((*it)->getGhostBody().getX(), (*it)->getGhostBody().getY()))
		{
			printBreadCrumbs((*it)->getGhostBody().getX(), (*it)->getGhostBody().getY());
			current = bc;
		}
			
		else
		{
			printGarbageVal((*it)->getGhostBody().getX(), (*it)->getGhostBody().getY());
			current = space;
		}
			



		(*it)->changePosition(board, countGhostMove, player.getPacmanBody(), current);
		
	}
}

/* This function handle fruit move*/
void Game::fruitMove()
{
	fruitRandomMove(fruit);

}

/* This function handle ghost random move*/
void Game::ghostRandomMove(Ghost& ghost)
{
	int x = ghost.getGhostBody().getX();
	int y = ghost.getGhostBody().getY();
	int direction = rand() % 4;

	// If wall get new random direction
	while (!(ghost.checkGhostValidMove(x, y, direction, board)))
		direction = rand() % 4;

	ghost.setGhostDirection(direction);
	// If last ghost position was breadcrumb print breadcrumb
	if (ifLastGhostPositionWasBreadcrumb(x, y))
	{
		printBreadCrumbs(x, y);
		ghost.move(bc);
	}
	else
	{
		ghost.move(space);
		cout << (char)space;
	}
	

	
}



/* This function handle fruit random move*/
void Game::fruitRandomMove(Fruit& fruit)
{
	int x = fruit.getFruitBody().getX();
	int y = fruit.getFruitBody().getY();
	int direction = rand() % 4;

	// If wall get new random direction
	while (!checkFruitValidMove(x, y, direction))
		direction = rand() % 4;

	fruit.setFruitDirection(direction);
	fruit.move();

	// If last ghost position was breadcrumb print breadcrumb
	if (ifLastFruitPositionWasBreadcrumb(x, y))
		printBreadCrumbs(x, y);
}

/* This function print breadcrumbs at point*/
void Game::printBreadCrumbs(int x, int y)
{
	unsigned char breadCrumb = bc;
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << breadCrumb;
}

void Game::printGarbageVal(int x, int y)
{
	unsigned char garbage = (char)space;
	setTextColor(Color::LIGHTGREEN);
	gotoxy(x, y);
	cout << 'p';
}

/* This function print fruit at point*/
void Game::printFruit(int x, int y)
{
	setTextColor(Color::WHITE);
	gotoxy(x, y);
	cout << fruit.getFruitNumber();
}

/* This function check if fruit next move is valid */
bool Game::checkFruitValidMove(int x, int y, int dir)
{
	fruitIlustrateNextMove(x, y, dir);
	unsigned char charAtNextPoint = board.getBoardValFromPoint(x, y);

	// If the fruit out of board
	if ((x == 79) || (x == 0) || (y == 0) || (y == 24))
		return false;

	// If the next move is wall, tunnel or ghost this isn't valid move
	if ((charAtNextPoint == w) || (charAtNextPoint == space) || (charAtNextPoint == ghostIcon)) //FIXINGGGGGGGG
		return false;

	return true;
}

/* This function ilustrate the next fruit move*/
void Game::fruitIlustrateNextMove(int& x, int& y, int dir)
{
	switch (dir)
	{
	case 0: // LEFT
		x--;
		break;
	case 1: // RIGHT
		x++;
		break;
	case 2: // UP
		y--;
		break;
	case 3: // DOWN
		y++;
		break;
	}
}
/* This function check if in the last position of the ghost was bread crumbs*/
bool Game::ifLastGhostPositionWasBreadcrumb(int x, int y)
{
	if (board.getBoardValFromPoint(x, y) == bc)
		return true;
	return false;
}


/* This function check if in the last position of the ghost was fruit*/
bool Game::ifLastGhostPositionWasFruit(int x, int y)
{
	if (board.getBoardValFromPoint(x, y) == 5 || board.getBoardValFromPoint(x, y) == 6 || board.getBoardValFromPoint(x, y) == 7 || board.getBoardValFromPoint(x, y) == 8 || board.getBoardValFromPoint(x, y) == 9)
		return true;
	return false;
}

/* This function check if in the last position of the fruit was bread crumbs*/
bool Game::ifLastFruitPositionWasBreadcrumb(int x, int y)
{
	if (board.getBoardValFromPoint(x, y) == bc)
		return true;
	return false;
}

/* This function print pacman score*/
void Game::printScore() const
{
	setTextColor(Color::WHITE);
	gotoxy(38, 26);
	cout << "Pacman Score: ";
	setTextColor(Color::YELLOW);
	cout << player.getScore();

	setTextColor(Color::WHITE);
	cout << " Pacman Score Plus Bonuses: ";
	setTextColor(Color::YELLOW);
	cout << player.getScorePlusBonuses();
}

/* This function print pacman score plus bonuses from fruits*/
void Game::printScorePlusBonuses() const
{
	setTextColor(Color::WHITE);
	gotoxy(59, 27);
	
	setTextColor(Color::YELLOW);
	
}

/* This function print pacman life*/
void Game::printLife()  const
{
	setTextColor(Color::WHITE);
	resetPrintLife();
	gotoxy(16, 26);
	cout << "Remaining lives: ";
	setTextColor(Color::LIGHTRED);
	for (int i = 0; i < player.getLife(); i++)
		cout << (char)heart;
}

void Game::resetPrintLife() const {
	gotoxy(16, 26);
	cout << "                     ";
}

/* This function handle game over*/
void Game::gameOver()
{
	//setTextColor(Color::LIGHTRED);
	gotoxy(30, 30);
	cout << "You losed!";
	Sleep(longPauseWindow);
	resetGame();
	clearScreen();
	getchar();
}

/* This function print pacman instructions*/
void const Game::printInstructions()
{
	clearScreen();
	cout << "Pacman game instructions:\n"
		"The purpose of the game is to eat all the breadcrumbs (dots).\n"
		"Be careful, if Pacman touches a ghost, he'll lose a life.\n"
		"The game will end when Pacman runs out of lives.\n\n"
		"The keys:\n"
		"Up- 'w' or 'W'\n"
		"Down- 'x' or 'X'\n"
		"Left- 'a' or 'A'\n"
		"Right- 'd' or 'D'\n"
		"Stay- 's' or 'S'\n"
		"Pause/continue the game- ESC\n\n"
		"Press any key to return to the main menu and enjoy playing!\n";

	char c = _getch();
	clearScreen();
}

/* This function print the game before paused*/
void Game::printPreviousGame() const
{
	clearScreen();
	board.printPreviousBoard();
	player.draw();

	std::vector<Ghost*>::const_iterator itr = ghosts.begin();
	std::vector<Ghost*>::const_iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		(**it).draw();
	}

	printScore();
	printScorePlusBonuses();
	printLife();
}

/* This function draw ghosts and player*/
void Game::drawGameObj() const
{
	player.draw();
	std::vector<Ghost*>::const_iterator itr = ghosts.begin();
	std::vector<Ghost*>::const_iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		(**it).draw();
	}


	fruit.draw();
}

/* This function check if the player eat all breadcrumbs he win!!*/
bool Game::checkWin() const
{
	return (player.getScore() == bcLeft);
}

/* This function handle win situation*/
void Game::winGame(int kindOfGame)
{
	if (kindOfGame == 1 || isLastMap(currentMap)) // Single game
	{
		gotoxy(26, 27);
		cout << "You won the game!!!" << endl;
		Sleep(longPauseWindow);
		resetGame();
		clearScreen();
	}
	else // Full game
	{
		gotoxy(26, 27);
		cout << "You won this level!!!" << endl;
		Sleep(longPauseWindow);
		resetFullGame();
		clearScreen();

	}
	setTextColor(Color::WHITE);
}

void Game::resetFullGame()
{
	// Update current map data member
	std::vector<string>::iterator itr = mapFiles.begin();

	while ((*itr) != currentMap)
	{
		++itr;
	}
	++itr;
	currentMap = (*itr);

	//Reset game 
	player.setScore(0);
	player.setPlusFruitScore(0);
	ghosts.clear();
	objects.clear();
	player.setDirection(4);

	std::vector<Ghost*>::iterator it = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto i = it; i != itrEnd; ++i)
	{

		(**i).setGhostBody((**i).getGhostBody().getX(), (**i).getGhostBody().getY());
	}

	board.resetBoard();
}

bool Game::isLastMap(string nameOfMap)
{
	std::vector<string>::iterator itrEnd = mapFiles.end()-1;

	if ((*itrEnd) == nameOfMap)
		return true;
	return false;
}

/* Check if user input is correct*/
bool Game::checkValidUserInput(string input) const
{
	if (input.length() == 1)
	{
		char chUser = stringToChar(input);
		if (chUser >= '0' && chUser <= '9')
			if ((chUser == '1') || (chUser == '2') || (chUser == '8') || (chUser == '9'))
				return true;
	}
	return false;
}

/* This function clear the center of the screen when pausing the game*/
void Game::clearCenter() const
{
	for (int j = 0; j < 5; j++)
	{
		gotoxy(20, 8 + j);
		cout << "                                  ";
	}
}

/* This function reset the game when starting again*/
void Game::resetGame()
{
	player.setScore(0);
	player.setPlusFruitScore(0);
	player.setLife(3);
	objects.clear();
	ghosts.clear();
	player.setDirection(4);

	std::vector<Ghost*>::iterator itr = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{
		
		(**it).setGhostBody((**it).getGhostBody().getX(), (**it).getGhostBody().getY());
	}

	board.resetBoard();
}

/* This function init pacman and ghosts*/
void Game::initGameObj()
{
	player.initPacman();
	initGhosts();
	fruit.initFruit();
	validFruitPoint();
}

/* This function init ghosts*/
void Game::initGhosts()
{
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	std::vector<Ghost*>::iterator itrEnd = ghosts.end();

	for (auto it = itr; it != itrEnd; ++it)
	{

		(**it).initGhost();
	}

}


/* This function check valid user input*/
bool Game::checkValidUserSettings(string& input) const
{
	if (input.length() == 1 && userChoice != 0)
	{
		int userChoice = stoi(input);
		if ((userChoice == 1) || (userChoice == 2) || (userChoice == 3))
			return true;
	}
	return false;
}

/* This function change string to char*/
char Game::stringToChar(string& s) const
{
	char res = s[0];
	return res;
}



/* This function handle the game menu settings input*/
void Game::handleGameMenuSettingsInput()
{
	string input;
	getline(cin, input);

	while (!checkValidUserSettings(input))
	{
		clearScreen();
		cout << "You entered incorrect option, please choose again.\n\n";
		
		getline(cin, input);
	}
	userChoice = stoi(input);
}


string Game::chooseMap()
{
	int choose;
	cout << "Choose screen from list: " << endl;
	for (int i = 0; i < mapFiles.size(); i++)
		cout << i + 1 << ") " << mapFiles[i] << endl;
	cout << "Choice: ";
	cin >> choose;
	return mapFiles[choose - 1];
	
}

bool Game::noFiles(std::vector<string>& files)
{
	if (files.size() == 0)
	{
		cout << "There are no screen files to run" << endl;
		return false;
	}
	return true;
}

void Game::setPlayerPosition(int x, int y)
{
	player.setPacmanBody(x, y);
	player = { x, y };
}

void Game::validFruitPoint()
{
	unsigned char ch;
	fruit.setFruitBody();
	int x = fruit.getFruitBody().getX();
	int y = fruit.getFruitBody().getY();
	
	ch= board.getPoint(x, y);
	while (ch != bc)
	{
		fruit.setFruitBody();
		x = fruit.getFruitBody().getX();
		y = fruit.getFruitBody().getY();
		ch = board.getPoint(x, y);
	}
}

//Updating currecnt ghost level
void Game::chooseGhostLevel()
{
	char input;
	cout << "Enter ghost level: \n";
	cout << "a. Best\nb. Good\nc. Novice\n";
	cin >> input;
	if (input == 'a')
		currentGhostLevel = (ghostLevel)best;
	if (input == 'b')
		currentGhostLevel = (ghostLevel)good;
	if (input == 'c')
		currentGhostLevel = (ghostLevel)novice;

}