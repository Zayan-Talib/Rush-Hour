#include "mode_station.h"
#include "../world/board.h"

// Constructor

ModeStation::ModeStation (Board* board, GameState* state) : 

    Structure (board, state, 3) 

{}

// Draw

void ModeStation::Draw () {

    int x = Board::GRID_LEFT;
    int y = Board::GRID_TOP + 21 - ((Board::CELL_COUNT - 1) * Board::CELL_SIZE);
    
    DrawSquare (x, y - Board::CELL_SIZE, Board::CELL_SIZE, colors [GRAY]);

}