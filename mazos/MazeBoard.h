#include "Room.h"
#include "Player.h"
#define ROW 4
#define COL 4
#define LENGTH_DRAW_C 10
#define LENGTH_DRAW_R 6
#define WALL_SIGN_HORIZONTAL '#'
#define DOOR_SIGN_HORIZONTAL '-'
#define WALL_SIGN_VERTICAL '#'
#define DOOR_SIGN_VERTICAL '|'
#define SPACE_CHAR ' '
#define BLOCKED_MSG "The crossing is blocked, an impossible step"
#pragma once

enum eMoveDirection
{
	moveLeft,
	moveRight,
	moveUp,
	moveDown
};


struct OutOfBoundsException : public exception
{
	string s;
	OutOfBoundsException(string ss) : s(ss) {}
	~OutOfBoundsException() throw () {} // Updated
	const char* text() const throw() { return s.c_str(); }
};


struct CrossingBlockedException : public exception
{
	string s;
	CrossingBlockedException(string ss) : s(ss) {}
	~CrossingBlockedException() throw () {} // Updated
	const char* text() const throw() { return s.c_str(); }
};

class MazeBoard
{
	Player _playerOne, _playerTwo;
	Room _maze[ROW][COL];
	bool _treasureIsReachable;
	void _crawler(int i, int j);
	int _trI, _trJ;


public:
	MazeBoard();

	void initNewBoard();

	void checkIfTresureIsReachble();

	void setMazeRooms();
	void serPlayersLocation();
	float checkAirDistance(int playerNum);
	void initTreasure();
	void printSingleRoom(int i, int j);
	void printMaze();
	void setPlayersName(string n1, string n2);
	bool isOutOfBounds(int i, int j);
	int getTresureValue(int playerNum);
	void movePlayer(int playerNum, eMoveDirection direction);

	void addScoreAfterGame(int playerNum, int scoreToAdd);

	Player getPlayerOne();

	Player getPlayerTwo();

	~MazeBoard();
};

