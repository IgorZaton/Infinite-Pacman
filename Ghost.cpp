#include "Ghost.h"
#include "Game.h"

Ghost::Ghost(Game *_board, std::mutex* _mutex)
{
	board = _board;
	mapmutex = _mutex;
	name = "Ghost";
	setSprite('&');
	setPosition();
	board->addGhost(this);
}

Ghost::~Ghost()
{
	board = nullptr;
	mapmutex = nullptr;
}

void Ghost::setPosition()
{
	x_pos = board->ghostSpot_X();
	y_pos = board->ghostSpot_Y();
}

void Ghost::moveLeft(bool _isplrseen)
{
	mapmutex->lock();

	if (x_pos - 1 > 0 && (*board)(x_pos - 1, y_pos) != '-' && (*board)(x_pos - 1, y_pos) != '|')	
	{
		(*board)(x_pos - 1, y_pos) = sprite;
		x_pos = x_pos - 1;		
		(*board)(x_pos + 1, y_pos) = '+';
	}
	mapmutex->unlock();
	if (_isplrseen) std::this_thread::sleep_for(std::chrono::milliseconds(350));
	else std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
}

void Ghost::moveRight(bool _isplrseen)
{
	mapmutex->lock();
	if (x_pos + 1 < (*board).getWidth() && (*board)(x_pos + 1, y_pos) != '-' && (*board)(x_pos + 1, y_pos) != '|')
	{
		(*board)(x_pos + 1, y_pos) = sprite;
		x_pos = x_pos + 1;
		(*board)(x_pos - 1, y_pos) = '+';
	}
	mapmutex->unlock();
	if (_isplrseen) std::this_thread::sleep_for(std::chrono::milliseconds(350));
	else std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
}

void Ghost::moveUp(bool _isplrseen)
{
	mapmutex->lock();
	if (y_pos - 1 > 0 && (*board)(x_pos, y_pos - 1) != '-' && (*board)(x_pos, y_pos - 1) != '|')
	{
		(*board)(x_pos, y_pos - 1) = sprite;
		y_pos = y_pos - 1;
		(*board)(x_pos, y_pos + 1) = '+';
	}
	mapmutex->unlock();
	if (_isplrseen) std::this_thread::sleep_for(std::chrono::milliseconds(350));
	else std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
}

void Ghost::moveDown(bool _isplrseen)
{
	mapmutex->lock();
	if (y_pos + 1 < (*board).getHeight() && (*board)(x_pos, y_pos + 1) != '-' && (*board)(x_pos, y_pos + 1) != '|')
	{
		(*board)(x_pos, y_pos + 1) = sprite;
		y_pos = y_pos + 1;
		(*board)(x_pos, y_pos - 1) = '+';
	}
	mapmutex->unlock();
	if(_isplrseen) std::this_thread::sleep_for(std::chrono::milliseconds(350));
	else std::this_thread::sleep_for(std::chrono::milliseconds(500));
}