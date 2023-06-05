#include "Game.h"

int main()
{
	srand(time(0));
	Game game;
	setTextColor(Color::WHITE);
	int userChoice = game.menu();
	std::vector<string> files = game.getScreenFiles();
	bool ifLose = false;
	while (userChoice != 9)
	{
		ifLose = false;
		switch (userChoice)
		{
		case 1://new game
		{
			if (!(game.noFiles(files)))
			{
				break;
			}
			game.chooseGhostLevel();
			game.playNewGame(0, &ifLose);
			clearScreen();
			break;
		}
		case 2://single game
		{
			if (!(game.noFiles(files)))
			{
				break;
			}
			string nameOfMap = game.chooseMap();
			game.chooseGhostLevel();
			game.playGame(1, nameOfMap, &ifLose);
			clearScreen();
			break;
		}
		case 8:
		{
			game.printInstructions();
			break;
		}
		default:
		{
			cout << "You entered incorrect option, please enter again!" << endl;
			break;
		}
		}

		//clearScreen();
		setTextColor(Color::WHITE);
		userChoice = game.menu();
	}

	clearScreen();
	setTextColor(Color::WHITE);
	cout << "Bye Bye!\n"
		"Thank you for playing with us!" << endl;
	return 0;
}