#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <iostream>
#include "tile.h"
#include "textureManager.h"
#include "board.h"

//Constructor
Tile::Tile()
{
    State state = HIDDEN;
    std::string spriteImg = "tile_hidden";
    setState(state);
}

Tile::Tile(std::string image)
{
    // setPos(vector);
    setSprite(image);
}

// Functionality
void Tile::draw(sf::RenderWindow& window)
{
  window.draw(m_sprite); 
  if (overlay)
    window.draw(m_overlaySprite);
}

void Tile::addAdjacentMines(int numOfMines)
{
    adjacentMines += numOfMines;
}

// TODO finish function
void Tile::leftClick()
{
  if (getState() != State::FLAGGED)
  {
    if (isMine())
    {
      setState(State::EXPLODED);   //Game Over
    }
    else if (isMine() == false)
    {
      setState(State::REVEALED);
    }
  }

    //=========================TESTING==============================  
    // std::cout <<    "x: " << (m_sprite.getPosition().x / 32) << " "
                    // "y: " << (m_sprite.getPosition().y / 32) << "\n";
    // std::cout << "Mine: " << mine << " \n";
    // std::cout << "Surrounding Mines: " << adjacentMines << std::endl;
    // std::cout << "Index: " << index << std::endl;
}

void Tile::rightClick()
{
  if (getState() == State::HIDDEN) 
  {
    setState(State::FLAGGED);
  }
  else if (getState() == State::FLAGGED){
    setState(State::HIDDEN);
  }
}

bool Tile::isMine()
{
    if (mine == 1)
    {
        //Game over
        return true;
    }
    return false;
}

void Tile::splitDigitSprite(int digit)
{
  // Splites the digit texture into appropriate value
  // Each digits should be 21 x 32 pixels, so each digit should be an offset of 21 (the width)
  int offset = 21;
  int widthOffset = offset;
  int leftOffset = 0;
 switch (digit) {
  case 0:
    break;
  case 1:
    leftOffset = offset;
    break;
  case 2:
    leftOffset = offset * digit;
    break;
  case 3:
    leftOffset = offset * digit;
    break;
  case 4:
    leftOffset = offset * digit;
    break;
  case 5:
    leftOffset = offset * digit;
    break;
  case 6:
    leftOffset = offset * digit;
    break;
  case 7:
    leftOffset = offset * digit;
    break;
  case 8:
    leftOffset = offset * digit;
    break;
  case 9:
    leftOffset = offset * digit;
    break;
  case 10:
    leftOffset = offset * digit;
    break;
  }
  m_sprite.setTextureRect(sf::IntRect(leftOffset,0,(widthOffset),32));
}

// Setters
void Tile::setMine(int val)
{
    if (val == 0 || val == 1) {mine = val;}
    else{
        std::cout << "Not a valid option \n Needs to be (0 or 1) ";
    }
}

void Tile::setPos(sf::Vector2f vector)
{
    m_sprite.setPosition(vector);
    m_overlaySprite.setPosition(vector);
}

void Tile::setSprite(std::string imagePath)
{
    m_sprite.setTexture(TextureManager::getTexture(imagePath));
}

void Tile::setOverlaySprite(std::string imagePath)
{
    overlay = true;
    m_overlaySprite.setTexture(TextureManager::getTexture(imagePath));
}

void Tile::setNumberOverlay(){
  if (adjacentMines == 1)
    setOverlaySprite("number_1");
  else if (adjacentMines == 2)
    setOverlaySprite("number_2");
  else if (adjacentMines == 3)
    setOverlaySprite("number_3");
  else if (adjacentMines == 4)
    setOverlaySprite("number_4");
  else if (adjacentMines == 5)
    setOverlaySprite("number_5");
  else if (adjacentMines == 6)
    setOverlaySprite("number_6");
  else if (adjacentMines == 7)
    setOverlaySprite("number_7");
  else if (adjacentMines == 8)
    setOverlaySprite("number_8");
}

void Tile::setState(Tile::State state)
{
    std::string spriteImg;
    if (state == HIDDEN){
        overlay = false;
        spriteImg = "tile_hidden";
    }
    else if (state == REVEALED){
        setNumberOverlay();
        spriteImg = "tile_revealed";
    }
    else if (state == FLAGGED){
        spriteImg = "tile_hidden";
        setOverlaySprite("flag");
    }
    else if (state == EXPLODED){
        spriteImg = "tile_revealed";
        setOverlaySprite("mine");
    }
    currentState = state;
    setSprite(spriteImg);
}

// Getters
int Tile::getAdjacentMines()
{
  return adjacentMines;
}

void Tile::resetAdjacentMines()
{
  adjacentMines=0;
}
sf::Sprite Tile::getSprite()
{
    return m_sprite;
}

Tile::State Tile::getState()
{
    return currentState;
}

sf::Vector2f Tile::getPos()
{
    //Returns the position of the tile as a sf::vector2f
    return m_position;
}

