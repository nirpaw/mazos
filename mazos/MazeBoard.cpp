#include "pch.h"
#include "MazeBoard.h"
#include "Room.h"
#include <iostream>
#include <time.h>



MazeBoard::MazeBoard()
{
}

void MazeBoard::initNewBoard()
{
	_treasureIsReachable = false;
	cout << "Wait...\n";
	while (!_treasureIsReachable)
	{
		srand(time(NULL));

		initMaze();
		initTreasure();
		initPlayers();
		checkIfTresureIsReachble();
	}
}
 
void MazeBoard::checkIfTresureIsReachble()
{
	_crawler(_playerOne.getI(), _playerOne.getJ());
}

void MazeBoard::_crawler(int i, int j)
{
	if (_maze[i][j].getTresureValue() != 0)
	{
		_treasureIsReachable = true;
	}
	else
	{
		_maze[i][j].setCheckVisitd(true);
		//go  left
		if (j - 1 >= 0 && _maze[i][j].getLeft() == door && !_maze[i][j - 1].getCheckVisitd())
			_crawler(i, j - 1);

		//go up
		if (i - 1 >= 0 && _maze[i][j].getTop() == door && !_maze[i - 1][j].getCheckVisitd())
			_crawler(i - 1, j);

		//go right
		if (j + 1 < COL && _maze[i][j].getRight() == door && !_maze[i][j + 1].getCheckVisitd())
			_crawler(i, j + 1);

		//go  down
		if (i + 1 < ROW && _maze[i][j].getBottom() == door && !_maze[i + 1][j].getCheckVisitd())
			_crawler(i + 1, j);
	}
}
void MazeBoard::initMaze()
{
	int externalRoomsCounter = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			ePartition currentLeft, currentTop, currentRight, currentBottom;

			// if left room is out of bounds generate random partition, else take the existing from left
			currentLeft = j - 1 < 0 ? static_cast<ePartition>(rand() % 2) : _maze[i][j - 1].getRight();

			// if top room is out of bounds generate random partition, else take the existing from top
			currentTop = i - 1 < 0 ? static_cast<ePartition>(rand() % 2) : _maze[i - 1][j].getBottom();

			//generate random patition for the right and botton part
			currentRight = static_cast<ePartition>(rand() % 2);
			currentBottom = static_cast<ePartition>(rand() % 2);

			//check if its internal or external room
			eRoomType currentRoomType = (i - 1 >= 0 && j - 1 >= 0 && j + 1 < ROW && i + 1 < COL) ? internalRoom : exteranlRoom;

			//cout << currentRoomType;
			_maze[i][j] = Room(i, j, currentTop, currentBottom, currentRight, currentLeft, currentRoomType);

		}
	}
}

void MazeBoard::initPlayers()
{
	int playersLocationI, playersLocationJ;
	do
	{
		// choose the first location of both players,
		// reapet till the choosen rooom is: extermal || external door is exist || witout tresure 
		int rndRowOrCol = rand() % 2;
		if (rndRowOrCol == 0)
		{

			playersLocationI = rand() % ROW;
			playersLocationJ = 0;
		}
		else
		{
			playersLocationJ = rand() % COL;
			playersLocationI = 0;
		}
	} while ((_maze[playersLocationI][playersLocationJ].getRoomType() != exteranlRoom) ||
		(!_maze[playersLocationI][playersLocationJ].isExternalDoorExist()) ||
		(_maze[playersLocationI][playersLocationJ].getTresureValue() != 0));

	_playerOne.setPlayerLocation(playersLocationI, playersLocationJ);
	_playerTwo.setPlayerLocation(playersLocationI, playersLocationJ);

}
void MazeBoard::initTreasure()
{
	_maze[rand() % ROW][rand() % COL].setTresureValue(rand() % 10);
}

void MazeBoard::printMaze()
{
	// DRAW_R is the numeber of chars that representing tops & bottoms parititions
	// DRAW_C is the numeber of chars that representing left & right parititions

	int i, j;
	for (int r = 0; r < DRAW_R * ROW; r++)
	{
		for (int c = 0; c < DRAW_C * COL; c++)
		{
			i = r / DRAW_R;
			j = c / DRAW_C;
			if (c % DRAW_C == 0)
			{
				cout << " ";
			}
			// print all row tops
			if (r % DRAW_R == 0)
			{
				if (_maze[i][j].getTop() == wall)
					cout << "#";
				else
					cout << "-";
			}
			//print all row bottoms 
			else if (r % DRAW_R == DRAW_R - 1)
			{
				if (_maze[i][j].getBottom() == wall)
					cout << "#";
				else
					cout << "-";
			}
			//print all row lefts
			else if (c % DRAW_C == 0)
			{
				if (_maze[i][j].getLeft() == wall)
					cout << "#";
				else
					cout << "|";
			}
			//print all row rights
			else if (c % DRAW_C == DRAW_C - 1)
			{
				if (_maze[i][j].getRight() == wall)
					cout << "#";
				else
					cout << "|";
			}
			//print treasure
			else if (c % DRAW_C == DRAW_C / 2 && r % DRAW_R == DRAW_R / 2)
			{
				int treasure = _maze[i][j].getTresureValue();
				if (treasure != 0)
					cout << treasure;
				else
					cout << " ";
			}
			//print player 1
			else if (c % DRAW_C == 2 && r % DRAW_R == 1)
			{
				if (_playerOne.getI() == i && _playerOne.getJ() == j)
				{
					cout << _playerOne.getName()[0];
				}
				else
				{
					cout << " ";
				}
			}
			//print player 2
			else if (c % DRAW_C == 2 && r % DRAW_R == 2)
			{
				if (_playerTwo.getI() == i && _playerTwo.getJ() == j)
				{
					cout << _playerOne.getName()[0];
				}
				else
				{
					cout << " ";
				}
			}
			else
			{
				cout << " ";
			}
		}
		cout << "\n";
	}

}

MazeBoard::~MazeBoard()
{
}
