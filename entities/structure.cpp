#include "structure.h"
 
Structure::Structure (Board* board, int startCellX, int startCellY, int type) :
    Entity (board, startCellX, startCellY),
    type (type) {} 