#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include "textureManager.h"
#include "randomGen.h"
#include "board.h"


Board::Board()
{
    setBoardConfig();
    createBoardData();


    //====================================TESTING=================================
    // createBoardData("lots_o_mines");        
    displayBoardData();                 
    // buildGameBoard();
}

void Board::setBoardConfig()
{
    // Reads in the Cols,Rows,numOfMines from board/config.cfg
    std::string filePath = "boards/config.cfg";   
    std::vector<int> values;
    std::string num;

    std::ifstream configFile;
    configFile.open(filePath); 

    while(getline (configFile, num))                  
    {
        values.push_back(stoi(num));
    };
    configFile.close();

    numOfCols  = values[0];
    numOfRows  = values[1];
    numOfMines = values[2];
    boardSize = (numOfCols * numOfRows);

    //Can't have less than 22 columns
    if (numOfCols < 22) {
        numOfCols = 22;
    } 
}

void Board::createBoardData()
{
    // 1. Create from board attributes
    boardData.resize(boardSize);

    // Picks positions ar random and places mine
    for (int mines=0; mines <= (numOfMines); mines++)
    {
        int pos = RandomGen::intGenerator(0, (boardSize));       // Random number between 0 - size of board  
        if (boardData[pos] == 0)
        {
            boardData[pos] = 1;
        }
    }
}

void Board::createBoardData(std::string boardFile)
{
    // 2. Create from a .brd file
    std::string dir = "boards/";                // TESTING
    std::string ext = ".brd";

    std::string filePath = dir + boardFile + ext;
    std::ifstream inputBoard;
    inputBoard.open(filePath);

    char val;
    while(inputBoard.get(val))
    {
        // Subtract by 48 to get the ASCII char to int
        if (val == '1'){
            boardData.push_back(((int)val - 48));
        }
        else if (val == '0') {
            boardData.push_back(((int)val - 48));
        }
    }

}

void Board::buildGameBoard(int length, int width)
{
    // Creates the game Board of Tiles
    int i=0;
    for (int col=0; col < getCols(); col++)  
    {
        for (int row=0; row < getRows(); row++)  
        {
            Tile tile;
            tile.setMine(boardData[i]); 
            sf::IntRect spriteRect = (tile.getSprite()).getTextureRect();       // Gets the rectangle of the tile
            tile.setPos(sf::Vector2f((float)(spriteRect.height * col), (float)(spriteRect.width * row)));   //sets the position of the tile based on the previous command
            gameboard.push_back(tile);
            i++;
        }
    }

  //TODO fix test buttons
    // Creates the game buttons     Doesn't WORK (-_-)
    Tile Smiley(sf::Vector2f((length*0.45),(width-87)), "face_happy");
    Tile Test1(sf::Vector2f((length*0.65),(width-87)), "test_1");
    Tile Test2(sf::Vector2f((length*0.75),(width-87)), "test_2");
    Tile Test3(sf::Vector2f((length*0.85),(width-87)), "test_3");
    Tile Debug(sf::Vector2f((length*0.55),(width-87)), "debug");
    Tile Flags(sf::Vector2f((length*0.05),(width-87)), "digits");

    testButtons.emplace("Smiley", Smiley);
    testButtons.emplace("Test1", Test1);
    testButtons.emplace("Test2", Test2);
    testButtons.emplace("Test3", Test3);
    testButtons.emplace("Debug", Debug);
    testButtons.emplace("Flags", Flags);
}

void Board::displayBoardData()
{ 
    // Displays the boards information
    // ===================TESTING====================
    std::cout << "BoardSize: "  << boardSize << "\n";
    std::cout << "numOfRows: "  << numOfRows << "\n";
    std::cout << "numOfCols: "  << numOfCols << "\n";
    std::cout << "numOfMines: " << numOfMines << "\n";


    // {1 (mine) or 0 (not a mine)}
    for (int i=0; i <= boardSize; i++)
    {
    //TODO fix but, Doesn't account for first value
        std::cout << boardData[i] << " ";
        if (((i % numOfCols) == 0)){

            std::cout << "Row: " << (i / numOfCols);                  // TESTING
            std::cout <<"\n";
        }
    }
}

void Board::renderBoard(sf::RenderWindow& window)
{
    // Renders the board to a window
    for (int i=0; i < (gameboard.size()); i++)
    {
        gameboard[i].draw(window);
    }

    // Renders game buttons (Not working)
    testButtons["Smiley"].draw(window);
    testButtons["Test1"].draw(window);
    testButtons["Test2"].draw(window);
    testButtons["Test3"].draw(window);
    testButtons["Debug"].draw(window);
    testButtons["Flags"].draw(window);
}

Tile Board::boardClick(sf::RenderWindow& window, bool Lclick)
{
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
    for (int i=0; i < gameboard.size(); i++) 
    {
        sf::Sprite sprite = gameboard[i].getSprite();
        if (sprite.getGlobalBounds().contains(translatedPos))
        {
            if(Lclick){
                gameboard[i].leftClick();
            }
            else{
                gameboard[i].rightClick();
            }
            return (gameboard[i]);
        }
    }
    return gameboard[0];
}

//==============================Accessors==================================
int Board::getCols()
{
    return numOfCols;
}

int Board::getRows()
{
    return numOfRows;
}

std::vector<int> Board::getBoardData()
{
    return boardData;
}

std::vector<Tile> Board::getGameBoard()
{
    return gameboard;
}

void Board::displayAllMines()
{
    
};

