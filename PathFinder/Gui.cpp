#include "Gui.h"

gui::Time::Time(sf::Font font, float time, sf::Vector2f pos) : text(font, 45,  pos)
{

}

void gui::Time::render(sf::RenderTarget& target)
{
	this->line.setString(std::to_string(this->time));

	target.draw(this->line);
}
