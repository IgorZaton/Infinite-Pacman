#pragma once
#include "Player.h"
#include <utility>

class Game;

class Ghost : public Player
{
public:
	Ghost(Game *_board, std::mutex* _mutex);
	~Ghost();
	void moveLeft(bool _isplrseen);
	void moveRight(bool _isplrseen);
	void moveUp(bool _isplrseen);
	void moveDown(bool _isplrseen);
private:
	void setPosition();
};
