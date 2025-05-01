#include "board.h"

// Helpers

int Board::getCellValue (int row, int col) const { 

    if (row >= 0 && row < CELL_COUNT && col >= 0 && col < CELL_COUNT) {
    
        return grid [row][col];
    
    }

    return -1;

}

bool Board::isValidMove (int x, int y) const {
    
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    return getCellValue (row, col) != 1;

}

// Drawing the Board

void Board::ResetBoard () {

    for (int a = 0; a < CELL_COUNT; a++) {

        for (int b = 0; b < CELL_COUNT; b++) {

            grid [a][b] = 0;

        }

    }

    GenerateBuildings ();
    PlaceFuelStations ();
    PlaceModeStation ();
    PlacePassengers ();
    PlaceDeliveryPoints ();

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
    DrawFuelStations ();
    DrawModeStation ();
    DrawPassengersAndPackages ();
    
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

// Fuel Stations

void Board::PlaceFuelStations () {
    
    int stationsPlaced = 0;
    int maxStations = GetRandInRange (2, 3);

    // Check which cells are reachable from start
    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill (visited, 0, 0);
    
    while (stationsPlaced <= maxStations) {

        int row = GetRandInRange (0, CELL_COUNT);
        int col = GetRandInRange (0, CELL_COUNT);
        
        if (grid [row][col] == 0 && visited [row][col] && isValidRoad (row, col)) {
        
            grid [row][col] = 2;
            stationsPlaced++;
        
        }
    
    }

}

void Board::DrawFuelStations () {

    for (int row = 0; row < CELL_COUNT; row++) {

        for (int col = 0; col < CELL_COUNT; col++) {

            if (grid [row][col] == 2) {

                int x = GRID_LEFT + (col * CELL_SIZE);
                int y = GRID_TOP + 21 - (row * CELL_SIZE);

                DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [GREEN]);

            }

        }

    }

}

bool Board::isFuelStation (int x, int y) const {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;

    return getCellValue (row, col) == 2;

}

// Mode Station

void Board::PlaceModeStation () {

    grid [CELL_COUNT - 1][0] = 3;

}

void Board::DrawModeStation () {

    int x = GRID_LEFT;
    int y = GRID_TOP + 21 - ((CELL_COUNT - 1) * CELL_SIZE);
    
    DrawSquare (x, y - CELL_SIZE, CELL_SIZE, colors [GRAY]);

}

bool Board::isModeStation (int x, int y) const {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    return getCellValue (row, col) == 3;

}

// Passengers and Packages

void Board::PlacePassengers() {

    int placed = 0;
    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill (visited, 0, 0);
    
    int MaxPassengers = GetRandInRange (2, 4);

    while (placed <= MaxPassengers) {

        int row = GetRandInRange (0, CELL_COUNT);
        int col = GetRandInRange (0, CELL_COUNT);
        
        if (grid [row][col] == 0 && visited [row][col]) {
            
            grid [row][col] = 4; 
            
            // Place destination
            bool destPlaced = false;
            while(!destPlaced) {
                int destRow = GetRandInRange(0, CELL_COUNT);
                int destCol = GetRandInRange(0, CELL_COUNT);
                
                if(grid[destRow][destCol] == 0 && visited[destRow][destCol]) {
                    grid[destRow][destCol] = 5; // Destination
                    destPlaced = true;

                }

            }

            placed++;

        }

    }

}

void Board::PlaceDeliveryPoints() {
    int placed = 0;
    bool visited[CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill(visited, 0, 0);

    int MaxPackages = GetRandInRange (2, 4);
    
    while(placed <= MaxPackages) {
        // Place package
        int row = GetRandInRange(0, CELL_COUNT);
        int col = GetRandInRange(0, CELL_COUNT);
        
        if(grid[row][col] == 0 && visited[row][col]) {
            grid[row][col] = 6; // Package
            
            // Place destination
            bool destPlaced = false;
            while(!destPlaced) {
                int destRow = GetRandInRange(0, CELL_COUNT);
                int destCol = GetRandInRange(0, CELL_COUNT);
                
                if(grid[destRow][destCol] == 0 && visited[destRow][destCol]) {
                    grid[destRow][destCol] = 7; // Destination
                    destPlaced = true;
                }
            }
            placed++;
        }
    }
}

void Board::DrawPassengersAndPackages() {

    int size = CELL_SIZE;

    for(int row = 0; row < CELL_COUNT; row++) {
        for(int col = 0; col < CELL_COUNT; col++) {
            int x = GRID_LEFT + (col * CELL_SIZE);
            int y = GRID_TOP + 21 - (row * CELL_SIZE);
            
            switch(grid[row][col]) {
                case 4: // Passenger
                DrawTriangle(
                    x + size/2, y - 5,           // Top point
                    x + 5, y - (size - 5),       // Bottom left
                    x + size - 5, y - (size - 5),// Bottom right
                    colors[YELLOW]
                );
                    break;
                case 5: // Passenger destination
                    DrawSquare(x, y - CELL_SIZE, CELL_SIZE, colors[ORANGE]);
                    break;
                case 6: // Package
                DrawRoundRect(
                    x + 5, y - size + 5,     // Position
                    size - 10, size - 10,     // Size (slightly smaller than cell)
                    colors[PURPLE],
                    5                         // Radius
                );
                    break;
                case 7: // Package destination
                    DrawSquare(x, y - CELL_SIZE, CELL_SIZE, colors[PINK]);
                    break;
            }
        }
    }
}

bool Board::isPassenger(int x, int y) const {
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    return getCellValue(row, col) == 4;
}

bool Board::isPassengerDestination(int x, int y) const {
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    return getCellValue(row, col) == 5;
}

bool Board::isPackage(int x, int y) const {
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    return getCellValue(row, col) == 6;
}

bool Board::isPackageDestination(int x, int y) const {
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    return getCellValue(row, col) == 7;
}

void Board::removePassenger(int x, int y) {
    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    if(grid[row][col] == 4) {
        grid[row][col] = 0;
    }
}

void Board::removePackage (int x, int y) {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    if (grid [row][col] == 6) {
        grid [row][col] = 0;
    }

}