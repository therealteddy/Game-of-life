/* 
   Author: Ted Jerin 
   Description: The Zero player Game of life in c
   Date: 12-Dec-23 
*/

#include <raylib.h>
#include <stdio.h>

#include "cells.h"
#include "life.h"


int main(int argc, char* argv[]) {
    /* Define a 2D array of cells */
    unsigned int** current_matrix; 
    unsigned int** next_matrix; 
    GetCellArray(&current_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);
    GetCellArray(&next_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);

    // Set up a blinker 
    current_matrix[0][1] = 1; 
    current_matrix[1][1] = 1; 
    current_matrix[2][1] = 1; 

    // Window Pre-requisites
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_T);
    SetTargetFPS(1);

    // Application loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid
        DrawCellGrid(0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H, BLACK);
        
        PrintCellArray(current_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H); 
        for (int j = 0; j < MATRIX_H; ++j) {
            for (int i = 0; i < MATRIX_W; ++i) {
                RuleOfLife(&current_matrix, &next_matrix, i, j); 
            }
        }
        current_matrix = next_matrix;
        GetCellArray(&next_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);

        EndDrawing(); 
    }
    CloseWindow();
    return 0; 
}