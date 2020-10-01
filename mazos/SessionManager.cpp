#include "pch.h"
#include "SessionManager.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <iostream>
#include <time.h>
#include <map>


SessionManager::SessionManager()
{
	srand(time(NULL));


}


SessionManager::~SessionManager()
{

}

void SessionManager::initSession()
{
	userInputGameSettings();
	startNewGame();
}

void SessionManager::addStep(int playerNun)
{
	if (playerNun == 0)
		_playerOneStepsCounter++;
	else
		_playerTwoStepsCounter++;
}

void SessionManager::printGameSummary(int winner)
{
	string winnerName = winner == 0 ? _mazeBoard.getPlayerOne().getName() : _mazeBoard.getPlayerTwo().getName();
	cout << "\n-----------------------------\n";
	cout << " ~-~-~-~| "<<winnerName <<" Wins! |~-~-~-~\n";
	cout << " " << _mazeBoard.getPlayerOne().getName()<<" with " << _mazeBoard.getPlayerOne().getScore()<< " Points\n";
	cout << " " << _mazeBoard.getPlayerTwo().getName()<<" with " << _mazeBoard.getPlayerTwo().getScore()<< " Points\n";
	cout << "-----------------------------\n";
	cout << "-->Tap any key to start new game\n";
	system("pause");
}

void SessionManager::gameOver(int winner, int tresureValue)
{
	if (winner == 0)
	{
		_mazeBoard.addScoreAfterGame(0, tresureValue - _playerOneStepsCounter);
		_mazeBoard.addScoreAfterGame(1, 0 - _playerTwoStepsCounter);
	}
	else
	{		
		_mazeBoard.addScoreAfterGame(1, tresureValue - _playerTwoStepsCounter);
		_mazeBoard.addScoreAfterGame(0, 0 - _playerTwoStepsCounter);
	}

	printGameSummary(winner);
	startNewGame();

}

void SessionManager::gameManager()
{

	int playerTurn = rand() % 2;
	bool gameIsOver = false;
	int treasureValue = 0;
	while (!gameIsOver)
	{
		system("pause");

		playerTurn = (playerTurn + 1) % 2;

		playTurn(playerTurn);

		if (_printingMethode == everyTurn)
		{
			_mazeBoard.printMaze();
		}
		//cout << "----\nfor debug\n" ;

		//cout << "p1 steps :" << _playerOneStepsCounter;
		//cout << "\np2 steps :" << _playerTwoStepsCounter;		cout << "\n----";

		try {
			treasureValue = _mazeBoard.getTresureValue(playerTurn);
		}

		catch (OutOfBoundsException& e) {
			treasureValue = 0;
		}

		gameIsOver = treasureValue != 0;
	}
	if (_printingMethode == whenTresuareFound)
	{
		_mazeBoard.printMaze();
	}
	gameOver(playerTurn, treasureValue);
}


