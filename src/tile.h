#pragma once
#include <vector>
#include <unordered_map>
#include "textureManager.h"
#include <SFML/Graphics.hpp>


class Tile
{
public:
    //Constructors
    Tile();
    Tile(std::string);    // Creates a tile with specific Sprite

    enum State{FLAGGED, HIDDEN, REVEALED, EXPLODED};        // Current state of the UI

    // Setters
    void setState(State state);
    void setMine(int val);
    void setPos(sf::Vector2f vector);
    void setSprite(std::string);
    void setOverlaySprite(std::string imagePath);
    void setNumberOverlay();

    //Getters
    State getState(); 
    sf::Sprite getSprite();
    sf::Vector2f getPos();
    int getAdjacentMines();

    // Functionallity
    void draw(sf::RenderWindow& window);            // Renders tile to window with it's sprite
    void rightClick();      // Toggles flag
    void leftClick();       // Reveals tile
    bool isMine();         

    void splitDigitSprite(int digit);
    void resetAdjacentMines();
    void addAdjacentMines(int numOfMines);      
    int mine;
    bool overlay = false;    // Determines whether to draw spites on each other
    sf::Sprite m_overlaySprite;
    std::vector<Tile*> adjacentTiles;
    int index;    // Used to help with letting the tile know it's place in the gameboard

private:
    int adjacentMines = 0;
    State currentState;
    sf::Vector2f m_position;
    sf::Sprite m_sprite;
    
};
