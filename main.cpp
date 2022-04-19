#include <iostream>

#include "core/Game.h"
#include "core/Settings.h"


int main()
{
	Game game;

	try 
	{
		game.Start();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
		return 1;
	}


	return 0;
}
