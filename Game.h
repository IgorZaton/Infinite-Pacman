#pragma once
#include "Ghost.h"
#include "Player.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

class Game
{
public:
	Game();
	~Game();
	void displayMap();
	void setMutex(std::mutex* _mutex);
	void addPlayer(Player* _player);
	void addGhost(Ghost* _ghost);
	int accessiblePoints();
	int ghostSpot_X();
	int ghostSpot_Y();
	int blindSpot_X();
	int blindSpot_Y();
	int getHeight();
	int getWidth();
	int currPlayerPos_X();
	int currPlayerPos_Y();
	bool collision();
	bool playerwin();
	bool gameEnd(bool& _win);
	char& operator()(int _x, int _y);
private:
	void findGhostSpot();
	void findBlindSpot();
	int loadMap();
	void inputName();

	Player* player;
	std::vector<Ghost*> ghosts;

	std::mutex* mapmutex;
	std::string mapname;
	int height;
	int width;
	char **map;
	int blindspot[2]; //x,y
	int ghostspot[2];

};