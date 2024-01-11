#include "board.h"
#include "randomGen.h"
#include <SFML/Graphics.hpp>
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
  // displayBoardData();
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

  if (boardFile == "random") {
    // 1. Create from board attributes
    boardData.resize(boardSize);

    // Picks positions ar random and places mine
    int newNumOfMines = 0;
    for (int mines = 0; mines < (numOfMines); mines++) {
      int pos = RandomGen::intGenerator(
        0, (boardSize)); // Random number between 0 - size of board
      if (boardData[pos] == 0) {
        boardData[pos] = 1;
      } else {
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
    int newNumOfMines = 0;
    while (inputBoard.get(val)) {
      // Subtract by 48 to get the ASCII char to int
      if (val == '1') {
        boardData.push_back(((int)val - 48));
        newNumOfMines++;
      } else if (val == '0') {
        boardData.push_back(((int)val - 48));
      }
    }
    numOfMines = newNumOfMines;
  }
}

void
Board::buildGameBoard()
{
  // Creates the game Board of Tiles
  Tile tile;
  int i = 0;
  for (int row = 0; row < getRows(); row++) {
    for (int col = 0; col < getCols(); col++) {
      tile.setMine(boardData[i]);
      sf::IntRect spriteRect =
        (tile.getSprite()).getTextureRect(); // Gets the rectangle of the tile
      tile.setPos(sf::Vector2f(
        (float)(spriteRect.height * col),
        (float)(spriteRect.width * row))); // sets the position of the tile
                                           // based on the previous command
      tile.index = i;
      gameboard.push_back(tile);
      i++;
    }
  }

  setNeighborTiles();
  setAdjacentMines();

  // Sets each mines neighbors

  Tile Smiley("face_happy");
  Tile Test1("test_1");
  Tile Test2("test_2");
  Tile Test3("test_3");
  Tile Debug("debug");
  sf::IntRect spriteRect =
    (Smiley.getSprite())
      .getTextureRect(); // Gets the rectangle for the test buttons

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

  // {1 (mine) or 0 (not a mine)}
  std::cout << "BoardData" << std::endl;
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

  // std::cout << "BoardSize: " << boardSize << std::endl;
  // std::cout << "RevealedTiles: " << RevealedTiles << std::endl;
  // std::cout << "numOfMines: " << numOfMines << std::endl;
  // Check win condition
  if ((boardSize) == (RevealedTiles + (numOfMines))) {
    // Winner
    funcButtons["Smiley"].setSprite("face_win");
    gameover = true;
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
  // Changes the "Remaining" button, shows the remaining mines on the board,
  // Changes when flags are added to screen
  int remainingMines = numOfMines - numOfFlags;
  int onesPlace = 0;
  int tensPlace = 0;
  int hundredsPlace = 0;

  if (remainingMines >= 0) {
    onesPlace = remainingMines % 10;
    tensPlace = ((remainingMines % 100 - onesPlace) / 10);
    hundredsPlace = ((remainingMines % 1000 - (tensPlace + onesPlace)) / 100);

    funcButtons["Remaining0"].splitDigitSprite(hundredsPlace);
    funcButtons["Remaining1"].splitDigitSprite(tensPlace);
    funcButtons["Remaining2"].splitDigitSprite(onesPlace);
  } else if (remainingMines < 0) {
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
      if (gameover != true) {
        if (Lclick) {

          if (gameboard[i].isMine()) {
            // Game Over
            gameboard[i].setState(Tile::State::REVEALED);
            funcButtons["Smiley"].setSprite("face_lose");
            displayMines();
            gameover = true;
          } else {
            revealNeighborMines(i);
            gameboard[i].leftClick();
          }
        } else {
          if ((gameboard[i].getState() == Tile::State::FLAGGED))
            numOfFlags--;
          else
            numOfFlags++;
          gameboard[i].rightClick();
        }
      }
      // /*
      // Testing
      std::cout << "NumOfMines: " << numOfMines << std::endl;
      std::cout << "RevealedTiles: " << RevealedTiles << std::endl;
      std::cout << "BoardSize: " << boardSize << std::endl;
      std::cout << "AdjacentMines: " << gameboard[i].getAdjacentMines()
                << std::endl;
      // */

      return (gameboard[i]);
    }
  }
  if (smiley.getGlobalBounds().contains(translatedPos)) {
    setBoardConfig();
    restartGame("random");
  } else if (test_1.getGlobalBounds().contains(translatedPos)) {
    restartGame("testboard1");
  } else if (test_2.getGlobalBounds().contains(translatedPos)) {
    restartGame("testboard2");
  } else if (test_3.getGlobalBounds().contains(translatedPos)) {
    restartGame("testboard3");
  } else if (debug.getGlobalBounds().contains(translatedPos)) {
    displayMines();
  }

  return gameboard[0];
}

void
Board::displayMines()
{
  // Toggles Debug button
  // Sets all the mines on the board to State::EXPLODED
  for (int i = 0; i < getGameBoard().size(); i++) {
    if (gameboard[i].isMine() &&
        gameboard[i].getState() != Tile::State::EXPLODED)
      gameboard[i].setState(Tile::State::EXPLODED);
    else if (gameboard[i].isMine()) {
      gameboard[i].setState(Tile::State::HIDDEN);
    };
  }
}

// BUG revealed tiles tend to wrap around board
// Tiles affected Bottom row, right most column,
void
Board::setNeighborTiles()
{
  int i = 0;
  for (int row = 0; row < numOfRows; row++) {
    for (int col = 0; col < numOfCols; col++) {
      // first tile
      if (i != 0 && i != gameboard.size()) {
        if (row != 0 && col != 0)
          gameboard[i].adjacentTiles.push_back(
            &gameboard[(i - numOfCols) - 1]); // above left
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (row != 0)
          gameboard[i].adjacentTiles.push_back(
            &gameboard[i - numOfCols]); // above
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (row != 0 && col != (numOfCols - 1))
          gameboard[i].adjacentTiles.push_back(
            &gameboard[(i - numOfCols) + 1]); // above right
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (col != 0)
          gameboard[i].adjacentTiles.push_back(&gameboard[i - 1]); // left
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (col != numOfCols - 1)
          gameboard[i].adjacentTiles.push_back(&gameboard[i + 1]); // right
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (row != (numOfRows - 1) && col != 0)
          gameboard[i].adjacentTiles.push_back(
            &gameboard[(i + numOfCols) - 1]); // below left
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (row != (numOfRows - 1))
          gameboard[i].adjacentTiles.push_back(
            &gameboard[i + numOfCols]); // below
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

        if (row != (numOfRows - 1) && col != (numOfCols - 1))
          gameboard[i].adjacentTiles.push_back(
            &gameboard[(i + numOfCols) + 1]); // below right
        else
          gameboard[i].adjacentTiles.push_back(nullptr);

      } else if (i == 0) {
        gameboard[i].adjacentTiles.push_back(
          &gameboard[(i + numOfCols) + 1]); // below right
        gameboard[i].adjacentTiles.push_back(
          &gameboard[i + numOfCols]);                            // below
        gameboard[i].adjacentTiles.push_back(&gameboard[i + 1]); // right
      } else if (i == gameboard.size()) {
        gameboard[i].adjacentTiles.push_back(&gameboard[i - 1]); // left
        gameboard[i].adjacentTiles.push_back(
          &gameboard[(i - numOfCols) + 1]); // above right
        gameboard[i].adjacentTiles.push_back(
          &gameboard[i - numOfCols]); // above
      }
      i++;
    }
  }
}

void
Board::setAdjacentMines()
{
  for (int i = 0; i < gameboard.size(); i++) {
    for (int j = 0; j < gameboard[i].adjacentTiles.size(); j++) {
      if (gameboard[i].adjacentTiles[j] != nullptr) {
        if (gameboard[i].adjacentTiles[j]->isMine()) {
          gameboard[i].addAdjacentMines(1);
        }
      }
    }
  }
}

// BUG Adding an additional RevealedTiles (not sure why)
void
Board::revealNeighborMines(int index)
{
  // Base case when mines are nearby we exit recursion
  if (gameboard[index].getAdjacentMines() > 0) {
    return;
  } else {
    for (int i = 0; i < gameboard[index].adjacentTiles.size(); i++) {
      if (gameboard[index].adjacentTiles[i] != nullptr) {
        if ((gameboard[index].adjacentTiles[i]->isMine() == false) &&
            gameboard[index].adjacentTiles[i]->getState() !=
              (Tile::State::REVEALED)) {
          gameboard[index].adjacentTiles[i]->setState(Tile::State::REVEALED);
          RevealedTiles++;
          revealNeighborMines(gameboard[index].adjacentTiles[i]->index);
        }
      }
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
    gameboard[i].resetAdjacentMines();
    gameboard[i].setMine(boardData[i]); // Make the board blank
    gameboard[i].setState(Tile::State::HIDDEN);
    funcButtons["Smiley"].setSprite("face_happy");
    numOfFlags = 0;
    RevealedTiles = 0;
    gameover = false;
  }
  setAdjacentMines();
  // displayBoardData();    //Testing
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
