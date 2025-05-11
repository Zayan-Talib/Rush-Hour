#include "transportable.h"

// Constructor

Transportable::Transportable (Board* board, GameState* state, int type = 0) :
    
    Entity (board, state),
    type (type) 
    
{} 