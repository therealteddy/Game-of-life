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
    unsigned int** matrix; 
    GetCellArray(&matrix, 100, 100, WINDOW_W, WINDOW_H);
    PrintCellArray(matrix, 100, 100, WINDOW_W, WINDOW_H);

    // The number of allowed rectangles should be equal to the number of cells
    unsigned int AllCells, CellCounter; 
    AllCells = (WINDOW_W/CELL_W) * (WINDOW_H/CELL_H); 
    CellCounter = 0;
    Vector2 T_CellPosition = {0, 0};
    Rectangle Cell[AllCells]; 

    InitWindow(WINDOW_W, WINDOW_H, WINDOW_T);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            T_CellPosition = GetCellPosition(GetMousePosition().x, GetMousePosition().y, 0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H);
            Cell[CellCounter].x = T_CellPosition.x;
            Cell[CellCounter++].y = T_CellPosition.y;
        }
        for (int i = 0; i < CellCounter; ++i) {
            DrawRectangle(Cell[i].x, Cell[i].y, CELL_W, CELL_H, RED);
        }
        DrawCellGrid(0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H, BLACK);
        EndDrawing(); 
    }
    CloseWindow();
    return 0; 
}