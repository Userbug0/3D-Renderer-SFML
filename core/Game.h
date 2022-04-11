#pragma once

#include "RenderEngine.h"


class Game
{
public:
	Game();
	~Game();;

	void Start();

private:
	void gameLoop();
	void update(const sf::Time& dt);
	void handleEvent();


	bool running_;
	sf::RenderWindow* window_;
	RenderEngine* engine_;
};

