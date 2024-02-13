#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

namespace MyWindow
{
	class Window
	{

	private:
		sf::VideoMode videomode;
		sf::RenderWindow* window;

		void InitWindow(unsigned width, unsigned height);
	public:

		Window(unsigned width, unsigned height);
		virtual ~Window();

		sf::RenderWindow* getWindow();






	};
}

