#include "board.h"

// Constructor

Board::Board () : numNPCCars (0) {
            
    InitRandomizer ();

    grid = new int * [CELL_COUNT];
    
    for (int a = 0; a < CELL_COUNT; a++) {
    
        grid [a] = new int [CELL_COUNT];
    
    }

    fuelstation = new FuelStation (this, nullptr);
    modestation = new ModeStation (this, nullptr);
    building = new Building (this, nullptr);

    ResetBoard ();

}

// Destructor

Board::~Board () {

    delete fuelstation;
    delete modestation;
    delete building;

    for (int a = 0; a < numNPCCars; a++) {

        delete npcCars[a];

    }

    for (int a = 0; a < CELL_COUNT; a++) {

        delete [] grid [a];

    }

    delete [] grid;

}

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

void Board::PlaceItem (int itemType, int minCount, int maxCount) {

    bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
    floodFill (visited, 0, 0);

    int placed = 0;
    int maxItems = (minCount == maxCount) ? minCount : GetRandInRange (minCount, maxCount + 1);

    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;
    
    while (placed < maxItems && attempts < MAX_ATTEMPTS) {

        attempts++;

        int row = GetRandInRange (0, CELL_COUNT);
        int col = GetRandInRange (0, CELL_COUNT);
        
        if (grid [row][col] == 0 && !(row == 0 && col == 0) && visited [row][col]) {
            
            grid [row][col] = itemType;
            placed++;
        
        }
    
    }

}

void Board::GenerateDestination (int itemType) {

    PlaceItem (itemType + 1, 1, 1);

}

// Drawing the Board

void Board::ResetBoard () {

    for (int a = 0; a < CELL_COUNT; a++) {

        for (int b = 0; b < CELL_COUNT; b++) {

            grid [a][b] = 0;

        }

    }

    // Reset NPC cars
    numNPCCars = 0;
    resetNPCSpeed ();

    GenerateBuildings ();
    PlaceModeStation ();
    PlaceFuelStations ();
    PlacePassengers ();
    PlaceDeliveryPoints ();

    for (int a = 0; a < INITIAL_NPC_CARS; a++) {
            
        addNPCCar ();
    
    }

}

