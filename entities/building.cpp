#include "building.h"
#include "../world/board.h"

// Constructor

Building::Building (Board* board, GameState* state) : 

    Structure (board, state, 1) 

{}

// Draw

void Building::Draw () {

    for (int row = 0; row < Board::CELL_COUNT; row++) {

        for (int col = 0; col < Board::CELL_COUNT; col++) {

            if (gameBoard -> getCellValue (row, col) == 1) {

                int x = Board::GRID_LEFT + (col * Board::CELL_SIZE);
                int y = Board::GRID_TOP + 21 - (row * Board::CELL_SIZE);

                DrawSquare (x, y - Board::CELL_SIZE, Board::CELL_SIZE, colors [BLACK]);

            }

        }

    }

}