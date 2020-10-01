#include "pch.h"
#include "Player.h"

Player::Player() : _score(0), _i(0) , _j(0) {
}


void Player::setName(string name)
{
	_name = name;
}

void Player::setScore(int score)
{
	_score = score;
}


void Player::addScore(int scoreToAdd)
{
	_score += scoreToAdd;
}

void Player::setI(int i)
{
		_i = i;
}

void Player::setJ(int j)
{
		_j = j;
}

void Player::setPlayerLocation(int i, int j)
{
	setI(i);
	setJ(j);
}

Player::~Player()
{
}
