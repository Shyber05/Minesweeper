#pragma once 
#include <SFML/Graphics.hpp>
#include "tile.hpp"

class Gamestate
{

    public:
        //Tracks the game status
        enum PlayStatus {WIN, LOSS, PLAYING};

        //Contructs a new random gamestate with specified _dimensions and _numOfMines
        Gamestate(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numOfMines = 50);

        //Constructs gamestate based on size, mine placement, numOfMines specified in filepath
        Gamestate(const char* filepath);

        //Current count num of flags on screen
        int getFlagCount(){return flagCount;};
        //Current count of mines on the board
        int getMineCount(){return mineCount;};

        sf::Vector2i getDimensions(){return dimensions;};

        //Returns Tile at specified location or nullptr if out of bounds
        Tile* getTile(int x, int y);

        PlayStatus getPlayStatus();

        void setPlayStatus(PlayStatus _status);

     protected:
        int flagCount;
        int mineCount;
        sf::Vector2i dimensions;
        PlayStatus currentstatus;
 

};