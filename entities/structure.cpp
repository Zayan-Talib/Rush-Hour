#include "structure.h"

// Constructor

Structure::Structure (Board* board, GameState* state, int type = 0) :
    
    Entity (board, state),
    type (type) 
    
{} 