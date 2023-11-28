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
    void setBoardConfig(); 
    void createBoardData();
    void createBoardData(std::string boardFile);
    void buildGameBoard(int width, int height);
    void displayBoardData();
    void renderBoard(sf::RenderWindow& window);
    void tileNeighborMines();

    Tile boardClick(sf::RenderWindow& window, bool Lclick);
    bool checkWin();

    int addAdjacentMines(int i);
    int getRows();
    int getCols();
    std::vector<int> getBoardData();
    std::vector<Tile> getGameBoard();
    void debugButton(sf::RenderWindow& window);

    //Constructor
    Board();
    std::unordered_map<std::string, Tile> testButtons;

private:
    int numOfCols, numOfRows, numOfMines, boardSize;
    std::vector<int> boardData;                                 // Stores the board as a 1-dim flattened array
    std::vector<Tile> gameboard;                                // Vector of tile objects
};
