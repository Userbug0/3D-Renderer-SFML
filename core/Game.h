#pragma once

#include "rendering/RenderEngine.h"
#include "physics/PhysicEngine.h"
#include "objects/GameObject.h"


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
	std::vector<GameObject*> m_objects;

	bool m_running;
	sf::RenderWindow* m_window;
	PhysicEngine* m_physic;
	RenderEngine* m_renderer;
};

