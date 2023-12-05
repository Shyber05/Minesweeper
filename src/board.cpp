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
        // (float)(spriteRect.height * col),
        // (float)(spriteRect.width * row))); // sets the position of the tile
                                           // based on the previous command
        (spriteRect.height * col),
        (spriteRect.width * row))); // sets the position of the tile
      gameboard.push_back(tile);
      i++;
      
    }
  }

  // TODO fix test buttons
  //  Creates the game buttons     Doesn't WORK (-_-)
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
  testButtons.emplace("Smiley", Smiley);
  testButtons.emplace("Test1", Test1);
  testButtons.emplace("Test2", Test2);
  testButtons.emplace("Test3", Test3);
  testButtons.emplace("Debug", Debug);
  testButtons.emplace("Remaining0", Digit0);
  testButtons.emplace("Remaining1", Digit1);
  testButtons.emplace("Remaining2", Digit2);
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
  testButtons["Smiley"].draw(window);
  testButtons["Test1"].draw(window);
  testButtons["Test2"].draw(window);
  testButtons["Test3"].draw(window);
  testButtons["Debug"].draw(window);
  testButtons["Remaining0"].draw(window);
  testButtons["Remaining1"].draw(window);
  testButtons["Remaining2"].draw(window);
}

Tile
Board::boardClick(sf::RenderWindow& window, bool Lclick)
{
  auto mousePos = sf::Mouse::getPosition(window);
  auto translatedPos = window.mapPixelToCoords(mousePos);

  // Functionality for the testing buttons
  sf::Sprite smiley = testButtons["Smiley"].getSprite();
  sf::Sprite test_1 = testButtons["Test1"].getSprite();
  sf::Sprite test_2 = testButtons["Test2"].getSprite();
  sf::Sprite test_3 = testButtons["Test3"].getSprite();
  sf::Sprite debug = testButtons["Debug"].getSprite();

  // Clicking within the bounds of the gameboard
  for (int i = 0; i < gameboard.size(); i++) {
    sf::Sprite sprite = gameboard[i].getSprite();
    if (sprite.getGlobalBounds().contains(translatedPos)) {
      if (Lclick) {
        gameboard[i].leftClick();
      } else {
        gameboard[i].rightClick();
        numOfFlags++;
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
    if (gameboard[i].isMine())
      gameboard[i].setState(Tile::State::EXPLODED);
  }
}

void
Board::restartGame(std::string boardType)
{
  // Resets all the tiles and reloads the board

  // resets all the data in the board
  // for (int i = 0; i < boardData.size(); i++) {
  //   boardData[i] = 0;
  // }
  boardData.clear();

  createBoardData(boardType); // Loads in a fresh config (random nums);
  for (int i = 0; i <= gameboard.size(); i++) {
    gameboard[i].setMine(boardData[i]); // Make the board blank
    gameboard[i].setState(Tile::State::HIDDEN);
    testButtons["Smiley"].setSprite("face_happy");
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
