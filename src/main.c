/* 
   Author: Ted Jerin 
   Description: The Zero player Game of life in c
   Date: 12-Dec-23 
*/
#include <stdlib.h> 

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#include <raylib-nuklear.h>

#include <raylib.h>
#include <stdio.h>

#include "cells.h"
#include "life.h"

#define FPS_CAP 10

int main(int argc, char* argv[]) {
    /* Colors */ 
    struct nk_colorf CellColor = ColorToNuklearF(WHITE);  
    struct nk_colorf BaseColor = ColorToNuklearF(GRAY); 

    /* Settings Variables */
    enum Options {DISABLE, ENABLE};
    bool PrintMatrix = DISABLE; // Default to No
    bool UpdateMatrix = DISABLE; // Default to No 

    /* Nuklear structures */ 
    struct nk_context* ctx; 
    
    ctx = InitNuklear(20); 

    /* Count the generation */ 
    unsigned int GenerationCounter = 0; 

    /* Define a 2D array of cells */
    unsigned int** current_matrix; 
    unsigned int** next_matrix; 
    Vector2 cell_position; 
    GetCellArray(&current_matrix, CELL_W, CELL_H, GRID_W, GRID_H);
    GetCellArray(&next_matrix, CELL_W, CELL_H, GRID_W, GRID_H);

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
        /* Update Nuklear */ 
        UpdateNuklear(ctx); 

        // Draw GUI 
        // Control Panel (1st)
        if (nk_begin(ctx, "Control Panel", nk_rect(GRID_W, 0, WINDOW_W-GRID_H, 100), NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR )) {
            // Print Matrix? 
            nk_layout_row_dynamic(ctx, 20, 1); 
            nk_label(ctx, "Print Grid (Slow)", NK_TEXT_ALIGN_CENTERED);
            
            // Buttons for enabling/disabling
            nk_layout_row_dynamic(ctx, 40, 2); 
            if (nk_option_label(ctx, "Enable", PrintMatrix == ENABLE)) PrintMatrix = ENABLE; 
            if (nk_option_label(ctx, "Disable", PrintMatrix == DISABLE)) PrintMatrix = DISABLE; 
        }
        nk_end(ctx);
        // Color Picker Panel (2nd) 
        if (nk_begin(ctx, "Color Picker", nk_rect(GRID_W, 100, WINDOW_W-GRID_W, 650), NK_WINDOW_TITLE | NK_WINDOW_BORDER )) {
            // Color Picker for cells
            nk_layout_row_static(ctx, 250, 300, 1); 
            CellColor = nk_color_picker(ctx, CellColor, NK_RGBA);
            nk_layout_row_static(ctx, 50, 300, 1); 
            nk_label(ctx, "Cell Color", NK_TEXT_ALIGN_CENTERED);

            // Color Picker for grid
            nk_layout_row_static(ctx, 250, 300, 1); 
            BaseColor = nk_color_picker(ctx, BaseColor, NK_RGBA);
            nk_layout_row_static(ctx, 50, 300, 1); 
            nk_label(ctx, "Grid Color", NK_TEXT_ALIGN_CENTERED);
        }
        nk_end(ctx);
        // Simulation State Panel (3rd)
        if (nk_begin(ctx, "Simulation State", nk_rect(GRID_W, 750, WINDOW_W-GRID_H, 100), NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
            // Start and Stop Simulation? 
            nk_layout_row_static(ctx, 40, 130, 2); 
            if (nk_button_label(ctx, "Run! ")) UpdateMatrix = ENABLE; 
            if (nk_button_label(ctx, "Stop!")) UpdateMatrix = DISABLE; 
        }
        nk_end(ctx); 
        // Help Panel 
        if (nk_begin(ctx, "Help!", nk_rect(GRID_W, 850, WINDOW_W-GRID_W, 150), NK_WINDOW_BORDER | NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR)) {
            // About Button 
            nk_layout_row_static(ctx, 40, 300, 1); 
            if (nk_button_label(ctx, "About")) {
                #ifdef _WIN32 
                    // Windows
                    system("start https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life");
                #elif __LINUX__ 
                    // Linux
                    system("xdg-open https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life");
                #elif __APPLE__ 
                    // MacOS
                    system("open https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life");
                #else 
                    // BSD, ReactOS etc. 
                    #error "Unsupported Platform: Documentation is found under `docs/`
                #endif
            }
            // Usage Panel 
            nk_layout_row_static(ctx, 40, 300, 1); 
            if (nk_button_label(ctx, "Usage")) {
                #ifdef _WIN32
                    // Windows (Fix this and add documentation!)
                    system("start ../docs/documentation.html");
                #elif __LINUX__
                    // Linux 
                    system("xdg-open ../docs/documentation.html"); 
                #elif  __APPLE__
                    // MacOS 
                    system("open ../docs/documentation.html");
                #else 
                    // BSD, ReactOS etc. 
                    #error "Unsupported Platform: Documentation is found under `docs/`
                #endif
            }

        }
        nk_end(ctx);

        BeginDrawing();
        ClearBackground(ColorFromNuklearF(BaseColor));

        /* Draw the current generation number */
        DrawText(TextFormat("Generation = %u\n", GenerationCounter), CELL_W/2, CELL_H/2, 25, BLACK);

        // Draw grid
        DrawCellGrid(0, 0, GRID_W, GRID_H, CELL_W, CELL_H, BLACK);

        // Draw the current cells
        for (int j = 0; j < MATRIX_H; ++j) {
            for (int i = 0; i < MATRIX_W; ++i) {
                if (current_matrix[j][i])
                    DrawRectangle(i*CELL_W, j*CELL_H, CELL_W, CELL_H, ColorFromNuklearF(CellColor));
            }
        }      
        
        // Run the simulation 
        if (UpdateMatrix) {
            // Print the current generation - disable if the grid is large!
            if(PrintMatrix) 
                PrintCellArray(current_matrix, CELL_W, CELL_H, GRID_W, GRID_H); 
            
            // update the cell matrix
            for (int j = 0; j < MATRIX_H; ++j) {
                for (int i = 0; i < MATRIX_W; ++i) {
                    RuleOfLife(&current_matrix, &next_matrix, i, j); 
                }
            }
        
            // Get ready for the next generation  
            DeleteCellArray(&current_matrix); 
            current_matrix = next_matrix;
            GetCellArray(&next_matrix, CELL_W, CELL_H, GRID_W, GRID_H);

            // Update the Generation counter 
            GenerationCounter++;
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                cell_position = GetCellPosition(GetMousePosition().x, GetMousePosition().y, 0, 0, CELL_W, CELL_H); 
                if ((cell_position.x/CELL_W >= 0 && cell_position.x/CELL_W < MATRIX_W) && (cell_position.y/CELL_H >= 0 && cell_position.y/CELL_H < MATRIX_H)) {
                    current_matrix[((int)cell_position.y)/CELL_H][((int)cell_position.x)/CELL_W] = !current_matrix[((int)cell_position.y)/CELL_H][((int)cell_position.x)/CELL_W]; 
                }
        }
        

        // Draw Nuklear 
        DrawNuklear(ctx); 
        EndDrawing(); 
    }

    UnloadNuklear(ctx);
    CloseWindow();
    return 0; 
}