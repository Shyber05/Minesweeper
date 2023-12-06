#include "board.h"
#include "randomGen.h"
#include "textureManager.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Board::Board()
{
  setBoardConfig();
  createBoardData("random");

  //====================================TESTING=================================
  // createBoardData("lots_o_mines");
  displayBoardData();
  // buildGameBoard();
}

void
Board::setBoardConfig()
{
  // Reads in the Cols,Rows,numOfMines from board/config.cfg
  std::string filePath = "boards/config.cfg";
  std::vector<int> values;
  std::string num;

  std::ifstream configFile;
  configFile.open(filePath);

  while (getline(configFile, num)) {
    values.push_back(stoi(num));
  };
  configFile.close();

  numOfCols = values[0];
  numOfRows = values[1];
  numOfMines = values[2];
  boardSize = (numOfCols * numOfRows);

  // Can't have less than 22 columns
  if (numOfCols < 22) {
    numOfCols = 22;
  }
}

void
Board::createBoardData(std::string boardFile)
{

  if (boardFile == "random") 
  {
    // 1. Create from board attributes
    boardData.resize(boardSize);

    // Picks positions ar random and places mine
    for (int mines = 0; mines <= (numOfMines); mines++) {
      int pos = RandomGen::intGenerator(
        0, (boardSize)); // Random number between 0 - size of board
      if (boardData[pos] == 0) {
        boardData[pos] = 1;
      }
      else 
      {
        mines--; // If it lands on a mine (1) don't add 1
      }
    }
  } else {
    // 2. Create from a .brd file
    std::string dir = "boards/"; // TESTING
    std::string ext = ".brd";

    std::string filePath = dir + boardFile + ext;
    std::ifstream inputBoard;
    inputBoard.open(filePath);

    char val;
    while (inputBoard.get(val)) {
      // Subtract by 48 to get the ASCII char to int
      if (val == '1') {
        boardData.push_back(((int)val - 48));
      } else if (val == '0') {
        boardData.push_back(((int)val - 48));
      }
    }
  }
}

void
Board::buildGameBoard(int length, int width)
{
  // Creates the game Board of Tiles
  int i = 0;
  for (int col = 0; col < getCols(); col++) {
    for (int row = 0; row < getRows(); row++) {
      Tile tile;
      tile.setMine(boardData[i]);
      sf::IntRect spriteRect =
        (tile.getSprite()).getTextureRect(); // Gets the rectangle of the tile
      tile.setPos(sf::Vector2f(
        (float)(spriteRect.height * col),
        (float)(spriteRect.width * row))); // sets the position of the tile
                                           // based on the previous command
      gameboard.push_back(tile);
      i++;
    }
  }
  
  //Sets each mines neighbors
  tileNeighborMines(gameboard);

  Tile Smiley("face_happy");
  Tile Test1("test_1");
  Tile Test2("test_2");
  Tile Test3("test_3");
  Tile Debug("debug");
  sf::IntRect spriteRect =
    (Smiley.getSprite())
      .getTextureRect(); // Gets the rectangle for the test buttons

  // TODO need to fix the values above so they aren't hard coded
  // Set position of these similarly sized buttons (Hard Coded)
  Smiley.setPos(sf::Vector2f((float)(spriteRect.height * 6),
                             (float)(spriteRect.width * 8)));
  Debug.setPos(sf::Vector2f((float)(spriteRect.height * 8.5),
                            (float)(spriteRect.width * 8)));
  Test1.setPos(sf::Vector2f((float)(spriteRect.height * 9.5),
                            (float)(spriteRect.width * 8)));
  Test2.setPos(sf::Vector2f((float)(spriteRect.height * 10.5),
                            (float)(spriteRect.width * 8)));
  Test3.setPos(sf::Vector2f((float)(spriteRect.height * 11.5),
                            (float)(spriteRect.width * 8)));

  // Loads in one long texture then splits it up into different sprites
  Tile Digit0("digits");
  Tile Digit1("digits");
  Tile Digit2("digits");
  
  Digit0.splitDigitSprite(0);
  Digit1.splitDigitSprite(0);
  Digit2.splitDigitSprite(0);

  
  Digit0.setPos(sf::Vector2f((float)(spriteRect.height * 0.3),
                            (float)(spriteRect.width * 8)));
  Digit1.setPos(sf::Vector2f((float)(spriteRect.height * 0.6),
                            (float)(spriteRect.width * 8)));
  Digit2.setPos(sf::Vector2f((float)(spriteRect.height * 0.9),
                            (float)(spriteRect.width * 8)));

  // sf::Vector2f((length*0.73),(width-87)),
  funcButtons.emplace("Smiley", Smiley);
  funcButtons.emplace("Test1", Test1);
  funcButtons.emplace("Test2", Test2);
  funcButtons.emplace("Test3", Test3);
  funcButtons.emplace("Debug", Debug);
  funcButtons.emplace("Remaining0", Digit0);
  funcButtons.emplace("Remaining1", Digit1);
  funcButtons.emplace("Remaining2", Digit2);
}

