#pragma once
#include "Player.h"
#include "Ghost.h"
#include <iostream>
#include <time.h>
#include <conio.h>

///////////// Menu functions

void Menu();

void failure();

void endstatement(Player* _player, std::string s);


//////////// Gaming functions 
void playerMove(Player* _player, bool *_win);  //returns whether player won or not

int ghostVision(Ghost* _ghost, int _visiondistance); // returns : 1 - left; 2 - right; 3 - up; 4 - down; 0 - no vision

void ghostMove(Ghost* _ghost);