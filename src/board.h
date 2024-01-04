#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <fstream>
#include "textureManager.h"
#include "randomGen.h"
#include "tile.h"


class Board
{
public:
    // Initial functions / setup
    void setBoardConfig(); 
    // void createBoardData();
    void createBoardData(std::string boardFile);
    void buildGameBoard();
    void displayBoardData();
    void renderBoard(sf::RenderWindow& window);
    
    // Functionallity
    Tile boardClick(sf::RenderWindow& window, bool Lclick);
    void setNeighborTiles();
    void setAdjacentMines();
    void revealNeighborMines(int index);
    void displayMines();
    void restartGame(std::string boardType);     
    void changeRemaingingMines();

    //Getters
    int getRows();
    int getCols();
    std::vector<int> getBoardData();
    std::vector<Tile> getGameBoard();

    //Constructor
    Board();

private:
    std::unordered_map<std::string, Tile> funcButtons;
    int numOfCols, numOfRows, numOfMines, boardSize;
    int numOfFlags = 0;
    int RevealedTiles = 0;
    std::vector<int> boardData;                                 // Stores the board as a 1-dim flattened array
    std::vector<Tile> gameboard;                                // Vector of tile objects
    bool gameover = false;
};
