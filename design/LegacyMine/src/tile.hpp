#pragma once 
#include <SFML/Graphics.hpp>


class Tile
{
    public:
        //Represents the current UI state
        enum State{ REVEALED, HIDDEN, FLAGGED, EXPLOADED};

        //Constructs a new tile at postition
        Tile(sf::Vector2f _position);

        //Returns the current location of tile
        sf::Vector2f getLocation(){return position;};

        //Returns current state of Tile
        State getState();

        //Returns Ptr to array of Tile pointers
        /*  Ordering
            |0 1 2|
            |3 X 4|
            |5 6 7|     */
        std::array<Tile*, 8>& getNeighbors();

        //Sets the state of the tile, should trigger any behavior related to that state
        void setState(State _state);

        //Populates and replaces the neighboring tile containers
        void setNeighbors(std::array<Tile*, 8> _neighbors);

        //Defines behavior when the left mouse is clicked reveals it 
        void onClickLeft();

        //Toggles state FLAGGED and HIDDEN
        void onClickRight();

        //Render tile to screen according to state
        void draw();

     protected:
        //Based on State and mine content of the tile neighbors, set their state to REVEALED
        void revealNeighbors();
        sf::Vector2f position;
        State currentState;
};
