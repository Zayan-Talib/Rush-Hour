#include "board.h"

void Board::DrawGrid () {

    DrawRectangle (StartX, StartY, BOARD_WIDTH, BOARD_HEIGHT, colors [BLACK]);
    
}