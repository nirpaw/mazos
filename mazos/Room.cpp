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
 

void::Room::printRoom()
{
		if (_top == wall)
		{
			std::cout << "============\n";
		}
		else
		{
			std::cout << "------------\n";
		}
		for (int i = 0; i < 7; i++)
		{
			if (_left == wall)
			{
				std::cout << "||";
			}
			else
			{
				std::cout << "|";
			}
			std::cout << "   R"<< _i<< _j<< "    ";
			if (_right == wall)
			{
				std::cout << "||";
			}
			else
			{
				std::cout << "|";
			}
			std::cout << "\n";
		}

		if (_bottom == wall)
		{
			std::cout << "============";
		}
		else
		{
			std::cout << "------------";
		}
		std::cout << "\n";

	
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
	if (_bottom == door && _i == ROW - 1 )
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