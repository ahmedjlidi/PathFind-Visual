#include "Map.h"

namespace sf
{
    static bool operator<(const sf::Vector2f& left, const sf::Vector2f& right)
    {
        return (left.x != right.x) ? (left.x < right.x) : (left.y < right.y);
    }
}



void Map::InitMap()
{
    RectangleShape shape;
    shape.setSize(Vector2f(cell_width, cell_width));
    shape.setFillColor(Color::Blue);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(Color::Black);

    this->player.setSize(Vector2f(cell_width, cell_width));
    this->player.setFillColor(Color::Red);
    this->player.setOutlineThickness(1.f);
    this->player.setOutlineColor(Color::Black);


    for (short i = 0; i < MapInfo::WINDOW_WIDTH / MapInfo::CELL_WIDTH; ++i)
    {
        for (short j = 0; j < MapInfo::WINDOW_HEIGHT / MapInfo::CELL_WIDTH; ++j)
        {
            Vector2f pos = { static_cast<float>(cell_width * i), static_cast<float>(cell_width * j) };
            this->map[pos] = new Node(pos);

            shape.setPosition(pos);
            this->cells[shape.getPosition()] = (shape);
        }
    }
}

Map::Map()
{
    this->InitMap();
}

std::map<Vector2f, Node*>* Map::maps()
{
    return &this->map;
}

cell_map* Map::getMap()
{
    return &this->map;
}

Vector2f* Map::getStartPos()
{
    return this->Start;
}

Vector2f* Map::getTargetPos()
{
    return this->Target;
}

RectangleShape& Map::getPlayer()
{
    return this->player;
}

void Map::reset()
{
    this->Start = nullptr;
    this->Target = nullptr;

    for (auto& e : this->map)
        delete e.second;

    this->cells.clear();
    this->map.clear();

    this->InitMap();
}

std::map<Vector2f,RectangleShape>& Map::getCells()
{
    return this->cells;
}

void Map::update(const RenderWindow& target)
{
    for (auto& cell : this->cells)
    {
        if (sf::Keyboard::isKeyPressed(Keyboard::LShift) && Mouse::isButtonPressed(Mouse::Left)
            && cell.second.getGlobalBounds().contains(Vector2f(Mouse::getPosition(target)))
            && this->map.find(cell.second.getPosition()) != this->map.end())
        {
            if (this->Start || this->Target)
            {

                if (this->Start)
                {
                    if (cell.second.getPosition() == *this->Start)
                    {
                       
                        continue;
                    }
                }

                if (this->Target)
                {
                    if (cell.second.getPosition() == *this->Target)
                    {
                        continue;
                    }
                }
            }

            
             this->map[cell.second.getPosition()]->isBarrier = true;
             cell.second.setFillColor(Color(130, 126, 125));
            

        }


        else if (Mouse::isButtonPressed(Mouse::Left)
            && cell.second.getGlobalBounds().contains(Vector2f(Mouse::getPosition(target)))
            && this->map.find(cell.second.getPosition()) != this->map.end())
        {
            if (this->Start == nullptr)
            {
                this->Start = new Vector2f(cell.second.getPosition());
                cell.second.setFillColor(Color::Red);

                this->player.setPosition(*this->Start);
            }
        }
        else if (Mouse::isButtonPressed(Mouse::Right)
            && cell.second.getGlobalBounds().contains(Vector2f(Mouse::getPosition(target)))
            && this->map.find(cell.second.getPosition()) != this->map.end())
        {
            if (this->Target == nullptr)
            {
                this->Target = new Vector2f(cell.second.getPosition());
                cell.second.setFillColor(Color::Green);
            }
        }

        
    }
}

void Map::render(RenderTarget& target)
{
    for (const auto& cell : this->cells)
    {
        target.draw(cell.second);
    }
    if (this->Start)
    {
        target.draw(this->player);
    }
}

