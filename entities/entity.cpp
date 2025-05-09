#include "entity.h"

Entity::Entity (Board* board, GameState* state, int startCellX, int startCellY) : 
    
    gameBoard (board), 
    gameState (state),
    cellX (startCellX), 
    cellY (startCellY) {}
