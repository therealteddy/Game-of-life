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