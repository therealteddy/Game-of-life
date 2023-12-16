#ifndef CELLS_H
#define CELLS_H

#include <stdlib.h>
#include <raylib.h>
#include <stdio.h> 
#include <math.h> 

#define CELL_H 50
#define CELL_W 50

#define GRID_W 1000 
#define GRID_H 1000

#define WINDOW_W 1300 
#define WINDOW_H 1000
#define WINDOW_T "Game Of Life"

#define MATRIX_W GRID_W/CELL_W
#define MATRIX_H GRID_H/CELL_H
#define MATRIX_A MATRIX_W*MATRIX_H

/* Get a 2D array of 1 and 0 for the number of cells within the Grid */
void GetCellArray(unsigned int*** Matrix, unsigned int CellWidth, unsigned int CellHeight, unsigned int GridWidth, unsigned int GridHeight);

/* Print a 2D array of cells */
void PrintCellArray(unsigned int** Matrix, unsigned int CellWidth, unsigned int CellHeight, unsigned int GridWidth, unsigned int GridHeight);

/* Free all the pointers within a cell array and then free the pointer of pointer itself */
void DeleteCellArray(unsigned int*** Matrix);

/*  Draw a grid of cells */ 
void DrawCellGrid(int XPos, int YPos, unsigned int GridWidth, unsigned int GridHeight, unsigned int CellWidth, unsigned int CellHeight, Color COLOR); 

/* Approximate the position of a cell from mouse posittion */ 
Vector2 GetCellPosition(int MousePosX, int MousePosY, int GridPosX, int GridPosY, unsigned int CellWidth, unsigned int CellHeight); 

/* Get the number of live neighbours surrounding a cell */
unsigned int GetLiveNeighbours(int** matrix, unsigned int MatrixWidth, unsigned int MatrixHeight, Vector2 index); 

#endif //CELLS_H