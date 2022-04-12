#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Settings.h"


Game::Game():
    m_running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Fun", sf::Style::Close, settings);
    m_window->setFramerateLimit(FPS);

	m_engine = new RenderEngine();
}


void Game::Start()
{
    m_engine->Start();

    m_running = true;

    gameLoop();
}


void Game::gameLoop()
{
    sf::Clock clock;

    while (m_running)
    {
        handleEvent();

        update(clock.getElapsedTime());
        clock.restart();

        m_engine->Render(m_window);
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


void Game::update(const sf::Time& dt)
{

}


Game::~Game()
{
    delete m_engine;
    delete m_window;
}
