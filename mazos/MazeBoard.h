#include "Room.h"
#include "Player.h"
#define ROW 8	
#define COL 8
#define DRAW_C 10
#define DRAW_R 6
#pragma once

class MazeBoard
{
	Player _playerOne, _playerTwo;
	Room _maze[ROW][COL];
	Room *_externalRooms;
	bool _treasureIsReachable;
	void _crawler(int i, int j);


public:
	MazeBoard();

	void initNewBoard();

	void checkIfTresureIsReachble();

	void initMaze();
	void initPlayers();
	void initTreasure();
	void printMaze();
	~MazeBoard();
};

