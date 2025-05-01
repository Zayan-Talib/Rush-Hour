#include "board.h"

// Drawing the Board

void Board::DrawGrid () {

    float * gridColor = colors [BLACK];

    int cx, cy, nx, ny, lwidth, cellsize;

    // Variable Values

    cx = (1020 - BOARD_WIDTH) / 2;
    cy = 770; // Coords start from bottom

    lwidth = 10;
    cellsize = CELL_SIZE;

    // Drawing the Grid

    // Horizontal Lines

    nx = BOARD_WIDTH;
    ny = cy;

    for (int a = 1; a <= 25; a++) {

        DrawLine (cx, ny, cx + nx, ny, lwidth, gridColor);

        ny -= cellsize;

    }

    // Vertical Lines

    nx = cx;
    ny = 24 * cellsize;

    for (int a = 1; a <= 25; a++) {

        DrawLine (nx, cy, nx, cy - ny, lwidth, gridColor);

        nx += cellsize;

    }   
    
}

void Board::DrawBuildings () {

    

}