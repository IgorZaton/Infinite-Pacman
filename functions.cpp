#include "functions.h"
#include "Game.h"

void Menu()
{
	std::cout << "\n\tINFINITE PACMAN\n";
	std::cout << "1. Start game" << std::endl;
	std::cout << "2. Exit" << std::endl;
}

void failure()
{
	std::cout << "Failure, try again:\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void endstatement(Player* _player, std::string s)
{
	std::cout << s << std::endl;
	std::cout << "points: " << _player->getPoints();
}

void playerMove(Player* _player, bool *_win)
{
	char b;
	bool win;
	while (!_player->getBoard()->gameEnd(win)) 
	{
			b = _getch();
			switch (b)
			{
			case 'w':	//up
				_player->moveUp();
				system("cls");
				_player->getBoard()->displayMap();
				break;
			case 's':	//down
				_player->moveDown();
				system("cls");
				_player->getBoard()->displayMap();
				break;
			case 'a':	//left
				_player->moveLeft();
				system("cls");
				_player->getBoard()->displayMap();
				break;
			case 'd':	//right
				_player->moveRight();
				system("cls");
				_player->getBoard()->displayMap();
				break;
			default:
				break;
			}
	}
	*_win = win;
}

int ghostVision(Ghost* _ghost, int _visiondistance)
{
	for (int i = 1; i <= _visiondistance; i++)
	{
		if (_ghost->getpos_X() - i != '-' && _ghost->getpos_X() - i != '|' && _ghost->getBoard()->currPlayerPos_X() == _ghost->getpos_X() - i && _ghost->getBoard()->currPlayerPos_Y() == _ghost->getpos_Y()) //left side
			return 1;
		else if (_ghost->getpos_X() + i != '-' && _ghost->getpos_X() + i != '|' && _ghost->getBoard()->currPlayerPos_X() == _ghost->getpos_X() + i && _ghost->getBoard()->currPlayerPos_Y() == _ghost->getpos_Y()) //right side
			return 2;
		else if (_ghost->getpos_Y() - i != '-' && _ghost->getpos_Y() - i != '|' && _ghost->getpos_Y() - i == _ghost->getBoard()->currPlayerPos_Y() && _ghost->getBoard()->currPlayerPos_X() == _ghost->getpos_X()) //up
			return 3;
		else if (_ghost->getpos_Y() + i != '-' && _ghost->getpos_Y() + i != '|' && _ghost->getpos_Y() + i == _ghost->getBoard()->currPlayerPos_Y() && _ghost->getBoard()->currPlayerPos_X() == _ghost->getpos_X()) //down
			return 4;
	}
	return 0;
}

void ghostMove(Ghost* _ghost)
{
	int ghostvision;
	bool isplrseen;
	bool win;
	while (!_ghost->getBoard()->gameEnd(win)) 
	{
		ghostvision = ghostVision(_ghost, 7);
		isplrseen = true;
		switch (ghostvision)
		{
		case 1:
			_ghost->moveLeft(isplrseen);
			system("cls");
			_ghost->getBoard()->displayMap();
			break;
		case 2:
			_ghost->moveRight(isplrseen);
			system("cls");
			_ghost->getBoard()->displayMap();
			break;
		case 3:
			_ghost->moveUp(isplrseen);
			system("cls");
			_ghost->getBoard()->displayMap();
			break;
		case 4:
			_ghost->moveDown(isplrseen);
			system("cls");
			_ghost->getBoard()->displayMap();
			break;
		case 0:
			int choose = rand() % 4 + 1;
			isplrseen = false;
			switch (choose)
			{
			case 1:
				_ghost->moveLeft(isplrseen);
				system("cls");
				_ghost->getBoard()->displayMap();
				break;
			case 2:
				_ghost->moveRight(isplrseen);
				system("cls");
				_ghost->getBoard()->displayMap();
				break;
			case 3:
				_ghost->moveUp(isplrseen);
				system("cls");
				_ghost->getBoard()->displayMap();
				break;
			case 4:
				_ghost->moveDown(isplrseen);
				system("cls");
				_ghost->getBoard()->displayMap();
				break;
			}
			break;
		}
		
	}
}