void
Board::displayBoardData()
{
  // Displays the boards information
  // ===================TESTING====================
  std::cout << "BoardSize: " << boardSize << "\n";
  std::cout << "numOfRows: " << numOfRows << "\n";
  std::cout << "numOfCols: " << numOfCols << "\n";
  std::cout << "numOfMines: " << numOfMines << "\n";

  // {1 (mine) or 0 (not a mine)}
  for (int i = 0; i <= boardSize; i++) {
    // TODO fix but, Doesn't account for first value
    std::cout << boardData[i] << " ";
    if (((i % numOfCols) == 0)) {

      std::cout << "Row: " << (i / numOfCols); // TESTING
      std::cout << "\n";
    }
  }
}

void
Board::renderBoard(sf::RenderWindow& window)
{
  // Renders the board to a window
  for (int i = 0; i < boardSize; i++) {
    gameboard[i].draw(window);
  }
       
  // Renders game buttons 
  funcButtons["Smiley"].draw(window);
  funcButtons["Test1"].draw(window);
  funcButtons["Test2"].draw(window);
  funcButtons["Test3"].draw(window);
  funcButtons["Debug"].draw(window);

  changeRemaingingMines();
  
  funcButtons["Remaining0"].draw(window);
  funcButtons["Remaining1"].draw(window);
  funcButtons["Remaining2"].draw(window);
}

void
Board::changeRemaingingMines()
{
  //Changes the "Remaining" button, shows the remaining mines on the board, Changes
  //when flags are added to screen
  int remainingMines = numOfMines - numOfFlags;
  int onesPlace = 0; 
  int tensPlace = 0; 
  int hundredsPlace = 0; 
  
  if (remainingMines >= 0)
  {
    onesPlace = remainingMines % 10;  
    tensPlace = ((remainingMines % 100 - onesPlace) / 10);
    hundredsPlace = ((remainingMines % 1000 - (tensPlace + onesPlace)) / 100);
    
    funcButtons["Remaining0"].splitDigitSprite(hundredsPlace);
    funcButtons["Remaining1"].splitDigitSprite(tensPlace);
    funcButtons["Remaining2"].splitDigitSprite(onesPlace);
  } else if (remainingMines < 0)
  {
    remainingMines = (remainingMines * (-1));
    onesPlace = remainingMines % 10;  
    tensPlace = ((remainingMines % 100 - onesPlace) / 10);
    
    funcButtons["Remaining0"].splitDigitSprite(10);
    funcButtons["Remaining1"].splitDigitSprite(tensPlace);
    funcButtons["Remaining2"].splitDigitSprite(onesPlace);
  }
}


Tile
Board::boardClick(sf::RenderWindow& window, bool Lclick)
{
  auto mousePos = sf::Mouse::getPosition(window);
  auto translatedPos = window.mapPixelToCoords(mousePos);

  // Functionality for the testing buttons
  sf::Sprite smiley = funcButtons["Smiley"].getSprite();
  sf::Sprite test_1 = funcButtons["Test1"].getSprite();
  sf::Sprite test_2 = funcButtons["Test2"].getSprite();
  sf::Sprite test_3 = funcButtons["Test3"].getSprite();
  sf::Sprite debug = funcButtons["Debug"].getSprite();

  // Clicking within the bounds of the gameboard
  for (int i = 0; i < gameboard.size(); i++) {
    sf::Sprite sprite = gameboard[i].getSprite();
    if (sprite.getGlobalBounds().contains(translatedPos)) {
      if (Lclick) {
        gameboard[i].leftClick();
      } else {
          if ((gameboard[i].getState() == Tile::State::FLAGGED))
            numOfFlags--;
          else
            numOfFlags++;
          gameboard[i].rightClick();
      }
      return (gameboard[i]);
    }
  }
  if (smiley.getGlobalBounds().contains(translatedPos)) {
    // std::cout << "Smiley was pressed" << std::endl;
    restartGame("random");
    // createBoardData("random");
  } else if (test_1.getGlobalBounds().contains(translatedPos)) {
    // std::cout << "Test 1 was pressed" << std::endl;
    restartGame("testboard1");
    // createBoardData("testboard1");
  } else if (test_2.getGlobalBounds().contains(translatedPos)) {
    // std::cout << "Test 2 was pressed" << std::endl;
    restartGame("testboard2");
    // createBoardData("testboard2");
  } else if (test_3.getGlobalBounds().contains(translatedPos)) {
    // std::cout << "Test 3 was pressed" << std::endl;
    restartGame("testboard3");
    // createBoardData("testboard3");
  } else if (debug.getGlobalBounds().contains(translatedPos)) {
    // std::cout << "Debug was pressed" << std::endl;
    displayMines();
  }

  return gameboard[0];
}

