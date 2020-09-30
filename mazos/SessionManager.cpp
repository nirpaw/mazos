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

void SessionManager::gameManager()
{
	int playerTurn = 0;
	bool gameIsOver = false;

	while (!gameIsOver)
	{
		playTurn(playerTurn);
		if (playerTurn == 0)
		{
			_playerOneStepsCounter++;
		}
		if (_printingMethode == everyTurn)
		{
			_mazeBoard.printMaze();
		}
		playerTurn = (playerTurn + 1) % 2;
	}
}
void SessionManager::playTurn(int playerTurn)
{
	cout << "\n\nNow it`s ";
	if (playerTurn == 0)
		cout << _mazeBoard.getPlayerOne().getName();
	else
		cout << _mazeBoard.getPlayerTwo().getName();

	cout << "`s turn.\n-->Choose direction to move:";
	char moveChoice;

	bool choiseIsOK = false;
	bool moveIsOk = false;

	while (!choiseIsOK || !moveIsOk)
	{
		cout << "\n\tA- Left\n\tD- Right\n\tW- Up\n\tS- Down\n\tX- Do not move\n";
		cin >> moveChoice;

		char options[] = { 'A', 'D' , 'W', 'S', 'X' };
		bool exists = find(begin(options), end(options), toupper(moveChoice)) != end(options);

		if (exists)
			choiseIsOK = true;
		else
		{
			cout << "~| Wrong input. Try again|~\n";
			continue;
		}


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
			default:
				break;
			}
			moveIsOk = true;
			addStep(playerTurn);
		}
		catch (OutOfBoundsException& e) {

			//means the user is not in board and cant move anymore. but still count the step
			moveIsOk = true;
			addStep(playerTurn);

		}
		catch (CrossingBlockedException& e) {
			cout << "~| YOU SHALL NOT PASS |~\nYou tried to pass through a wall. Try Again.\n";
		}
	}



	//bool moveIsOk = false;
	//while (!moveIsOk)
	//{

	//}


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
	if (toupper(printChoose) == 'A')
	{
		_printingMethode = everyTurn;
	}
	else if (toupper(printChoose) == 'B') {
		_printingMethode = whenTresuareFound;
	}
	else {
		//TODO: THROW EXCEPTION
	}

}