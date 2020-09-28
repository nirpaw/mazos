#pragma once
enum ePartition { wall , door };
enum eRoomType{  exteranlRoom, internalRoom};



class Room
{
	int _tresureValue;
	ePartition _top, _bottom, _right, _left;
	eRoomType _roomType;
	int _i, _j;

public:

	Room();
	Room(int x, int y, ePartition _top, ePartition _bottom, ePartition _right, ePartition _left, eRoomType _roomType);
	~Room();

	ePartition getTop();
	ePartition getBottom();
	ePartition getRight();
	ePartition getLeft();
	eRoomType getRoomType();

	int getTresureValue();

	void setTresureValue(int value);

	bool isExternalDoorExist();

	void printRoom();

};

