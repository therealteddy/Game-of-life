/* 
   Author: Ted Jerin 
   Description: The Zero player Game of life in c
   Date: 12-Dec-23 
*/

#include <raylib.h>
#include <stdio.h>

#include "cells.h"

#define WINDOW_H 1000 
#define WINDOW_W 1000 
#define WINDOW_T "Game Of Life"
#define FPS_CAP 60

int main(int argc, char* argv[]) {
    unsigned int** matrix; 
    GetCellArray(&matrix, 100, 100, WINDOW_W, WINDOW_H);
    PrintCellArray(matrix, 100, 100, WINDOW_W, WINDOW_H);

    InitWindow(WINDOW_W, WINDOW_H, WINDOW_T);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCellGrid(0, 0, WINDOW_W, WINDOW_H, 10, 10, BLACK);
        EndDrawing(); 
    }
    return 0; 
}