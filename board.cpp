#include "board.h"

// Helpers

int Board::getCellValue (int row, int col) const { 

    if (row >= 0 && row < CELL_COUNT && col >= 0 && col < CELL_COUNT) {
    
        return grid [row][col];
    
    }

    return -1;

}

bool Board::GridCheck (int x, int y, int check) const {

    int row, col;

    row = (GRID_TOP - y) / CELL_SIZE;
    col = (x - GRID_LEFT) / CELL_SIZE;

    return getCellValue (row, col) == check;

}

bool Board::isValidMove (int x, int y) const {
    
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    return getCellValue (row, col) != 1;

}

void Board::PlaceItem (int itemType, int minCount, int maxCount, bool needDestination) {

    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill (visited, 0, 0);

    int placed = 0;
    int maxItems = GetRandInRange (minCount, maxCount);

    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;
    
    while (placed <= maxItems && attempts < MAX_ATTEMPTS) {

        attempts++;

        int row = GetRandInRange (0, CELL_COUNT);
        int col = GetRandInRange (0, CELL_COUNT);
        
        if (grid [row][col] == 0 && visited [row][col]) {
            
            grid [row][col] = itemType;
            placed++;
        
        }
    
    }

}

void Board::GenerateDestination (int itemType) {

    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill (visited, 0, 0);
    
    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;

    bool destPlaced = false;

    while (!destPlaced && attempts < MAX_ATTEMPTS) {

        attempts++;

        int destRow = GetRandInRange (0, CELL_COUNT);
        int destCol = GetRandInRange (0, CELL_COUNT);
        
        if (grid [destRow][destCol] == 0 && visited [destRow][destCol]) {
        
            grid [destRow][destCol] = itemType + 1;  // Destination type
            destPlaced = true;
        
        }

    }

}

// Drawing the Board

void Board::ResetBoard () {

    for (int a = 0; a < CELL_COUNT; a++) {

        for (int b = 0; b < CELL_COUNT; b++) {

            grid [a][b] = 0;

        }

    }

    GenerateBuildings ();
    PlaceModeStation ();
    PlaceFuelStations ();
    PlacePassengers ();
    PlaceDeliveryPoints ();

}

void Board::DrawBoard (int currentMode) {

    DrawGrid ();
    DrawModeStation ();
    DrawBuildings ();
    DrawFuelStations ();
    DrawPassengersAndPackages (currentMode);

}

void Board::DrawGrid () {

    float * gridColor = colors [BLACK];
    int cx, cy, nx, ny, lwidth, cellsize;

    // Variable Values

    cx = (1020 - BOARD_WIDTH) / 2;
    cy = 770; // Coords start from bottom

    lwidth = 10;
    cellsize = CELL_SIZE;

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

void Board::DrawModeStation () {

    int x = GRID_LEFT;
    int y = GRID_TOP + 21 - ((CELL_COUNT - 1) * CELL_SIZE);
    
    DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [GRAY]);

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

void Board::DrawFuelStations () {

    for (int row = 0; row < CELL_COUNT; row++) {

        for (int col = 0; col < CELL_COUNT; col++) {

            if (grid [row][col] == 2) {

                int x = GRID_LEFT + (col * CELL_SIZE);
                int y = GRID_TOP + 21 - (row * CELL_SIZE);

                DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [RED]);

            }

        }

    }

}

void Board::DrawPassengersAndPackages (int currentMode) {
    
    int size = CELL_SIZE;

    for (int row = 0; row < CELL_COUNT; row++) {
        
        for (int col = 0; col < CELL_COUNT; col++) {
            
            int x = GRID_LEFT + (col * CELL_SIZE);
            int y = GRID_TOP + 21 - (row * CELL_SIZE);
            
            if (currentMode == 0) {

                if (grid [row][col] == 4) { 

                    DrawTriangle (x + size / 2, y - 5, x + 5, y - (size - 5), x + size - 5, y - (size - 5), colors [YELLOW]);
                                
                }

                else if (grid [row][col] == 5) {
                
                    DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [ORANGE]);
                
                }

            }

            if (currentMode == 1) {
                    
                if (grid [row][col] == 6) { 

                    DrawRoundRect (x + 5, y - size + 5, size - 10, size - 10, colors [BROWN], 5);                                
                
                }

                else if (grid [row][col] == 7) {
                
                    DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [PURPLE]);
                
                }
            
            }

        }

    }

}

// Buildings

void Board::GenerateBuildings () {
    
    int totalCells = CELL_COUNT * CELL_COUNT;
    int buildingCells = (totalCells * BUILDING_PERCENT) / 100;
    
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

bool Board::canReachAllCorners () {
    
    if (grid [0][0] != 0) { return false; }

    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    
    // Start from top left

    floodFill (visited, 0, 0);
    
    // Corners Check

    return visited [0][0] && visited [0][CELL_COUNT - 1] && visited [CELL_COUNT - 1][0] && visited [CELL_COUNT - 1][CELL_COUNT - 1];

}

void Board::floodFill (bool visited [][24], int row, int col) {

    // Base cases - out of bounds or already visited or is a building

    if (row < 0 || row >= CELL_COUNT || col < 0 || col >= CELL_COUNT || visited [row][col] || grid [row][col] != 0) {
        
        return;
    
    }
    
    // Mark current cell as visited

    visited [row][col] = true;
    
    floodFill (visited, row + 1, col); // Down
    floodFill (visited, row - 1, col); // Up
    floodFill (visited, row, col + 1); // Right
    floodFill (visited, row, col - 1); // Left

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

// Passengers and Packages

void Board::removePassenger (int x, int y) {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;

    if (grid [row][col] == 4) {
    
        grid [row][col] = 0;
        GenerateDestination (4);
    
    }

}

void Board::removePackage (int x, int y) {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    if (grid [row][col] == 6) {
    
        grid [row][col] = 0;
        GenerateDestination (6);
    
    }

}

void Board::removePassengerDestination (int x, int y) {
    
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    if (grid [row][col] == 5) {

        grid [row][col] = 0;

    }

}

void Board::removePackageDestination (int x, int y) {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    if (grid [row][col] == 7) {

        grid [row][col] = 0;

    }

}