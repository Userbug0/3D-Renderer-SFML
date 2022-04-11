#include "RenderEngine.h"


RenderEngine::RenderEngine(const sf::Color& bgColor)
	: backgroundColor_(bgColor)
{

}


void RenderEngine::Render(sf::RenderWindow* window)
{
	window->clear(backgroundColor_);

	window->display();
}


void RenderEngine::Start()
{

}
