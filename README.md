# Conway's Game of Life

Conway's Game of Life consists of a virtual environment where "cells" (represented by coloured dots in the screen) are born and cease to live, following the evolution of these individuals across "generations" (iterations or cycles of the system). The game, designed by John Horton Conway in 1970, follows three simple rules:

```
• Birth: Given that a dead cell has exactly three living cells surrounding it, it is born. What this means is that it will be alive in the next cycle.

• Death: There are two cases in which a living cell can die:
  
  o Overpopulation: if it has more than three neighboring cells.
  
  o Isolation: If it has one or zero neighboring cells.
  
• Survival: A cell stays alive when the amount of neighboring cells is equal to two or three.
```

## How to play

The game can be accesed by running the main .exe file or by typing "cmd" in the folder's path and pressing the "enter" key.
For the board to be initialized, it is required that the number of rows and columns and a pre-defined or custom pattern are entered via command line.

The order in which the arguments must be typed in is as follows:

```
rows columns pattern delay(in ms) cycles
```

Rows = A number bigger or equal to 18.

Columns = A number bigger or equal to 38.

Pattern = A name corresponding to a pre-defined pattern or to one made by the player. Typing in "custom" allows for the user to initialize the board however they please. Space separated names must be introduced between a set of " ".

Delay = A number that represents the amount of miliseconds it takes for the screen to refresh and show each game cycle.

Cycles = A number indicating how many "generations" of cells (game cycles) will be displayed.  

### Patterns

Patterns provide a way of initialazing the board without the need of creating a pattern from scratch. Each time the player starts a customized initialization of the board, they're given the option of saving the state of the matrix in order to use it again.

The game includes a few example patterns:

* Glider gun (glidergun, glider-gun or "glider gun")
 
![Gosperglidergun](https://github.com/user-attachments/assets/16604476-77cc-4fdd-b2d8-ba9895a5db5f)

* Random

  Entering this pattern fills the matrix with libing cells at random positions, making each run unique.
  

## Implementation

The program is based on the C programming language, aidded by the SDL2 library in order to display graphics.
The board that represents the space where the cells are contained is an NxM unsigned integer matrix, set to contain merely 0s by default. During every evolutive cycle, an intermediate state is defined for each cell by counting the amount of living cells in its eiight nearest positions and updating the unsigned integer number asociated to that particular specimen (2=DYING,3=ABOUT TO BE BORN). Following this, which is needed for the correct updating of the system when the algorithm receives the previous state of the matrix, the board is traversed again, this time changing the intermediate states of each cell to a definitive one (0=DEAD,1=ALIVE) for the SDL2 functions to work with.

The matrix has two extra rows and columns that exist solely to dispose of the preocupation of running into unauthorized memory positions while the algorithm checks those cells located in the corners and borders of the board. The content of these set auxiliary positions are permanently set to 0 (dead cells), and by never being updated, it does not interfere with calculations.

## Closure 

This project was built for the Information Technologies Engineering course dictated at Universdad Nacional de La Matanza. As such, it was made possible by the hands of Lautaro Agustín Barreto, Bentancur Suárez Ismael, Franco Caccavari and Luciano Damian Falconi. Credits to Pablo Soligo for the implementation of the SDL2 library in a portable fashion.

