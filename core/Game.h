#pragma once

#include "RenderEngine.h"
#include "PhysicEngine.h"
#include "Cube.h"


class Game
{
public:
	Game();
	~Game();

	void Start();

private:
	void gameLoop();
	void handleEvent();

	void initObjects();
	Cube* m_cube;

	bool m_running;
	sf::RenderWindow* m_window;
	PhysicEngine* m_physic;
	RenderEngine* m_renderer;
};

