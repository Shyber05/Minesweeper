#include <SFML/Graphics.hpp>
//#include <SFML/Graphics/Sprite.hpp>
#include "button.hpp"

//Constructor
Button::Button(sf::Vector2f _position, std::function<void(void)>  onClick)
{
  fposition = _position;
}


void Button::setSprite(sf::Sprite* _sprite)
{
  sprite = *_sprite;
}


//Fuctionality for when the button is clicked
void onClick()
{
}
