#pragma once
#include <iostream>
#include <stdio.h>
#include <mutex>
#include <thread>
#include <chrono>


class Game;
class Player
{
public:
	Player() {};
	Player(Game* _board, std::mutex* _mutex);
	Game* getBoard();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveUp();
	virtual void moveDown();
	int getpos_X();
	int getpos_Y();
	int getPoints();
protected:
	void setSprite(char _spr);
	void inputName();

	std::mutex* mapmutex;
	std::string name;
	virtual void setPosition();
	Game *board;
	char sprite;
	int points;
	int x_pos;
	int y_pos;
};