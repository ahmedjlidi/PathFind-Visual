#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

class text
{
protected:
	sf::Text line;

public:
	text(sf::Font font, unsigned char_size, sf::Vector2f pos)
	{
		this->line.setFillColor(sf::Color::White);
		this->line.setFont(font);
		this->line.setOutlineThickness(2.f);
		this->line.setOutlineColor(sf::Color::Black);
		this->line.setCharacterSize(char_size);
		this->line.setPosition(pos);
	}

	sf::Text& getText()
	{
		return this->line;
	}

};

namespace gui
{
	class Time  : public text
	{
	private:
		float time;
	public:
		Time(sf::Font font,float time,sf::Vector2f pos);

		void render(sf::RenderTarget &target);

	};
}

