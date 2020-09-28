#include "Room.h"
#include "Player.h"
#define ROW 4
#define COL 4
#pragma once

class MazeBoard
{
	Player _playerOne, _playerTwo;
	Room _maze[ROW][COL];
	bool _treasureIsReachble;

	void _crawler(int i, int j);


public:
	MazeBoard();

	void initBoard();

	void checkIfTresureIsReachble();

	void initMaze();
	void initPlayers();
	void initTreasure();
	void printMaze();
	~MazeBoard();
};

