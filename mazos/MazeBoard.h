#include "Room.h"
#include "Player.h"
#define ROW 4
#define COL 4
#pragma once

class MazeBoard
{
	Player _playerOne, _playerTwo;
	Room _maze[ROW][COL];

public:
	MazeBoard();

	void initBoard();

	void initMaze();
	bool isExternalDoorInRoom(int i, int j);
	void initPlayers();
	void initTreasure();
	void printMaze();
	~MazeBoard();
};

