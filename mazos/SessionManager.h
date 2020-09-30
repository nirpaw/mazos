#include "MazeBoard.h"
#pragma once

enum ePrintingMethod
{
	everyTurn,
	whenTresuareFound
};

class SessionManager
{

	int _roundsCounter; 

	int _playerOneStepsCounter;
	int _playerTwoStepsCounter;	

	int _playerTreasurePicks;
	int _playerTwoStepsPicks;

	MazeBoard _mazeBoard;
	ePrintingMethod _printingMethode;

public:
	SessionManager();
	~SessionManager();

	void initSession();

	void addStep(int playerNun);

	void gameManager();

	void playTurn(int playerTurn);


	void startNewGame();

	void userInputGameSettings();



};

