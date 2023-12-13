/* 
   Author: Ted Jerin 
   Description: The Zero player Game of life in c
   Date: 12-Dec-23 
*/

#include <raylib.h>
#include <stdio.h>

#include "cells.h"

#define WINDOW_H 900 
#define WINDOW_W 900 
#define WINDOW_T "Game Of Life"
#define FPS_CAP 60

int main(int argc, char* argv[]) {
    /* Define a 2D array of cells */
    unsigned int** matrix; 
    GetCellArray(&matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);
    PrintCellArray(matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);

    // The number of allowed rectangles should be equal to the number of cells
    unsigned int AllCells, CellCounter; 
    AllCells = (WINDOW_W/CELL_W) * (WINDOW_H/CELL_H); 
    CellCounter = 0;
    Vector2 T_CellPosition = {0, 0};
    Rectangle Cell[AllCells]; 

    // Window Pre-requisites
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_T);
    
    // Application loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Approximate cell position and update matrix
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CellCounter <= AllCells) {
            T_CellPosition = GetCellPosition(GetMousePosition().x, GetMousePosition().y, 0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H);
            matrix[((int) T_CellPosition.y)/CELL_H] [((int) T_CellPosition.x)/CELL_H] = 1;
            Cell[CellCounter].x = T_CellPosition.x;
            Cell[CellCounter++].y = T_CellPosition.y;
            PrintCellArray(matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);
        }

        // Draw all the rectangles in the predefined position
        for (int i = 0; i < CellCounter; ++i) {
            DrawRectangle(Cell[i].x, Cell[i].y, CELL_W, CELL_H, RED);
        }

        // Draw grid
        DrawCellGrid(0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H, BLACK);
        EndDrawing(); 
    }

    printf("Live neighbours = %d\n", GetLiveNeighbours(matrix, (Vector2) {1, 1}));
    CloseWindow();
    return 0; 
}