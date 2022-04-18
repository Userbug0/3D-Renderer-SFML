#include <SFML/Graphics.hpp>

#include "Game.h"
#include "objects\Cube.h"
#include "Settings.h"


Game::Game():
    m_running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D", sf::Style::Close, settings);
    m_window->setFramerateLimit(FPS);

	m_renderer = new RenderEngine();
    m_physic = new PhysicEngine();

    initObjects();
}


void Game::initObjects()
{
    //Cube* cube = new Cube();
    //cube->transform.position += { -0.5f, -0.5f, 2 };
    //cube->SetColor(sf::Color::Cyan);
    //m_objects.push_back(cube);

    //cube = new Cube();
    //cube->transform.position += { -0.5f, -0.5f, 5 };
    //cube->transform.rotation += {1, 1, 1};
    //cube->SetColor(sf::Color::Green);
    //m_objects.push_back(cube);

    GameObject* torus = new GameObject("Resources/torus.obj");
    torus->transform.position += {-0.5f, -0.5f, 5};
    m_objects.push_back(torus);
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

        m_physic->Update(clock.getElapsedTime(), m_objects);
        clock.restart();

        m_renderer->Render(m_window, m_objects);
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
    for (auto& object : m_objects)
        delete object;

    delete m_renderer;
    delete m_physic;
    delete m_window;
}