void SessionManager::playTurn(int playerTurn)
{
	char moveChoice;

	bool choiseIsOK = true;
	bool moveIsOk = false;

	while (!choiseIsOK || !moveIsOk)
	{
		choiseIsOK = true;
		cout << "\n\n-->Now it`s ";
		string playerName;
		if (playerTurn == 0)
			playerName= _mazeBoard.getPlayerOne().getName();
		else
			playerName= _mazeBoard.getPlayerTwo().getName();

		cout << playerName<< "`s turn.\n";

		if (_gameType == userVsRobot && playerTurn == 0)
		{
			cout << "\n-->Choose direction to move:: ";
			cout << "\n\tA- Left\n\tD- Right\n\tW- Up\n\tS- Down\n\tX- Do not move\n";
			cout << "-->Hints:\n\tN- Air distance from the Treasury\n\tM- Show adjoining room\n\tChoice:";
			cin >> moveChoice;
		}
		else
		{
			char options[] = { 'A', 'D', 'S', 'W' , 'X'};
			moveChoice = options[rand() % sizeof(options) / sizeof(char)];
		}
		bool isStep = true;
		try
		{
			switch (toupper(moveChoice))
			{
			case 'A':
				_mazeBoard.movePlayer(playerTurn, moveLeft);
				break;
			case 'D':
				_mazeBoard.movePlayer(playerTurn, moveRight);
				break;
			case 'S':
				_mazeBoard.movePlayer(playerTurn, moveDown);
				break;
			case 'W':
				_mazeBoard.movePlayer(playerTurn, moveUp);
				break;
			case 'X':
				isStep = false;
				break;
			case 'N':
				printAirDist(playerTurn);
				system("pause");
				break;
			case 'M':
				printAjoiningRoom(playerTurn);
				system("pause");
				break;
			default:
				if (_gameType == userVsRobot && playerTurn == 0)
				{
					cout << "--------------------> ~| Wrong input. Try again|~\n";
				}
				choiseIsOK = false;
				continue;
				break;
			}

			if (!(_gameType == userVsRobot && playerTurn == 0)	)
				cout << "\n-> " << playerName << " " << optionsMap(toupper(moveChoice));
			cout << "\n";
			moveIsOk = true;
			if(isStep)
				addStep(playerTurn);
		}
		catch (OutOfBoundsException& e) {
			//means the user is not in board and cant move anymore. but still count the step
			moveIsOk = true;
			if (isStep)
				addStep(playerTurn);
		}
		catch (CrossingBlockedException& e) {
			cout << playerName << " tried to pass through a wall. Try Again.\n";
			system("pause");

			continue;
		}
		
	}

}
void SessionManager::printAjoiningRoom(int playerTurn)
{
	int i = playerTurn == 0 ? _mazeBoard.getPlayerOne().getI() : _mazeBoard.getPlayerTwo().getI();
	int j = playerTurn == 0 ? _mazeBoard.getPlayerOne().getJ() : _mazeBoard.getPlayerTwo().getJ();

	bool choiseIsOK = false;
	char roomChoice;

	while (!choiseIsOK)
	{
		choiseIsOK = true;
		cout << "\n-->Which room would you like to see?\n\tA- Left\n\tD- Right\n\tW- Up\n\tS- Down\n";
		cout << "\n\tChoice:";
		cin >> roomChoice;
		try
		{
			switch (toupper(roomChoice))
			{
			case 'A':
				_mazeBoard.printSingleRoom(i, j - 1);
				break;

			case 'W':
				_mazeBoard.printSingleRoom(i - 1, j);
				break;

			case 'D':
				_mazeBoard.printSingleRoom(i, j + 1);
				break;

			case 'S':
				_mazeBoard.printSingleRoom(i + 1, j);
				break;

			default:
				cout << "--------------------> ~| Wrong input. Try again|~\n";
				choiseIsOK = false;
				continue;
				break;
			}
		}
		catch (OutOfBoundsException& e) 
		{
			cout << "-->There is no such room\n";
		}
	}
}

void SessionManager::printAirDist(int playerTurn)
{
	cout << " --> Air distance from the Treasury: ";
	cout << _mazeBoard.checkAirDistance(playerTurn);
	cout << "\n";
}

void SessionManager::startNewGame()
{
	_roundsCounter++;
	_playerOneStepsCounter = 0;
	_playerTwoStepsCounter = 0;
	_playerTreasurePicks = 0;
	_playerTwoStepsPicks = 0;

	_mazeBoard.initNewBoard();

	cout << "\n --> Game is started <-- \n";
	_mazeBoard.printMaze();

	gameManager();
}

void SessionManager::userInputGameSettings()
{

	char printChoose;

	bool choiseIsOk = false;
	while (!choiseIsOk)
	{
		cout << "-->Choose:\n\tA - Print maze every turn\n\tB - Print maze only at the end\n\tChoice: ";
		cin >> printChoose;

		switch (toupper(printChoose))
		{
		case 'A':
			_printingMethode = everyTurn;
			choiseIsOk = true;
			break;		
		case 'B':
			_printingMethode = whenTresuareFound;
			choiseIsOk = true;
			break;
		default:
			cout << "--------------------> ~| Wrong input. Try again|~\n";
			continue;
			break;
		}
	}

	char gameTypeChoose;

	choiseIsOk = false;
	while (!choiseIsOk)
	{
		cout << "-->Choose:\n\tA - Robot VS Robot\n\tB - User VS Robot\n\tChoice: ";
		cin >> gameTypeChoose;

		switch (toupper(gameTypeChoose))
		{
		case 'A':
			_gameType = robotVsRobot;
			choiseIsOk = true;
			break;		
		case 'B':
			_gameType = userVsRobot;
			choiseIsOk = true;
			break;
		default:
			cout << "--------------------> ~| Wrong input. Try again|~\n";
			continue;
			break;
		}
	}

	string n1, n2;
	if (_gameType == userVsRobot)
	{
		cout << "-->Enter Player name: ";
		cin >> n1;
		n2 = "Robot";
	}
	else if (_gameType == robotVsRobot)
	{
		n1 = "Wall-E";
		n2 = "Terminator";
	}
	

	_mazeBoard.setPlayersName(n1, n2);



}

string SessionManager::optionsMap(char c)
{
	switch (c)
	{
	case 'A':
		return "Choose to go Left";
		break;
	case 'D':
		return "Choose to go Right";
		break;
	case 'S':
		return "Choose to go Down";
		break;
	case 'W':
		return "Choose to go Up";
		break;
	case 'X':
		return "Choose to Stay";
		break;
	default:
		break;
	}

}