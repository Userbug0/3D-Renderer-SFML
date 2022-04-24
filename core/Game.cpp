#include <SFML/Graphics.hpp>

#include "Game.h"
#include "objects\Cube.h"
#include "objects\Pyramid.h"
#include "objects\RegularPolygon.h"
#include "objects\Sphere.h"
#include "Settings.h"


Game::Game()
    : m_running(true)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_Window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Stuff", sf::Style::Close, settings);
    m_Window->setFramerateLimit(FPS);

    m_Camera = new Camera({0, 0, 0});
    m_Player = new Player(m_Camera);

    m_Renderer = new RenderEngine(m_Camera, { 1, 121, 191 });
    m_PhysicEngine = new PhysicEngine();

    initObjects();
}


void Game::initObjects()
{
    RegularPolygon* sun = new RegularPolygon(8, 6);
    sun->UsingLight = false;
    sun->GetTransform().translation += {0.175f, -5.f, -20};
    sun->SetColor(sf::Color::Yellow);
    sun->GetTransform().rotation += {0, 3.f, 0};
    m_objects.push_back(sun);

    RegularPolygon* floor = new RegularPolygon(8, 10);
    floor->UsingLight = false;
    floor->GetTransform().translation += {0.175f, 0.5f, 3};
    floor->GetTransform().rotation += {-1.53f, 0, 0};
    m_objects.push_back(floor);

    Pyramid* pyramid = new Pyramid(5, 3, 20);
    pyramid->GetTransform().translation += {2.f, 1.f, 10};
    pyramid->GetTransform().rotation += {1.53f, 0, 0};
    pyramid->SetColor({ 0, 250, 250 });
    pyramid->SetBaseColor({ 250, 0, 250 });
    m_objects.push_back(pyramid);

    Cube* cube = new Cube(1, 2, 2);
    cube->GetTransform().translation += { 4.f, -0.5f, 5 };
    cube->GetTransform().rotation += {0, 1.4f, 0};
    cube->SetColor(sf::Color::Green);
    m_objects.push_back(cube);

    Sphere* sphere = new Sphere(0.8f, 2);
    sphere->GetTransform().translation += {1.5f, 0, 4};
    sphere->GetTransform().rotation += {1.53f, 0, 0};
    sphere->SetColor({ 250, 150, 0 });
    m_objects.push_back(sphere);

    GameObject* torus = new GameObject("Resources/torus.obj");
    torus->SetColor({ 200, 200, 0 });
    torus->UsingLight = true;
    torus->GetTransform().translation += {-1.f, -0.1f, 3};
    m_objects.push_back(torus);

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

        m_Player->Update(clock.getElapsedTime());
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

        m_Renderer->HandleEvent(event);
        m_PhysicEngine->HandleEvent(event);

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                m_running = false;
        }
 
    }
}


Game::~Game()
{
    for (auto& object: m_objects)
        delete object;

    delete m_Camera;
    delete m_Player;
    delete m_Renderer;
    delete m_PhysicEngine;
    delete m_Window;
}
