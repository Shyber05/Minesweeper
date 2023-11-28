#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "toolbox.hpp"


Tile::Tile(sf::Vector2f _position)
{
};

void revealNeighbors()
{
};


// Tile::State getState(){};

void setState(Tile::State _state)
{
    sf::Texture tileTexture;
    sf::Sprite tilesprite;
    Toolbox& toolbox = Toolbox::getInstance();
    

    if (_state == Tile::REVEALED)
    {
        tileTexture.loadFromFile("data\\images\\tile_reveled.png"); 
        tilesprite.setTexture(tileTexture);
    }
    else if (_state == Tile::HIDDEN)
    {
        tileTexture.loadFromFile("data\\images\\tile_hidden.png"); 
        tilesprite.setTexture(tileTexture);
    }
    else if (_state == Tile::FLAGGED)
    {
        tileTexture.loadFromFile("data\\images\\flag.png"); 
        tilesprite.setTexture(tileTexture);
    }
    else if (_state == Tile::EXPLOADED)
    {
        tileTexture.loadFromFile("data\\images\\mine.png"); 
        tilesprite.setTexture(tileTexture);
    };


};


void draw()
{
    sf::Sprite tilesprite;
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.window.draw(tilesprite);
};
