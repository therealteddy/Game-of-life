#include "life.h"
#include "cells.h"

void RuleOfLife(int*** current_matrix, int*** next_matrix, unsigned int xpos, unsigned int ypos) {
    // Birth Rule 
    if (((*current_matrix)[ypos][xpos] == 0) && (GetLiveNeighbours((*current_matrix), MATRIX_W, MATRIX_W, (Vector2) {xpos, ypos}) == 3)) {
        (*next_matrix)[ypos][xpos] = 1;
    } 
    // Survival Rule 
    else if (((*current_matrix)[ypos][xpos] == 1) && (GetLiveNeighbours((*current_matrix), MATRIX_W, MATRIX_W, (Vector2) {xpos, ypos}) == 3 || GetLiveNeighbours((*current_matrix), MATRIX_W, MATRIX_W, (Vector2) {xpos, ypos}) == 2)) {
        (*next_matrix)[ypos][xpos] = 1; 
    }

    // Death Rule 
    else if (((*current_matrix)[ypos][xpos] == 1) && (GetLiveNeighbours((*current_matrix), MATRIX_W, MATRIX_W, (Vector2) {xpos, ypos}) > 3 || GetLiveNeighbours((*current_matrix), MATRIX_W, MATRIX_W, (Vector2) {xpos, ypos}) < 2)) {
        (*next_matrix)[ypos][xpos] = 0;
    }
}