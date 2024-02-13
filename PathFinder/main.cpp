#include <iostream>
#include <queue>
#include <map>
#include "Window.h"
#include "Map.h"

using namespace std;
using namespace sf;


//Window

MyWindow::Window* win = new MyWindow::Window(static_cast<float>(MapInfo::WINDOW_WIDTH + 400.f)
    , static_cast<float>(MapInfo::WINDOW_HEIGHT));
Event event;
//map
Map* grid_map = new Map();
std::vector<sf::Vector2f> path;
static Clock timer;
int distance = 0;
static map<string, Text> texts;

bool vector2fEqual(const sf::Vector2f& left, const sf::Vector2f& right)
{
    // Define a small epsilon for approximate equality check
    const float epsilon = 0.0001f;
    return std::abs(left.x - right.x) < epsilon && std::abs(left.y - right.y) < epsilon;
}

namespace sf
{
    static bool operator<(const sf::Vector2f& left, const sf::Vector2f& right)
    {
        return (left.x != right.x) ? (left.x < right.x) : (left.y < right.y);
    }

}

void reset()
{
    grid_map->reset();

}
template<typename Key, typename Value>
bool bfs(Vector2f StartP, Vector2f Target, std::map<Key, Value>& Map, std::vector<sf::Vector2f>& path)
{
    int moves[4][2] = { {-1, 0}, {0, 1}, {0, -1}, {1, 0} };
    std::queue<Node*> nodes;

    // Assuming starting position is (0, 0)
    sf::Vector2f start = StartP;

    // Find the starting node in the map
    auto startNodeIt = Map.find(start);
    if (startNodeIt == Map.end()) {
        // Handle the case where the starting node is not found
        return false;
    }

    Node* startNode = startNodeIt->second;

    nodes.push(startNode);

    while (!nodes.empty())
    {
        Node* currentNode = nodes.front();
        nodes.pop();
        currentNode->visited = true;

        
            if (currentNode->position == Target)
            {
                // Retrieve the path
                Node* current = currentNode;
                while (current)
                {
                        path.push_back(current->position);

                    // Add a check for nullptr before accessing the parent
                    if (current->parent)
                    {
                        current = current->parent;
                    }
                    else
                    {
                        break;  // Break the loop if the parent is nullptr
                    }
                }

                // Reverse the path to get it from start to target
                std::reverse(path.begin(), path.end());

                return true;
            }

            // Process the current node as needed

            // Enqueue unvisited neighbors
            for (int i = 0; i < 4; ++i)
            {
                sf::Vector2f newPos = currentNode->position + sf::Vector2f(moves[i][0] * cell_width, moves[i][1] * cell_width);
                // Check if the key exists in the map before accessing it
                auto neighborNodeIt = Map.find(newPos);

                if (neighborNodeIt != Map.end() && !neighborNodeIt->second->visited && !neighborNodeIt->second->isBarrier)
                {
                    Node* neighborNode = neighborNodeIt->second;
                    neighborNode->visited = true;
                    neighborNode->parent = currentNode;
                    nodes.push(neighborNode);
                }
            }
        
    }

    return false;
}


void printPath(std::vector<sf::Vector2f>& path, Map &map, Vector2f &StartP, Vector2f &Target)
{

    for (const auto e : path)
    {
        if(e != StartP&& e!= Target )
            map.getCells()[e].setFillColor(Color::Yellow);

    }
}


void renderGUi(RenderTarget& target)
{
   
    static const vector<string>names = { "ALGO_NAME"  "TIME", "CONTROLS", "DISTANCE"};
    static Font font;
    font.loadFromFile("PixelifySans-Regular.ttf");



    for (auto& text : texts)
    {
        text.second.setFillColor(Color::White);
        text.second.setFont(font);
        text.second.setOutlineThickness(2.f);
        text.second.setOutlineColor(Color::Black);
        if (text.first == names[0])
            text.second.setCharacterSize(70.f);
        else
            text.second.setCharacterSize(30.f);

    }

    texts["ALGO_NAME"].setString("Breadth-first search");
    texts["ALGO_NAME"].setPosition((MapInfo::WINDOW_WIDTH + 175.f ) - (texts["ALGO_NAME"].getGlobalBounds().width / 2.f),
        (texts["ALGO_NAME"].getGlobalBounds().height));

    texts["CONTROLS"].setString("Start: left-click\n\n"
        "Target: right-click\n\n"
        "barriers: left-click + Lshift\n\n"
        "Start algorithm: Enter\n\n"
        "Reset algorithm: R\n");

    texts["CONTROLS"].setPosition((MapInfo::WINDOW_WIDTH + 175.f) - (texts["ALGO_NAME"].getGlobalBounds().width / 2.f),
        (200.f));


    for (auto& e : texts)
    {
        target.draw(e.second);
    }
}

int main()
{
    
    
    auto window = win->getWindow();
    static int index = 0;
    while (window->isOpen())
    {
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }


        grid_map->update(*window);
        if (grid_map->getStartPos() && grid_map->getTargetPos()
            && Keyboard::isKeyPressed(Keyboard::Enter))

        {

            if (index <= 0)
            {
                bfs(*grid_map->getStartPos(), *grid_map->getTargetPos(), *grid_map->getMap(), path);
                printPath(path, *grid_map, *grid_map->getStartPos(), *grid_map->getTargetPos());
               

            }


            ++index;

        }
        else
            timer.restart();

        if (Keyboard::isKeyPressed(Keyboard::R))
        {
            reset();
            index = 0;
            path.clear();

        }
        window->clear(Color::Black);
        grid_map->render(*window);

        renderGUi(*window);
        window->display();
    }
    
    return 0;
}

