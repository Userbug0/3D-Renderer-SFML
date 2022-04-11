#include <SFML/Graphics.hpp>

#include "Game.h"

#define WINDOW_WIDTH  = 800;
#define WINDOW_HEIGHT = 600;

#define FPS	= 500;



Game::Game():
    running_(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window_ = new sf::RenderWindow(sf::VideoMode(800, 600), "Fun", sf::Style::Close, settings);
    window_->setFramerateLimit(500);

	engine_ = new RenderEngine();
}


void Game::Start()
{
    engine_->Start();

    running_ = true;

    gameLoop();
}


void Game::gameLoop()
{
    sf::Clock clock;

    while (running_)
    {
        handleEvent();
        update(clock.getElapsedTime());
        engine_->Render(window_);
    }
}


void Game::handleEvent()
{
    sf::Event event;

    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            running_ = false;
    }
}


void Game::update(const sf::Time& dt)
{

}


Game::~Game()
{
    delete engine_;
    delete window_;
}
