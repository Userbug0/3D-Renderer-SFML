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
    RegularPolygon* floor = new RegularPolygon(8, 10);
    floor->UsingLight = false;
    floor->GetTransform().translation += {0.175f, 0.33f, 3};
    floor->GetTransform().rotation += {-1.53f, 0, 0};
    m_objects.push_back(floor);

    Sphere* sphere = new Sphere(1.f, 3);
    sphere->GetTransform().translation += {0.f, -0.f, 2};
    sphere->GetTransform().rotation += {1.53f, 0, 0};
    sphere->SetColor({250, 150, 0});
    m_objects.push_back(sphere);

    //GameObject* torus = new GameObject("Resources/torus.obj");
    //torus->SetColor({ 150, 150, 0 });
    //torus->UsingLight = true;
    //torus->GetTransform().translation += {-2.f, -0.175f, 7};
    //m_objects.push_back(torus);

    //Cube* cube = new Cube(1, 1, 2);
    //cube->GetTransform().translation += { -0.5f, -0.5f, 5 };
    //cube->GetTransform().rotation += {0, 1, 0};
    //cube->SetColor(sf::Color::Green);
    //m_objects.push_back(cube);

    //Pyramid* pyramid = new Pyramid(3, 2, 20);
    //pyramid->GetTransform().translation += {5.f, 0.5f, 6};
    //pyramid->GetTransform().rotation += {1.53f, 0, 0};
    //pyramid->SetColor({0, 150, 0});
    //pyramid->SetBaseColor({ 10, 10, 0 });
    //m_objects.push_back(pyramid);

    //GameObject* axis = new GameObject("Resources/axis.obj");
    //axis->GetTransform().translation += {0, 2, 5};
    //axis->GetTransform().rotation += {1.7f, 2.2f, 0};
    //m_objects.push_back(axis);

    //GameObject* map = new GameObject("Resources/map.obj");
    //map->GetTransform().translation += {1.f, 1.f, 1};
    //map->GetTransform().rotation += {0.f, 0, 3.1f};
    //m_objects.push_back(map);
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
        else if (event.type == sf::Event::KeyPressed)
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
