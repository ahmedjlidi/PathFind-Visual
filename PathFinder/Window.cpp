#include "Window.h"

using namespace MyWindow;

void Window::InitWindow(unsigned width, unsigned height)
{
	this->videomode.width = width;
	this->videomode.height = height;

	this->window = new sf::RenderWindow(this->videomode, "PathFind", sf::Style::Titlebar | sf::Style::Close);
}

Window::Window(unsigned width, unsigned height)
{
	this->InitWindow(width, height);

	
}

Window::~Window()
{
	delete this->window;
}

sf::RenderWindow* Window::getWindow()
{
	return this->window;
}



