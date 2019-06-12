#include <iostream>
#include <thread>
#include <string>

#include "Game.h"
#include "Player.h"
#include "Ghost.h"
#include "functions.h"


int main()
{
	int choose;
	bool win;
	std::string wrongchoice;
	

	while (1)
	{
		Menu();
		std::cin >> choose;
		if (choose == 1)
		{
			Game master;
			std::mutex mutex;
			master.setMutex(&mutex);
			Player player(&master, &mutex);
			Ghost* ghost1 = new Ghost(&master, &mutex);
			std::thread plmv{ playerMove,&player, &win };
			std::thread ghmv_1{ ghostMove, ghost1 };
			plmv.join();
			ghmv_1.join();
			// Results:
			system("cls");
			if (win) endstatement(&player, "You won");
			else endstatement(&player, "You lose");
		}
		else if (choose == 2)
			return 0;
		else
			failure();
	}
	
	std::cin.get();
	return 0;
}