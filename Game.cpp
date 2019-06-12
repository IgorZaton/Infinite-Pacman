#include "Game.h"



Game::Game()
{
	mapmutex = nullptr;
	inputName();
	loadMap();
	findBlindSpot();
	findGhostSpot();
}

Game::~Game()
{
	for (auto g : ghosts)
		delete g;
	for (int i = 0; i < height; i++)
		delete map[i];
	delete map;
}

void Game::inputName()
{
	std::cout << "Input map name: ";
	std::cin >> mapname;					
}

int Game::loadMap()
{
	std::ifstream mapfile;
	mapfile.open(mapname, std::ifstream::in);
	if (!mapfile.is_open())
	{
		std::cout << "File opening error";
		return 1;
	}
	else
	{
		mapfile >> height >> width;

		map = new char*[height];
		for (int i = 0; i < height; i++)
			map[i] = new char[width];

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
				mapfile.get(map[i][j]);
		}
		return 0;
	}
}

void Game::displayMap()
{
	if (mapmutex!=nullptr) mapmutex->lock();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
	if (mapmutex != nullptr) mapmutex->unlock();
}

void Game::setMutex(std::mutex* _mutex)
{
	mapmutex = _mutex;
}

void Game::addPlayer(Player* _player)
{
	player = _player;

}

void Game::addGhost(Ghost* _ghost)
{
	ghosts.push_back(_ghost);
}

void Game::findBlindSpot()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == ' ')
			{
				blindspot[0] = j;
				blindspot[1] = i;
			}
		}
	}
}

void Game::findGhostSpot()
{
	int potential_x = blindspot[0], potential_y = blindspot[1];
	bool flag, exitflag, solutionflag;
	if (blindspot[0] - width / 3 > 0) //checking left
	{
		exitflag = 0; flag = 0; solutionflag = 0;
		potential_x = blindspot[0] - width / 3;
		if (map[potential_y][potential_x] == '+')
		{
			ghostspot[0] = potential_x;
			ghostspot[1] = potential_y;
			solutionflag = true;
		}
		else
		{
			while (map[potential_y][potential_x] != '+' && abs(potential_x - blindspot[0]) > 7 )  // seven is min player - ghost distance
			{																					 // at the beginning 
				if (!flag) 
				{ 
					potential_x++; 
					if(potential_y < height - 1) potential_y++;
					flag = 1;
				}
				else
				{
					potential_x++;
					if (potential_y > 1) potential_y--;
					flag = 0;
				}
				if (abs(potential_x - blindspot[0]) == 7)
				{
					exitflag = 1;
					break;
				}
			}
			if (!exitflag) 
			{
				ghostspot[0] = potential_x;
				ghostspot[1] = potential_y;
				solutionflag = true;
			}
		}
	}
	if (blindspot[0] + width / 3 < width) //checking right
	{
		exitflag = 0; flag = 0; solutionflag = 0;
		potential_x = blindspot[0] + width / 3;
		if (map[potential_y][potential_x] == '+')
		{
			ghostspot[0] = potential_x;
			ghostspot[1] = potential_y;
			solutionflag = true;
		}
		else
		{
			while (map[potential_y][potential_x] != '+')
			{
				if (!flag)
				{
					potential_x--;
					if (potential_y < height - 1) potential_y++;
					flag = 1;
				}
				else
				{
					potential_x--;
					if (potential_y > 1) potential_y--;
					flag = 0;
				}
				if (abs(potential_x - blindspot[0]) == 7)
				{
					exitflag = 1;
					break;
				}
			}
			if (!exitflag)
			{
				ghostspot[0] = potential_x;
				ghostspot[1] = potential_y;
				solutionflag = true;
			}
		}
	}
	if (blindspot[1] - height / 3 < height) //checking up
	{
		exitflag = 0; flag = 0; solutionflag = 0;
		potential_y = blindspot[1] - height / 3;
		if (map[potential_y][potential_x] == '+')
		{
			ghostspot[0] = potential_x;
			ghostspot[1] = potential_y;
			solutionflag = true;
		}
		else
		{
			while (map[potential_y][potential_x] != '+' && abs(potential_x - blindspot[0]) > 7)
			{
				if (!flag)
				{
					potential_y++;
					if (potential_x < width - 1) potential_x++;
					flag = 1;
				}
				else
				{
					potential_y++;
					if (potential_x > 1) potential_x--;
					flag = 0;
				}
				if (abs(potential_x - blindspot[0]) == 7)
				{
					exitflag = 1;
					break;
				}
			}
			if (!exitflag)
			{
				ghostspot[0] = potential_x;
				ghostspot[1] = potential_y;
				solutionflag = true;
			}
		}
	}
	if (blindspot[1] + height / 3 < height) //checking down
	{
		exitflag = 0; flag = 0; solutionflag = 0;
		potential_y = blindspot[1] + height / 3;
		if (map[potential_y][potential_x] == '+')
		{
			ghostspot[0] = potential_x;
			ghostspot[1] = potential_y;
			solutionflag = true;
		}
		else
		{
			while (map[potential_y][potential_x] != '+' && abs(potential_x - blindspot[0]) > 7)
			{
				if (!flag)
				{
					potential_y--;
					if (potential_x < width - 1) potential_x++;
					flag = 1;
				}
				else
				{
					potential_y--;
					if (potential_x > 1) potential_x--;
					flag = 0;
				}
				if (abs(potential_x - blindspot[0]) == 7)
				{
					exitflag = 1;
					break;
				}
			}
			if (!exitflag)
			{
				ghostspot[0] = potential_x;
				ghostspot[1] = potential_y;
				solutionflag = true;
			}
		}
	}
	if(!solutionflag) //find first in the row
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i][j] == '+')
				{
					ghostspot[0] = j;
					ghostspot[1] = i;
				}
			}
		}
	}
}

int Game::accessiblePoints()
{
	int points = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == '+') points++;
		}
	}
	return points;
}

int Game::blindSpot_X()
{
	return blindspot[0];
}

int Game::blindSpot_Y()
{
	return blindspot[1];
}

int Game::ghostSpot_X()
{
	return ghostspot[0];
}

int Game::ghostSpot_Y()
{
	return ghostspot[1];
}

int Game::getHeight()
{
	return height;
}

int Game::getWidth()
{
	return width;
}

int Game::currPlayerPos_X()
{
	return player->getpos_X();
}

int Game::currPlayerPos_Y()
{
	return player->getpos_Y();
}

bool Game::collision()
{
	for (Ghost* bot : ghosts)
	{
		if (player->getpos_X() == bot->getpos_X() && player->getpos_Y() == bot->getpos_Y())
			return 1;
	}
	return 0;

}

bool Game::playerwin()
{
	if (!player->getBoard()->accessiblePoints()) return 1;
	return 0;
}

bool Game::gameEnd(bool& _win)
{
	if (playerwin())
	{
		_win = true;
		return true;
	}
	else if (collision())
	{
		_win = false;
		return true;
	}
	return false;
}

//operators

char& Game::operator()(int _x, int _y)
{
	assert(_x > 0 && _x < width);
	assert(_y > 0 && _y < height);
	return map[_y][_x];
}