#pragma once
#include <SFML/Graphics.hpp>
#include "toolbox.hpp"

//Global Functions

//Invoked directly by main and is responsible for launching the game
int launch();

//Resets all states/objects and generates a default game and turns of debug mode
//The new game state should be default (25x16 with 50 randomly placed mines)
void restart();

//Draws the UI elements according to the current gameState and debug mode
void render();

//Flips debug mode on and off
void toggleDebugMode();

//Returns true if debug mode is active 
bool getDebugMode();
