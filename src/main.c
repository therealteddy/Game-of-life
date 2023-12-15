/* 
   Author: Ted Jerin 
   Description: The Zero player Game of life in c
   Date: 12-Dec-23 
*/

#include <raylib.h>
#include <stdio.h>

#include "cells.h"
#include "life.h"

#define FPS_CAP 10

int main(int argc, char* argv[]) {
    /* Count the generation */ 
    unsigned int GenerationCounter = 0; 

    /* Define a 2D array of cells */
    unsigned int** current_matrix; 
    unsigned int** next_matrix; 
    GetCellArray(&current_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);
    GetCellArray(&next_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);

    // Set up a glider 
    current_matrix[0][0] = 1;

    current_matrix[1][1] = 1; 
    current_matrix[1][2] = 1;

    current_matrix[2][0] = 1;
    current_matrix[2][1] = 1;

    // Set up a blinker
    current_matrix[0][MATRIX_W-2] = 1; 
    current_matrix[1][MATRIX_W-2] = 1;
    current_matrix[2][MATRIX_W-2] = 1;

    // Set up a toad 
    current_matrix[MATRIX_H-3][0] = 1; 
    current_matrix[MATRIX_H-3][1] = 1;
    current_matrix[MATRIX_H-3][2] = 1;

    current_matrix[MATRIX_H-2][1] = 1; 
    current_matrix[MATRIX_H-2][2] = 1;
    current_matrix[MATRIX_H-2][3] = 1;

    // Window Pre-requisites
    InitWindow(WINDOW_W, WINDOW_H, WINDOW_T);
    SetTargetFPS(FPS_CAP);

    // Application loop
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        /* Draw the current generation number */
        DrawText(TextFormat("Generation = %u\n", GenerationCounter++), 0, 0, 25, BLACK);

        // Draw grid
        DrawCellGrid(0, 0, WINDOW_W, WINDOW_H, CELL_W, CELL_H, BLACK);
        
        // Print the current generation - disable if the grid is large!
        //PrintCellArray(current_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H); 

        // Draw the current cells
        for (int j = 0; j < MATRIX_H; ++j) {
            for (int i = 0; i < MATRIX_W; ++i) {
                if (current_matrix[j][i])
                    DrawRectangle(i*CELL_W, j*CELL_H, CELL_W, CELL_H, RED);
            }
        }      
        
        
        // update the cell matrix
        for (int j = 0; j < MATRIX_H; ++j) {
            for (int i = 0; i < MATRIX_W; ++i) {
                RuleOfLife(&current_matrix, &next_matrix, i, j); 
            }
        }
        
        // Get ready for the next generation  
        DeleteCellArray(&current_matrix); 
        current_matrix = next_matrix;
        GetCellArray(&next_matrix, CELL_W, CELL_H, WINDOW_W, WINDOW_H);

        EndDrawing(); 
    }
    CloseWindow();
    return 0; 
}