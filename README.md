## Minesweeper

This version of Minesweeper was written in C++ with the [SFML](https://www.sfml-dev.org/) library.
This project was formally one of the projects in my Computer Science program at the University of Florida.


<img src="./design/pic.png" 
    alt="Minesweeper" 
    style="display: block; 
           margin-left: auto;
           margin-right: auto;
           width: 50%;"
/>
<h3 style="text-align:center;"> Description</h3>

__Rules Overview__  
The rules of the game are as follows:  
There exists a board, which contains a grid of spaces. A space could be a mine, or not. The player clicks
on a space, and it gets revealed. The goal of the game is to reveal all the spaces that are not mines, while
avoiding the spaces that are.  
  
When a space is revealed:  
  
If it’s a mine, the game ends  

If it’s not a mine, it shows the number of mines adjacent to that space (anywhere from 0 to 8, with 0 just
showing as an empty space)  

- If a space has no adjacent mines, all non-mine spaces adjacent to it are also revealed The
player uses the numbers as clues to figure out where other mines may be located.
When all of the non-mine spaces have been revealed, the player wins!
---

<h3 style="text-align:center;"> Features</h3>

_Flags_: Right-clicking a hidden space puts a flag on that space, marking it as a possible mine. Flagged
spaces cannot be revealed (with left-clicks or as a result of adjacent spaces being revealed), but another
right-click will remove the flag.  

_Mine Counter_: To track the number of mines that are on the board. Every time the player places a flag,
the counter goes down by one. Every time they remove a flag, the counter goes up by one. The mine
counter can also go negative. 

_Restart Button_: The smiley face centered at the top or bottom of the window lets you restart a new
board with everything reset and mines randomized.

---
<h3 style="text-align:center;">Non-standard features for your version of this project</h3>
_Debug Button_: Clicking this button will toggle the visibility of the mines on the board. Use this to help
test/debug various features of the game. It reveals all the mines on the board.

_Test Buttons #1-3:_ Clicking on these loads a file with a specific board
layout. Mainly used in testing to make sure certain board configs acted appropriate.

---

### Build instructions
 
I used [CMake](https://cmake.org/) for the build process so the steps to create the executable are as follows 
Start in the base directory

    mkdir build
    cd build
    cmake ..
    make
    cd ..
    ./minesweeper


This puts all the Cmake build files in the _build_ directory and the executable in the base directory.


