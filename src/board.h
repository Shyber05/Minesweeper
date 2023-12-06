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
    void buildGameBoard(int width, int height);
    void displayBoardData();
    void renderBoard(sf::RenderWindow& window);
    
    // Functionallity
    Tile boardClick(sf::RenderWindow& window, bool Lclick);
    void displayAllMines();
    bool checkWin();
    void tileNeighborMines(std::vector<Tile>& gameboard);
    int addAdjacentMines(int i);
    void displayMines();
    void restartGame(std::string boardType);      // The random flag changes the loaded config
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
    std::vector<int> boardData;                                 // Stores the board as a 1-dim flattened array
    std::vector<Tile> gameboard;                                // Vector of tile objects
};
