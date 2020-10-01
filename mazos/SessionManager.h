#include "MazeBoard.h"
#pragma once

enum ePrintingMethod
{
	everyTurn,
	whenTresuareFound
};

enum eGameType
{
	robotVsRobot,
	userVsRobot
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
	eGameType _gameType;

public:
	SessionManager();
	~SessionManager();

	void initSession();

	void addStep(int playerNun);

	void printGameSummary(int winner);

	void gameOver(int winner, int tresureValue);

	void gameManager();

	string optionsMap(char c);

	void playTurn(int playerTurn);

	void printAjoiningRoom(int playerTurn);



	void printAirDist(int playerTurn);

	void startNewGame();

	void userInputGameSettings();



};

