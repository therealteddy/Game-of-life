#ifndef CELLS_H
#define CELLS_H

#include <stdlib.h>
#include <raylib.h>
#include <stdio.h> 
#include <math.h> 

#define CELL_H 250
#define CELL_W 250 

/* Get a 2D array of 1 and 0 for the number of cells within the window */
void GetCellArray(unsigned int*** Matrix, unsigned int CellWidth, unsigned int CellHeight, unsigned int WindowWidth, unsigned int WindowHeight);

/* Print a 2D array of cells */
void PrintCellArray(unsigned int** Matrix, unsigned int CellWidth, unsigned int CellHeight, unsigned int WindowWidth, unsigned int WindowHeight);

/*  Draw a grid of cells */ 
void DrawCellGrid(int XPos, int YPos, unsigned int WindowWidth, unsigned int WindowHeight, unsigned int CellWidth, unsigned int CellHeight, Color COLOR); 
#endif //CELLS_H