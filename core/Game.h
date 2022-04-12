#pragma once

#include "RenderEngine.h"
#include "Cube.h"


class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	void gameLoop();
	void update(const sf::Time& dt);
	void handleEvent();

	Cube* m_cube;

	bool m_running;
	sf::RenderWindow* m_window;
	RenderEngine* m_engine;
};

