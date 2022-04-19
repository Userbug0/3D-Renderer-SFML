#include <SFML/Graphics.hpp>

#include "Game.h"
#include "objects\Cube.h"
#include "Settings.h"


Game::Game():
    m_running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D", sf::Style::Close, settings);
    m_Window->setFramerateLimit(FPS);

    m_Camera = new Camera({0, 0, 0});
	m_Renderer = new RenderEngine(m_Camera);
    m_PhysicEngine = new PhysicEngine();

    initObjects();
}


void Game::initObjects()
{
    Cube* cube = new Cube();
    cube->transform.position += { -0.5f, -0.5f, 3 };
    cube->SetColor(sf::Color::Cyan);
    m_objects.push_back(cube);

    //Cube* cube = new Cube();
    //cube->transform.position += { -0.5f, -0.5f, 5 };
    ////cube->transform.rotation += {1, 1, 1};
    //cube->SetColor(sf::Color::Green);
    //m_objects.push_back(cube);

    //GameObject* torus = new GameObject("Resources/torus.obj");
    //torus->transform.position += {0.175f, -0.175f, 3};
    //m_objects.push_back(torus);
}


void Game::Start()
{
    m_Renderer->Start();
    m_PhysicEngine->Start();

    m_running = true;

    gameLoop();
}


void Game::gameLoop()
{
    sf::Clock clock;

    while (m_running)
    {
        handleEvent();

        m_PhysicEngine->Update(clock.getElapsedTime(), m_objects);
        clock.restart();

        m_Renderer->Render(m_Window, m_objects);
    }
}


void Game::handleEvent()
{
    sf::Event event;

    while (m_Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;
    }
}


Game::~Game()
{
    for (auto& object : m_objects)
        delete object;

    delete m_Camera;
    delete m_Renderer;
    delete m_PhysicEngine;
    delete m_Window;
}