void Board::DrawBoard (int currentMode) {

    DrawGrid ();

    building -> Draw ();
    modestation -> Draw ();
    fuelstation -> Draw ();

    DrawPassengersAndPackages (currentMode);
    DrawNPCCars ();

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

void Board::DrawPassengersAndPackages (int currentMode) {
    
    int size = CELL_SIZE;

    for (int row = 0; row < CELL_COUNT; row++) {
        
        for (int col = 0; col < CELL_COUNT; col++) {
            
            int x = GRID_LEFT + (col * CELL_SIZE);
            int y = GRID_TOP + 21 - (row * CELL_SIZE);
            
            if (currentMode == 0) {

                if (grid [row][col] == 4) { 

                    //  DrawTriangle (x + size / 2, y - 5, x + 5, y - (size - 5), x + size - 5, y - (size - 5), colors [YELLOW]);
                           
                    // Draw stick figure

                    // Head
                    DrawCircle (x + size / 2, y - size / 4 - 2, size / 6, colors[BLACK]);
                    
                    // Body
                    DrawLine (x + size / 2, (y - size / 2) + 2, x + size / 2, (y - size * 0.8), 5, colors [BLACK]);
                    
                    // Arms
                    DrawLine (x + size / 3, y - size * 0.65 + 2, x + size * 0.67, y - size * 0.65 + 2, 5, colors [BLACK]);
                    
                    // Legs
                    DrawLine (x + size / 2, y - size * 0.8, x + size / 3, y - size * 0.95 + 2, 5, colors [BLACK]);
                    DrawLine (x + size / 2, y - size * 0.8, x + size * 0.67, y - size * 0.95 + 2, 5, colors [BLACK]);
                        
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
        ReplenishItems (0);

    }

}

void Board::removePackageDestination (int x, int y) {

    int row = (GRID_TOP - y) / CELL_SIZE;
    int col = (x - GRID_LEFT) / CELL_SIZE;
    
    if (grid [row][col] == 7) {

        grid [row][col] = 0;
        ReplenishItems (1);

    }

}

// Replenishing

int Board::countPassengers () const {

    int count = 0;

    for (int row = 0; row < CELL_COUNT; row++) {
        
        for (int col = 0; col < CELL_COUNT; col++) {
            
            if (grid [row][col] == 4) {
            
                count++;
            
            }
        
        }
    
    }
    
    return count;

}

int Board::countPackages () const {
    
    int count = 0;
    
    for (int row = 0; row < CELL_COUNT; row++) {
        
        for (int col = 0; col < CELL_COUNT; col++) {
        
            if (grid [row][col] == 6) {
        
                count++;
        
            }
        
        }
    
    }
    
    return count;

}

void Board::ReplenishItems (int currentMode) {

    if (currentMode == 0) {
        
        int passengerCount = countPassengers ();
        
        if (passengerCount < MIN_PASSENGERS) {
    
            PlaceItem (4, 1, 1);
    
        }
    
    }

    else {
        
        int packageCount = countPackages ();
        
        if (packageCount < MIN_PACKAGES) {
        
            PlaceItem (6, 1, 1);

        }

    }

}

void Board::trySpawnNewItem (int currentMode) {

    // First check current count
    int currentCount = (currentMode == 0) ? countPassengers () : countPackages ();
    int maxAllowed = (currentMode == 0) ? MAX_PASSENGERS : MAX_PACKAGES;
    
    // Don't spawn if already at or above max
    if (currentCount >= maxAllowed) {
        return;
    }

    // Generate random number 1-100
    int chance = GetRandInRange (1, 100);
    
    if (chance <= SPAWN_CHANCE) {

        PlaceItem ((currentMode == 0) ? 4 : 6, 1, 1);

    }

}

bool Board::tryRefuel (PlayerCar* car) {

    if (car -> getMoney () >= 20 && isFuelStation (car -> getX (), car -> getY ())) {

        car -> addMoney (-FUEL_COST);
        car -> refillFuel ();
        return true;

    }

    return false;

}

// NPC Cars

void Board::increaseNPCSpeed (float mult) {

    for (int a = 0; a < numNPCCars; a++) {

        npcCars [a] -> setSpeed (npcCars [a] -> getSpeed () * mult);

    }

    NPCCar::setGlobalSpeed (NPCCar::getGlobalSpeed () * mult);

}

void Board::resetNPCSpeed () {

    for (int a = 0; a < numNPCCars; a++) {

        npcCars [a] -> setSpeed (1.0f);

    }

    NPCCar::setGlobalSpeed (1.0f);

}

void Board::stepNPCCars () {

    for (int a = 0; a < numNPCCars; a++) {

        if (npcCars [a] -> isActive ()) {

            // Clear old position
            
            grid [npcCars [a] -> getCellY ()][npcCars [a] -> getCellX ()] = 0;

            // Move car
            
            npcCars [a] -> Move ();
            
            // Set new position
            
            grid [npcCars [a] -> getCellY ()][npcCars [a] -> getCellX ()] = NPC_CAR_TYPE;

        }

    }

}

void Board::addNPCCar () {
        
        bool visited [CELL_COUNT][CELL_COUNT] = {{false}};
        
        floodFill (visited, 0, 0);
        
        int attempts = 0;

        while (attempts < 1000) {
            
            int row = GetRandInRange (0, CELL_COUNT);
            int col = GetRandInRange (0, CELL_COUNT);
             
            if (grid [row][col] == 0 && visited [row][col]) {

                npcCars [numNPCCars] = new NPCCar (this, nullptr);
                npcCars [numNPCCars] -> setCellY (row);
                npcCars [numNPCCars] -> setCellX (col);
                npcCars [numNPCCars] -> setDirection (GetRandInRange (0, 4));
                npcCars [numNPCCars] -> setActive (true);
                
                grid [row][col] = NPC_CAR_TYPE;
                numNPCCars++;
                
                break;
            
            }
            
            attempts++;
        
    }

}

void Board::DrawNPCCars () {

    for (int a = 0; a < numNPCCars; a++) {
    
        if (npcCars [a] != nullptr) {
        
            npcCars [a] -> Draw ();
        
        }

    }

}
