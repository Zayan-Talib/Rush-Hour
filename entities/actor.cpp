#include "actor.h"

Actor::Actor (Board* board, GameState* state, float speed, int startCellX, int startCellY) :
    
    Entity (board, state, startCellX, startCellY),
    speed (speed),
    active (true) {} 