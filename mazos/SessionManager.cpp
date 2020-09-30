#include "pch.h"
#include "SessionManager.h"
#include <algorithm> // for std::find
#include <iterator> // for std::begin, std::end
#include <iostream>


SessionManager::SessionManager()
{

}


SessionManager::~SessionManager()
{

}

void SessionManager::initSession()
{

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
		playerTurn = (playerTurn + 1) % 2;

		playTurn(playerTurn);

		if (_printingMethode == everyTurn)
		{
			_mazeBoard.printMaze();
		}
		cout << "----\nfor debug\n" ;

		cout << "p1 steps :" << _playerOneStepsCounter;
		cout << "\np2 steps :" << _playerTwoStepsCounter;		cout << "\n----";

		try {
			treasureValue = _mazeBoard.getTresureValue(playerTurn);
		}

		catch (OutOfBoundsException& e) {
			treasureValue = 0;
		}

		gameIsOver = treasureValue != 0;
	}
	gameOver(playerTurn, treasureValue);
}
void SessionManager::playTurn(int playerTurn)
{
	cout << "\n\n-->Now it`s ";
	if (playerTurn == 0)
		cout << _mazeBoard.getPlayerOne().getName();
	else
		cout << _mazeBoard.getPlayerTwo().getName();
	cout << "`s turn.\n";
	char moveChoice;

	bool choiseIsOK = false;
	bool moveIsOk = false;

	while (!choiseIsOK || !moveIsOk)
	{
		cout << "\n-->Choose direction to move:: ";

		cout << "\n\tA- Left\n\tD- Right\n\tW- Up\n\tS- Down\n\tX- Do not move\n";
		cout << "-->Hints:\n\tN- Air distance from the Treasury\n\tM- Show adjoining room\n\tChoice:";
		cin >> moveChoice;

		char options[] = { 'A', 'D' , 'W', 'S', 'X' , 'N', 'M'};
		bool exists = find(begin(options), end(options), toupper(moveChoice)) != end(options);

		if (exists)
			choiseIsOK = true;
		else
		{
			cout << "~| Wrong input. Try again|~\n";
			continue;
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
				break;
			}

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
			cout << "\n~| YOU SHALL NOT PASS |~\nYou tried to pass through a wall. Try Again.\n";
			system("pause");

			continue;
		}
		
	}
}
void SessionManager::printAjoiningRoom(int playerTurn)
{

	bool choiseIsOK = false;
	char roomChoice;

	while (!choiseIsOK)
	{
		cout << "\n-->Which room would you like to see?\n\tA- Left\n\tD- Right\n\tW- Up\n\tS- Down\n";
		cout << "\n\tChoice:";
		cin >> roomChoice;

		char options[] = { 'A', 'D' , 'W', 'S' };
		bool exists = find(begin(options), end(options), toupper(roomChoice)) != end(options);

		if (exists)
			choiseIsOK = true;
		else
		{
			cout << "~| Wrong input. Try again|~\n";
			continue;
		}
	}

	//TODO:FINISH
	cout << "THIS FEATURE IS WILL BE HERE TOMMOROW\n";
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
	_mazeBoard.printMaze();

	gameManager();
}

void SessionManager::userInputGameSettings()
{
	string n1, n2;
	cout << "-->Enter Player One name: ";
	cin >> n1;
	cout << "-->Enter Player Two name: ";
	cin >> n2;
	_mazeBoard.setPlayersName(n1, n2);
	char printChoose;
	cout << "-->Choose:\n\tA - Print maze every turn\n\tB - Print maze only at the end\n\tChoice: ";
	cin >> printChoose;

	bool choiseIsOk = false;
	while (!choiseIsOk)
	{
		if (toupper(printChoose) == 'A')
		{
			_printingMethode = everyTurn;
			choiseIsOk = true;
		}
		else if (toupper(printChoose) == 'B') {
			_printingMethode = whenTresuareFound;
			choiseIsOk = true;

		}
		else {
			cout << "~| Wrong input. Try again|~\n";
		}
	}



}