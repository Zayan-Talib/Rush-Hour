#include "fuel_station.h"
#include "../world/board.h"

// Constructor

FuelStation::FuelStation (Board* board, GameState* state) : 

    Structure (board, state, 2) 

{}

// Draw

void FuelStation::Draw () {

    for (int row = 0; row < Board::CELL_COUNT; row++) {

        for (int col = 0; col < Board::CELL_COUNT; col++) {

            if (gameBoard -> getCellValue (row, col) == 2) {

                int x = Board::GRID_LEFT + (col * Board::CELL_SIZE);
                int y = Board::GRID_TOP + 21 - (row * Board::CELL_SIZE);

                DrawSquare (x, y - Board::CELL_SIZE, Board::CELL_SIZE, colors [RED]);

            }

        }

    }

}