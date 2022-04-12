#include "RenderEngine.h"


RenderEngine::RenderEngine(const sf::Color& bgColor)
	: m_backgroundColor(bgColor)
{

}


void RenderEngine::Render(sf::RenderWindow* window)
{
	window->clear(m_backgroundColor);

	window->display();
}


void RenderEngine::Start()
{

}
