#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "textureManager.h"
#include "randomGen.h"
#include "board.h"
#include "tile.h"

// =================================Prototypes================================
int launch(sf::RenderWindow& window, Board& board);
void eventHandling(sf::RenderWindow& window, Board& board);

int main()
{
    // 1. Initialize
    int LENGTH = 800;
    int WIDTH = 600;

    std::string dir = "images/";    
    TextureManager::setDirectory(dir);

    Board board;
    board.buildGameBoard(WIDTH, LENGTH);
    // board.displayBoardData();                  //TESTING

    sf::RenderWindow window(sf::VideoMode(LENGTH, WIDTH), "Minesweeper");

    // 2. Launch Game
    launch(window, board);

    // 3. Cleanup
    return 0;
}

// =================================Definitions================================
int launch(sf::RenderWindow& window, Board& board)
{
    while (window.isOpen())
    {
        eventHandling(window, board);

        // Clear the window with white color
        window.clear(sf::Color::White);

        // Render game
        //This is where we will draw the game
        board.renderBoard(window);

        // Ends the current frame
        window.display();
    }

    TextureManager::clear();
    return 0;
}

void eventHandling(sf::RenderWindow& window, Board& board)
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close the window
        if (event.type == sf::Event::Closed){
            window.close();
        } 
        // Right or left click mouse
        if (event.type == sf::Event::MouseButtonPressed){
            int x_cord = event.mouseButton.x;  
            int y_cord = event.mouseButton.y; 
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                //Reveal tile
                board.boardClick(window, true);
            }
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                //Add flag
                board.boardClick(window, false);
            }   

      
            // TESTING
            // std::cout << "x cord:" << x_cord << std::endl; 
            // std::cout << "y cord:" << y_cord << "\n\n"; 
        }
    }
}


// ============================LEGACY=========================================
/*
void renderBoard(sf::RenderWindow& window, Board& board)
{
    std::vector<Tile> gameBoard = board.getGameBoard();

    for (int i=0; i < (gameBoard.size()); i++)
    {
        sf::Sprite tileSprite = gameBoard[i].getSprite();
        window.draw(tileSprite);
    }
}
*/