#include "destination.h"
#include "../world/board.h"

// Constructor

Destination::Destination (Board* board, GameState* state) : 

    Structure (board, state, 5) 

{}

// Draw

void Destination::DrawDestination (int currentMode) {

    float * MainColor = nullptr;

    if (currentMode == 0) {
        MainColor = colors [GREEN];
    }
    else if (currentMode == 1) {
        MainColor = colors [DARK_BLUE];
    }

    for (int row = 0; row < Board::CELL_COUNT; row++) {

        for (int col = 0; col < Board::CELL_COUNT; col++) {

            int x = Board::GRID_LEFT + (col * Board::CELL_SIZE);
            int y = (Board::GRID_TOP + 21 - (row * Board::CELL_SIZE)) - Board::CELL_SIZE;

            if (gameBoard -> getCellValue (row, col) == 5 || gameBoard -> getCellValue (row, col) == 7) {

                DrawSquare (x, y, Board::CELL_SIZE, MainColor); 

                DrawSquare (x + 10, y + 10, 5, colors[BLACK]);
                DrawSquare (x + 5, y + 15, 5, colors[BLACK]);
    
                DrawSquare (x + 5, y + 5, 20, colors[WHITE]);
                DrawSquare (x + 10, y + 10, 10, colors[BLACK]);     

            }

        }

    }

}

void Destination::Draw () {}