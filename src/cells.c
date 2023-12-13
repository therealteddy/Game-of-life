#include "cells.h"

void GetCellArray(unsigned int*** Matrix, unsigned int cw, unsigned int ch, unsigned int ww, unsigned int wh) {
    *Matrix = malloc((wh/ch) * sizeof(unsigned int*)); 
    for (int i = 0; i < (wh/ch); *(*Matrix+(i++)) = calloc((ww/cw), sizeof(unsigned int)));
} 

void PrintCellArray(unsigned int** Matrix, unsigned int cw, unsigned int ch, unsigned int ww, unsigned int wh) {
    unsigned int j, i; 
    for(i = 0; i++ < 6; printf(" "));
    for(i = 0; i < (ww/cw); printf("[%d]", i++));
    printf("\n");
    for (j = 0; j < (wh/ch); ++j) {
        printf("[%d] [  ", j); 
        for (i = 0; i < (ww/cw); printf("%d  ", Matrix[j][i++]));
        printf("]\n");
    } 
}

void DrawCellGrid(int XPos, int YPos, unsigned int WindowWidth, unsigned int WindowHeight, unsigned int CellWidth, unsigned int CellHeight, Color COLOR) {
    for (int i = XPos; i <= XPos+WindowWidth; i+=CellWidth) {
        DrawLine(i, YPos, i, YPos+WindowHeight, COLOR);
    }
    for (int i = YPos; i <= YPos+WindowHeight; i+=CellHeight) {
        DrawLine(XPos, i, XPos+WindowWidth, i, COLOR);
    }
}

Vector2 GetCellPosition(int MousePosX, int MousePosY, int GridPosX, int GridPosY, unsigned int WindowWidth, unsigned int WindowHeight, unsigned int CellWidth, unsigned int CellHeight) {
    double OffsetX = MousePosX - GridPosX; 
    double OffsetY = MousePosY - GridPosY; 
    int CellPosX = (((int)(OffsetX/CellWidth))*CellWidth)+GridPosX; 
    int CellPosY = (((int)(OffsetY/CellHeight))*CellHeight)+GridPosY;
    return (Vector2) {CellPosX, CellPosY}; 
}

unsigned int GetLiveNeighbours(int** matrix, Vector2 index) {
    unsigned int counter = 0; 

    // Row below (3 neighbours)
    counter += (matrix[((int)index.y)-1][((int)index.x)-1]);
    counter += (matrix[((int)index.y)-1][((int)index.x)+0]);
    counter += (matrix[((int)index.y)-1][((int)index.x)+1]);

    // Current row (only 2 neighbours) 
    counter += (matrix[((int)index.y)+0][((int)index.x)-1]);
    counter += (matrix[((int)index.y)+0][((int)index.x)+1]);

    // Row Above (3 neighbours)
    counter += (matrix[((int)index.y)+1][((int)index.x)-1]);
    counter += (matrix[((int)index.y)+1][((int)index.x)+0]);
    counter += (matrix[((int)index.y)+1][((int)index.x)+1]);

    return counter;    
}