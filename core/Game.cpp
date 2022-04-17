#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Settings.h"


Game::Game():
    m_running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fun", sf::Style::Close, settings);
    m_window->setFramerateLimit(FPS);

	m_renderer = new RenderEngine();
    m_physic = new PhysicEngine();

    initObjects();
}


void Game::initObjects()
{
    m_cube = new Cube();
    m_cube->Translate({ -0.5f, -0.5f, 1 });

}


void Game::Start()
{
    m_renderer->Start();
    m_physic->Start();

    m_running = true;

    gameLoop();
}


void Game::gameLoop()
{
    sf::Clock clock;

    while (m_running)
    {
        handleEvent();

        m_physic->Update(clock.getElapsedTime(), m_cube);
        clock.restart();

        m_renderer->Render(m_window, m_cube);
    }
}


void Game::handleEvent()
{
    sf::Event event;

    while (m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;
    }
}


Game::~Game()
{
    delete m_renderer;
    delete m_window;
}