void
Board::displayMines()
{
  // Sets all the mines on the board to State::EXPLODED
  for (int i = 0; i < getGameBoard().size(); i++) {
    // if (gameboard[i].isMine())
    if (boardData[i] == 1)
      gameboard[i].setState(Tile::State::EXPLODED);
  }
}

void
Board::tileNeighborMines(std::vector<Tile>& board){
  //TODO fix function
  //Determines the number of surrounding Mines on a tile
  int neighborMines = 0;
  
  std::cout << "gameboard size: " << gameboard.size() << std::endl;
  int i = 0;
  for (int row=0; row < numOfRows; row++)
  {
    for (int col=0; col < numOfCols; col++)
    {
      //Possible of 8 total surrounding mines
      if ((i > 0) && (i < gameboard.size())){
        if ((boardData[i - 1] == 1) && (col != 0))                  //left
          std::cout << "left " << std::endl;
          // neighborMines++;
        if ((boardData[i + 1] == 1) && (col != numOfCols))          //right
          std::cout << "right " << std::endl;
          // neighborMines++;
        
        //check for first Row
        if (row != 0)
        {
          if ((boardData[i - numOfCols]) == 1)                      //above 
            std::cout << "above " << std::endl;
            // neighborMines++;
          // 
          //check for first Col
          if (col != 0)
          {
            if ((boardData[(i - numOfCols) - 1]) == 1)              //above left
          std::cout << "above left " << std::endl;
              // neighborMines++;
            if ((boardData[(i - numOfCols) + 1]) == 1)              //above right
          std::cout << "above right " << std::endl;
              // neighborMines++;
          }
        }
        
        //check for last row
        if (row != numOfRows)
        {
          if ((boardData[(i + numOfCols) + 1]) == 1)                //below right
            std::cout << "below right " << std::endl;
            // neighborMines++;
          //check for last col
          if (col != numOfCols)
          {
            if ((boardData[(i + numOfCols) - 1]) == 1)              //below left
              std::cout << "below left " << std::endl;
              // neighborMines++;
            if ((boardData[(i + numOfCols)]) == 1)                  //below
              std::cout << "below  " << std::endl;
              // neighborMines++;
          }
        }
      }
      else if (i == 0)     // Initial Tile
      {
        
        if ((boardData[i + 1]) == 1)                          
          neighborMines++;
        if ((boardData[(numOfCols + i)]) == 1)                 
          neighborMines++;
        if ((boardData[(numOfCols + i) + 1]) == 1)              
          neighborMines++;
      }
      else if (i == boardData.size())       //Final tile
        {
        if ((boardData[i - 1]) == 1)                             
          neighborMines++;
        if ((boardData[(i - numOfCols) - 1]) == 1)  
          neighborMines++;
        if ((boardData[i - numOfCols]) == 1)       
          neighborMines++;
        }
      
      // std::cout << "index: " << i << " neighbor mines " << neighborMines << std::endl;
      std::cout << "index: " << i << std::endl;
      gameboard[i].setAdjacentMines(neighborMines);
      i++;
      neighborMines = 0;
    }
  }
}

void
Board::restartGame(std::string boardType)
{
  // Resets all the tiles and reloads the board
  boardData.clear();
  createBoardData(boardType); // Loads in a fresh board
  for (int i = 0; i <= gameboard.size(); i++) {
    gameboard[i].setMine(boardData[i]); // Make the board blank
    gameboard[i].setState(Tile::State::HIDDEN);
    funcButtons["Smiley"].setSprite("face_happy");
    numOfFlags = 0;
  }
  displayBoardData();
}

//==============================Accessors==================================
int
Board::getCols()
{
  return numOfCols;
}

int
Board::getRows()
{
  return numOfRows;
}

std::vector<int>
Board::getBoardData()
{
  return boardData;
}

std::vector<Tile>
Board::getGameBoard()
{
  return gameboard;
}
