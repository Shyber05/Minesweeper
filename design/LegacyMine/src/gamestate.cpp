#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "toolbox.hpp"


Gamestate::Gamestate(sf::Vector2i _dimensions, int _numofMines)
{
    Gamestate::mineCount = _numofMines;
};

/*
Gamestate(const char* filepath)
{

};
*/

/*
Tile* getTile(int x, int y)
{
    return 
};
*/

void setPlayStatus(Gamestate::PlayStatus _status){};


void getPlayStatus(){};
