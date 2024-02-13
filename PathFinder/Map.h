#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace std;
using namespace sf;

constexpr short cell_width = 30;
constexpr short window_width = cell_width * 25;
constexpr short window_height = cell_width * 23;

enum MapInfo
{
    CELL_WIDTH = 30,
    WINDOW_WIDTH = window_width,
    WINDOW_HEIGHT = window_height
};

struct Node
{
    Vector2f position;
    bool isBarrier = false;
    bool visited = false;
    Node* parent = nullptr;

    Node(sf::Vector2f position_) : position(position_) {};
};

typedef map<Vector2f, Node*> cell_map;

class Map
{
private:

    

    
    cell_map map;

    Vector2f *Start = nullptr;
    Vector2f *Target = nullptr;

    std::map<Vector2f,RectangleShape> cells;

    void InitMap();
public:

   
    Map();

    std::map<Vector2f, Node*>* maps();
    cell_map* getMap();
    Vector2f* getStartPos();
    Vector2f* getTargetPos();

    void reset();
    
    std::map<Vector2f, RectangleShape>& getCells();
    void update(const RenderWindow &target);
    void render(RenderTarget &target);

    
};
