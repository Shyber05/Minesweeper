#include <iostream>
#include <SFML/Graphics.hpp>
#include "toolbox.hpp"
#include "minesweeper.hpp"
#include "tile.hpp"
#include "gamestate.hpp"

int main(int, char**) {
    return launch();
}

int launch()
{
    Toolbox& toolbox = Toolbox::getInstance();

    //Entry point for game
    while (toolbox.window.isOpen())
    {
        //Close Window
        sf::Event event;
        while (toolbox.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                toolbox.window.close();
            }
            //Take user input here
        }

        toolbox.window.clear(sf::Color::White);
        //render
        toolbox.window.display();
    }
    return 0;
};

void restart()
{
};

void render()
{ 
    Toolbox& toolbox = Toolbox::getInstance();
    int gameStatus = toolbox.gamestate->getPlayStatus(); 
    sf::Vector2i dimensions = toolbox.gamestate->getDimensions();
    int x_dim = dimensions.x;
    int y_dim = dimensions.y;

  //Renders the game for playing 
    for (int row=1;row<=x_dim;row++)
    {
        for (int col=1;col<=y_dim;col++)
        {
           sf::Vector2f position((float)row, (float)col);
           Tile tile(position);
           tile.draw();
        }
    };

    if (gameStatus == Gamestate::PLAYING)
    {
    };

    if (gameStatus == Gamestate::LOSS)
    {
    };

    if (gameStatus == Gamestate::WIN)
    {
    };

};

void toggleDebugMode()
{

};

bool getDebugMode()
{
    return true;
};

/*
sf::Texture* getTextures()
{
    sf::Texture debug, digits, face_happy, face_lose, face_win, flag, mine, number_1, number_2,
        numeber_3, number_4, number_5, number_6, number_7, number_8, test_1, test_2, test_3,
        tile_hidden, tile_revealed;


};
*/
