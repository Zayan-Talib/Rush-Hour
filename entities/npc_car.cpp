#include "npc_car.h"
#include "../world/board.h"

// Static member initialization

float NPCCar::GlobalSpeed = 1.0f;

// Constructor

NPCCar::NPCCar (Board* board, GameState* state) : 

    Actor (board, state, START_SPEED), 
    isBlocked (false),
    targetCellX (0), 
    targetCellY (0), 
    direction (0)  

{}

// Drawing

void NPCCar::Draw () {

    int x = gameBoard -> getLeft () + (cellX * gameBoard -> getCellSize ()) + 5;
    int y = gameBoard -> getTop () - (cellY * gameBoard -> getCellSize ()) - 4;
    
    DrawSquare (x, y, 20, colors [MAGENTA]);

    int wheelSize = 3;

    DrawCircle (x + 5, y, wheelSize, colors [BLACK]);      // Left wheel
    DrawCircle (x + 15, y, wheelSize, colors [BLACK]);     // Right wheel

    // Direction Indicator - Centered in the square
    
    int arrowSize = 10;
    int centerX = x + 10;  // Center of the 20x20 square
    int centerY = y + 10;  // Center of the 20x20 square
    
    switch (direction) {
        
        case 0: // Up

            DrawTriangle (centerX, centerY + arrowSize, centerX - arrowSize / 2, centerY, centerX + arrowSize / 2, centerY, colors [BLACK]);
            break;
        
        case 1: // Right
        
            DrawTriangle (centerX + arrowSize, centerY, centerX, centerY - arrowSize / 2, centerX, centerY + arrowSize / 2, colors [BLACK]);
            break;
        
        case 2: // Down
        
            DrawTriangle (centerX, centerY - arrowSize, centerX - arrowSize / 2, centerY, centerX + arrowSize / 2, centerY, colors [BLACK]);
            break;
      
        case 3: // Left
        
            DrawTriangle (centerX - arrowSize, centerY, centerX, centerY - arrowSize / 2, centerX, centerY + arrowSize / 2, colors [BLACK]);
            break;
    
    }

}

// Movement

bool NPCCar::canMoveTo (int newCellX, int newCellY) {

    if (newCellY < 0 || newCellY >= Board::CELL_COUNT || newCellX < 0 || newCellX >= Board::CELL_COUNT) {
        return false;
    }
    
    return gameBoard -> getCellValue (newCellY, newCellX) == 0;
}

void NPCCar::Move (int dx, int dy) {

    int newCellX = cellX;
    int newCellY = cellY;
    
    switch (direction) {

        case 0: newCellY--; break; // Up
        case 1: newCellX++; break; // Right  
        case 2: newCellY++; break; // Down
        case 3: newCellX--; break; // Left
    
    }
    
    if (!canMoveTo (newCellX, newCellY)) {
        
        direction = GetRandInRange (0, 4);
        return;
    
    }
    

    cellY = newCellY;
    cellX = newCellX;

}