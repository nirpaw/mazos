#include <string>
using namespace std;

#pragma once
class Player
{
	string _name;
	int _score;
	int _i;
	int _j;


public:
	Player();
	//Player(string name, int x = 0, int y = 0, int score = 0);
	void setPlayerLocation(int x, int y);
	~Player();

	//getters and setters
	string getName() const { return _name; }
	void setName(string);
	int getScore() { return _score; }
	void setScore(int);
	void addScore(int scoreToAdd);
	int getI() { return _i; }
	void setI(int);
	int getJ() { return _j; }
	void setJ(int);

};

