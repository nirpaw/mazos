#include "pch.h"
#include "Room.h"
#include "MazeBoard.h"

#include <iostream>


Room::Room()
{
}

Room::Room(int i, int j, ePartition top, ePartition bottom, ePartition right, ePartition left, eRoomType roomType)
{
	_i = i;
	_j = j;
	_top = top;
	_bottom = bottom;
	_right = right;
	_left = left;
	_roomType = roomType;
	_tresureValue = 0;
	_checkVisited = false;
}


Room::~Room()
{
}


void Room::printRoom()
{
	for (int i = 0; i < LENGTH_DRAW_C; i++)
	{
		if (_top == wall)
			cout << WALL_SIGN_HORIZONTAL;
		else
			cout << DOOR_SIGN_HORIZONTAL;
	}
	cout << "\n";
	for (int i = 0; i < LENGTH_DRAW_R; i++)
	{
		for (int j = 0; j < LENGTH_DRAW_C ; j++)
		{
			if (j == 0)
			{
				if (_left == wall)
					cout << WALL_SIGN_VERTICAL;
				else
					cout << DOOR_SIGN_VERTICAL;
			}
			else if (j == LENGTH_DRAW_C - 1)
			{
				if (_right == wall)
					cout << WALL_SIGN_VERTICAL;
				else
					cout << DOOR_SIGN_VERTICAL;
			}
			else if (i== LENGTH_DRAW_C / 2 && j== LENGTH_DRAW_R / 2)
			{
				if (_tresureValue != 0)
					cout << _tresureValue;
				else
					cout << SPACE_CHAR;
			}
			else {
				cout << SPACE_CHAR;;
			}
		}
		cout << "\n";

	}


	for (int i = 0; i < LENGTH_DRAW_C; i++)
	{
		if (_bottom == wall)
			cout << WALL_SIGN_HORIZONTAL;
		else
			cout << DOOR_SIGN_HORIZONTAL;
	}
	cout << "\n";
}

ePartition Room::getTop()
{
	return _top;
}
ePartition Room::getBottom()
{
	return _bottom;
}
ePartition Room::getRight()
{
	return _right;
}
ePartition Room::getLeft()
{
	return _left;
}

eRoomType Room::getRoomType()
{
	return _roomType;
}

int Room::getTresureValue()
{
	return _tresureValue;
}
bool Room::getCheckVisitd()
{
	return _checkVisited;
}
void Room::setCheckVisitd(bool visited)
{
	_checkVisited = visited;

}
void Room::setTresureValue(int value)
{
	_tresureValue = value;
}

bool Room::isExternalDoorExist()
{
	if (_bottom == door && _i == ROW - 1)
	{
		return true;
	}
	if (_top == door && _i == 0)
	{
		return true;
	}
	if (_right == door && _j == COL - 1)
	{
		return true;
	}
	if (_left == door && _j == 0)
	{
		return true;
	}
	return false;
}