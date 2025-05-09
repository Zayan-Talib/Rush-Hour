#include "npc_car.h"
#include "../world/board.h"
#include "../utility/util.h"

NPCCar::NPCCar(Board* board, GameState* state, int startCellX, int startCellY, float aiSpeed) :
    Actor(board, state, aiSpeed, startCellX, startCellY),
    aiSpeed(aiSpeed),
    isBlocked(false),
    targetCellX(startCellX),
    targetCellY(startCellY),
    movementDelay(1000 / aiSpeed),  // Convert speed to delay
    lastMoveTime(0) {
    // NPCs start with full fuel and in taxi mode
    fullFuel();
    setMode(MODE_TAXI);
}

void NPCCar::Draw() {
    // Store current color
    float* currentColor = colors[BLUE];
    
    // Draw the NPC car
    float* wheelColor = colors[BLACK];
    
    // Convert cell coordinates to pixel coordinates
    int pixelX = gameBoard->getLeft() + (cellX * 30);
    int pixelY = gameBoard->getTop() - (cellY * 30);
    
    DrawSquare(pixelX, pixelY, 20, currentColor);
    
    int wheelSize = 5;
    DrawCircle(pixelX + 5, pixelY, wheelSize, wheelColor);
    DrawCircle(pixelX + 15, pixelY, wheelSize, wheelColor);
    
    glutPostRedisplay();
}

void NPCCar::Move(int dX, int dY) {
    // Only move if enough time has passed (based on AI speed)
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime - lastMoveTime < movementDelay) {
        return;
    }
    
    // Call base class move
    Actor::Move(dX, dY);
    
    // Update last move time
    lastMoveTime = currentTime;
}

bool NPCCar::canMoveTo(int newCellX, int newCellY) {
    return Actor::canMoveTo(newCellX, newCellY) && !isBlocked;
}

void NPCCar::updateAI() {
    // If we're at the target or blocked, find a new target
    if (isAtTarget() || isBlocked) {
        findNewTarget();
        return;
    }
    
    // Calculate direction to target
    int dx = 0, dy = 0;
    
    if (cellX < targetCellX) dx = 1;
    else if (cellX > targetCellX) dx = -1;
    else if (cellY < targetCellY) dy = 1;
    else if (cellY > targetCellY) dy = -1;
    
    // Try to move towards target
    Move(dx * 30, dy * 30);  // Convert cell movement to pixel movement
}

void NPCCar::setTarget(int cellX, int cellY) {
    targetCellX = cellX;
    targetCellY = cellY;
}

bool NPCCar::isAtTarget() const {
    return cellX == targetCellX && cellY == targetCellY;
}

void NPCCar::findNewTarget() {
    // Simple random target selection
    // In a real implementation, this would be more sophisticated
    int boardWidth = 24;  // Assuming standard board size
    int boardHeight = 24;
    
    targetCellX = rand() % boardWidth;
    targetCellY = rand() % boardHeight;
    
    // Reset blocked status when finding new target
    isBlocked = false;
} 