#include "Player.h"
#include "Game.h"



Player::Player(Game* _board, std::mutex* _mutex)
{
	board = _board;
	mapmutex =_mutex;
	points = 0;
	inputName();
	setSprite('<');
	setPosition();
	board->addPlayer(this);
}

Game* Player::getBoard()
{
	return board;
}

void Player::inputName()
{
	std::cout << "Input player name: ";
	std::cin >> name;
}

void Player::setSprite(char _spr)
{
	sprite = _spr;
}

void Player::setPosition()
{
	x_pos = board->blindSpot_X();
	y_pos = board->blindSpot_Y();
	(*board)(x_pos, y_pos) = sprite;
}

int Player::getpos_X()
{
	return x_pos;
}

int Player::getpos_Y()
{
	return y_pos;
}

int Player::getPoints()
{
	return points;
}

void Player::moveLeft()
{
	mapmutex->lock();

	if (x_pos - 1 > 0 && (*board)(x_pos - 1, y_pos) != '-' && (*board)(x_pos - 1, y_pos) != '|')
	{
		if ((*board)(x_pos - 1, y_pos) == '+')
		{
			points++;
			setSprite('>');
			(*board)(x_pos - 1, y_pos) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			x_pos = x_pos - 1;
		}
		else
		{
			setSprite('>');
			(*board)(x_pos - 1, y_pos) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			x_pos = x_pos - 1;
		}
	}
	mapmutex->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Player::moveRight()
{
	mapmutex->lock();


	if (x_pos + 1 < (*board).getWidth() && (*board)(x_pos + 1, y_pos) != '-' && (*board)(x_pos + 1, y_pos) != '|')
	{
		if ((*board)(x_pos + 1, y_pos) == '+')
		{
			points++;
			setSprite('<');
			(*board)(x_pos + 1, y_pos) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			x_pos = x_pos + 1;
		}
		else
		{
			setSprite('<');
			(*board)(x_pos + 1, y_pos) = sprite; 
			(*board)(x_pos, y_pos) = ' ';
			x_pos = x_pos + 1;
		}
	}
	mapmutex->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Player::moveUp()
{
	mapmutex->lock();


	if (y_pos - 1 > 0 && (*board)(x_pos, y_pos - 1) != '-' && (*board)(x_pos, y_pos - 1) != '|')
	{
		if ((*board)(x_pos, y_pos - 1) == '+')
		{
			points++;
			setSprite('v');
			(*board)(x_pos, y_pos - 1) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			y_pos = y_pos - 1;
		}
		else
		{
			setSprite('v');
			(*board)(x_pos, y_pos - 1) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			y_pos = y_pos - 1;
		}
	}
	mapmutex->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

}

void Player::moveDown()
{
	mapmutex->lock();


	if (y_pos + 1 < (*board).getHeight() && (*board)(x_pos, y_pos + 1) != '-' && (*board)(x_pos, y_pos + 1) != '|')
	{
		if ((*board)(x_pos, y_pos + 1) == '+')
		{
			points++;
			setSprite('^');
			(*board)(x_pos, y_pos + 1) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			y_pos = y_pos + 1;
		}
		else
		{
			setSprite('^');
			(*board)(x_pos, y_pos + 1) = sprite;
			(*board)(x_pos, y_pos) = ' ';
			y_pos = y_pos + 1;
		}
	}
	mapmutex->unlock();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}