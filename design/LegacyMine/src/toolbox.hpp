#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.hpp"
#include "gamestate.hpp"


//Singleton  
class Toolbox
{
    private:
        static Toolbox* instancePtr;
        Toolbox(){};     //Singleton  Initializes the tools for game

    public:
        sf::RenderWindow window;    //SFML Application Window
        
        Gamestate* gamestate;   //Primary game state representation
        Button* debugButton;    //Reveals mines in debug mode
        Button* newGameButton;  //Resets / New game
        Button* testButton1;    //Load test board 1
        Button* testButton2;    //Load test board 2
        

        static Toolbox& getInstance() 
        {
            static Toolbox toolbox;
            return toolbox;
        };
};
