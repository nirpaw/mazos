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
	while (!_treasureIsReachable)
	{
		srand(time(NULL));

		setMazeRooms();
		initTreasure();
		serPlayersLocation();
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
void MazeBoard::setMazeRooms()
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

			// generate random patition for the right and botton part
			currentRight = static_cast<ePartition>(rand() % 2);
			currentBottom = static_cast<ePartition>(rand() % 2);

			// check if its internal or external room
			eRoomType currentRoomType = (i - 1 >= 0 && j - 1 >= 0 && j + 1 < ROW && i + 1 < COL) ? internalRoom : exteranlRoom;

			// cout << currentRoomType;
			_maze[i][j] = Room(i, j, currentTop, currentBottom, currentRight, currentLeft, currentRoomType);

		}
	}
}

void MazeBoard::serPlayersLocation()
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
float MazeBoard::checkAirDistance(int playerNum)
{
	Player temp = playerNum == 0 ? _playerOne : _playerTwo;
	// Calculating distance 
	int x1 = _playerOne.getI();
	int x2 = _playerOne.getJ();
	int y1 = _trI;
	int y2 = _trJ;

	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}

void MazeBoard::initTreasure()
{
	_trI = rand() % ROW;
	_trJ = rand() % COL;
	_maze[_trI][_trJ].setTresureValue(rand() % 10);
}

void MazeBoard::printMaze()
{
	// DRAW_R is the numeber of chars that representing tops & bottoms parititions
	// DRAW_C is the numeber of chars that representing left & right parititions

	int i, j;
	for (int r = 0; r < LENGTH_DRAW_R * ROW; r++)
	{
		for (int c = 0; c < LENGTH_DRAW_C * COL; c++)
		{
			i = r / LENGTH_DRAW_R;
			j = c / LENGTH_DRAW_C;
			if (c % LENGTH_DRAW_C == 0)
			{
				cout << " ";
			}
			// print all row tops
			if (r % LENGTH_DRAW_R == 0)
			{
				if (_maze[i][j].getTop() == wall)
					cout << WALL_SIGN_HORIZONTAL;
				else
					cout << DOOR_SIGN_HORIZONTAL;
			}
			//print all row bottoms 
			else if (r % LENGTH_DRAW_R == LENGTH_DRAW_R - 1)
			{
				if (_maze[i][j].getBottom() == wall)
					cout << WALL_SIGN_HORIZONTAL;
				else
					cout << DOOR_SIGN_HORIZONTAL;
			}
			//print all row lefts
			else if (c % LENGTH_DRAW_C == 0)
			{
				if (_maze[i][j].getLeft() == wall)
					cout << WALL_SIGN_VERTICAL;
				else
					cout << DOOR_SIGN_VERTICAL;
			}
			//print all row rights
			else if (c % LENGTH_DRAW_C == LENGTH_DRAW_C - 1)
			{
				if (_maze[i][j].getRight() == wall)
					cout << WALL_SIGN_VERTICAL;
				else
					cout << DOOR_SIGN_VERTICAL;
			}
			//print treasure
			else if (c % LENGTH_DRAW_C == LENGTH_DRAW_C / 2 && r % LENGTH_DRAW_R == LENGTH_DRAW_R / 2)
			{
				int treasure = _maze[i][j].getTresureValue();
				if (treasure != 0)
					cout << treasure;
				else
					cout << SPACE_CHAR;
			}
			//print player 1
			else if (c % LENGTH_DRAW_C == 2 && r % LENGTH_DRAW_R == 1)
			{
				if (_playerOne.getI() == i && _playerOne.getJ() == j)
				{
					cout << _playerOne.getName()[0]; //first letter
				}
				else
				{
					cout << SPACE_CHAR;
				}
			}
			//print player 2
			else if (c % LENGTH_DRAW_C == 2 && r % LENGTH_DRAW_R == 2)
			{
				if (_playerTwo.getI() == i && _playerTwo.getJ() == j)
				{
					cout << _playerTwo.getName()[0]; //first letter
				}
				else
				{
					cout << SPACE_CHAR;
				}
			}
			else
			{
				cout << SPACE_CHAR;
			}
		}
		cout << "\n";
	}

}

void MazeBoard::setPlayersName(string n1, string n2)
{
	_playerOne.setName(n1);
	_playerTwo.setName(n2);

}

int MazeBoard::getTresureValue(int playerNum)
{
	Player temp = playerNum == 0 ? _playerOne : _playerTwo;

	if (temp.getI() < 0 || temp.getI() >= ROW ||
		temp.getJ() < 0 || temp.getJ() >= ROW)
	{
		throw OutOfBoundsException("Out of bounds");
	}
	return _maze[temp.getI()][temp.getJ()].getTresureValue();
}

void MazeBoard::movePlayer(int playerNum, eMoveDirection direction)
{


	Player temp = playerNum == 0 ? _playerOne : _playerTwo;

	if (temp.getI() < 0 || temp.getI() >= ROW ||
		temp.getJ() < 0 || temp.getJ() >= ROW)
	{
		throw OutOfBoundsException("Out of bounds");
	}

	switch (direction)
	{
	case moveLeft:
		if ((_maze[temp.getI()][temp.getJ()]).getLeft() == wall)
			throw CrossingBlockedException("The crossing is blocked, an impossible step");
		temp.setPlayerLocation(temp.getI(), temp.getJ() - 1);
		break;
	case moveRight:
		if ((_maze[temp.getI()][temp.getJ()]).getRight() == wall)
			throw CrossingBlockedException("The crossing is blocked, an impossible step");
		temp.setPlayerLocation(temp.getI(), temp.getJ() + 1);
		break;
	case moveUp:
		if ((_maze[temp.getI()][temp.getJ()]).getTop() == wall)
			throw CrossingBlockedException("The crossing is blocked, an impossible step");
		temp.setPlayerLocation(temp.getI() - 1, temp.getJ());

		break;
	case moveDown:
		if ((_maze[temp.getI()][temp.getJ()]).getBottom() == wall)
			throw CrossingBlockedException("The crossing is blocked, an impossible step");
		temp.setPlayerLocation(temp.getI() + 1, temp.getJ());
		break;
	default:
		break;
	}


	if (playerNum == 0) {
		_playerOne = temp;
	}
	else {
		_playerTwo = temp;
	}
}


void MazeBoard::addScoreAfterGame(int playerNum, int scoreToAdd)
{
	if (playerNum == 0)
	{
		_playerOne.addScore(scoreToAdd);
	}
	else
	{
		_playerTwo.addScore(scoreToAdd);

	}
}


Player MazeBoard::getPlayerOne()
{
	return _playerOne;
}
Player MazeBoard::getPlayerTwo()
{
	return _playerTwo;

}

MazeBoard::~MazeBoard()
{
}
