#include "board.h"

// Drawing the Board

void Board::ClearBoard () {

    for (int a = 0; a < CELL_COUNT; a++) {

        for (int b = 0; b < CELL_COUNT; b++) {

            grid [a][b] = 0;

        }

    }

}

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
    
    DrawBuildings ();
    
}

void Board::DrawBuildings () {

    for (int row = 0; row < CELL_COUNT; row++) {

        for (int col = 0; col < CELL_COUNT; col++) {

            if (grid [row][col] == 1) {

                int x = GRID_LEFT + (col * CELL_SIZE);
                int y = GRID_TOP + 21 - (row * CELL_SIZE);

                DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [BLACK]);

            }

        }

    }

}

// Building Generation Logic

void Board::GenerateBuildings () {
    
    InitRandomizer ();
    
    int totalCells = CELL_COUNT * CELL_COUNT;
    int buildingCells = (totalCells * BUILDING_PERCENT) / 100;
    
    grid [0][0] = 0;                            // Top-left
    grid [0][CELL_COUNT - 1] = 0;               // Top-right
    grid [CELL_COUNT - 1][0] = 0;               // Bottom-left
    grid [CELL_COUNT - 1][CELL_COUNT - 1] = 0;  // Bottom-right
    
    // Place buildings randomly

    int placedBuildings = 0;
    
    while (placedBuildings < buildingCells) {

        int row = GetRandInRange (0, CELL_COUNT);
        int col = GetRandInRange (0, CELL_COUNT);
        
        if (grid [row][col] == 0 && isValidRoad (row, col)) {
            
            grid [row][col] = 1;
            
            placedBuildings++;
            
            // Verify if corners are still reachable and undo if they aren't
            
            if (!canReachAllCorners ()) {

                grid [row][col] = 0;
                placedBuildings--;

            }

        }

    }

}

bool Board::isValidRoad (int row, int col) {
    
    // Check if placing a building here would block all paths - Ensure at least one adjacent cell is a road

    bool hasAdjacentRoad = false;
    
    if (row > 0 && grid [row - 1][col] == 0) { 
        hasAdjacentRoad = true; 
    }
    
    if (row < CELL_COUNT - 1 && grid [row + 1][col] == 0) {
        hasAdjacentRoad = true;
    }
    
    if (col > 0 && grid [row][col - 1] == 0) {
        hasAdjacentRoad = true;
    }
    
    if (col < CELL_COUNT - 1 && grid [row][col + 1] == 0) {
        hasAdjacentRoad = true;
    }
        
    return hasAdjacentRoad;
}

bool Board::canReachAllCorners () {
    
    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    
    // Start from top left
    
    if (grid [0][0] == 0) {

        floodFill (visited, 0, 0);

    } 
    
    else {

        return false;

    }
    
    // Corners Check

    return visited [0][0] && visited [0][CELL_COUNT - 1] && visited [CELL_COUNT - 1][0] && visited [CELL_COUNT - 1][CELL_COUNT - 1];

}

void Board::floodFill (bool visited [][24], int row, int col) {

    // Base cases - out of bounds or already visited or is a building

    if (row < 0 || row >= CELL_COUNT || col < 0 || col >= CELL_COUNT || 
    
        visited [row][col] || grid [row][col] != 0) {
        return;
    
    }
    
    // Mark current cell as visited

    visited [row][col] = true;
    
    floodFill (visited, row + 1, col); // Down
    floodFill (visited, row - 1, col); // Up
    floodFill (visited, row, col + 1); // Right
    floodFill (visited, row, col - 1); // Left

}