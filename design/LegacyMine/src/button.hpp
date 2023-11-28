#pragma once 
#include <SFML/Graphics.hpp>
#include <functional>
#include "button.hpp"


class Button
{
private:

    sf::Vector2f fposition;
    sf::Sprite sprite;

public:

    //Constructs a new object at the specified _postition which invokes the _onClick callback when clicked
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);

    sf::Vector2f getPosition(){return fposition;};
    
    //Returns the current sprite of the button
    sf::Sprite* getSprite(){return &sprite;}

    
    //Sets this button's visualization to the specified _sprite
    void setSprite(sf::Sprite* _sprite);
    
    //Invokes the button's callback method 
    void onClick();

};
