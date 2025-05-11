#include "passenger.h"
#include "../world/board.h"

// Constructor

Passenger::Passenger (Board* board, GameState* state) : 

    Transportable (board, state, 4) 

{}

// Draw

void Passenger::Draw () {

    for (int row = 0; row < Board::CELL_COUNT; row++) {

        for (int col = 0; col < Board::CELL_COUNT; col++) {

            if (gameBoard -> getCellValue (row, col) == 4) {

                int x = Board::GRID_LEFT + (col * Board::CELL_SIZE);
                int y = Board::GRID_TOP + 21 - (row * Board::CELL_SIZE);

                DrawPassenger (x, y);

            }

        }

    }

}

void Passenger::DrawPassenger (int x, int y) {

    // Head
    DrawCircle(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE / 4 - 2, Board::CELL_SIZE / 6, colors[BLACK]);

    // Body
    DrawLine(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE / 4, x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE * 0.6, 4, colors[BLACK]);

    // Arms (angled downward slightly instead of flat)
        
    y -= 1;

    DrawLine(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE * 0.4, x + Board::CELL_SIZE / 4, y - Board::CELL_SIZE * 0.5, 3, colors[BLACK]);  // Left arm
    DrawLine(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE * 0.4, x + Board::CELL_SIZE * 0.75, y - Board::CELL_SIZE * 0.5, 3, colors[BLACK]); // Right arm

    y += 1;

    // Legs (symmetrical and diagonal to suggest standing or walking in place)
    DrawLine(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE * 0.6, x + Board::CELL_SIZE / 3, y - Board::CELL_SIZE * 0.9, 4, colors[BLACK]);   // Left leg
    DrawLine(x + Board::CELL_SIZE / 2, y - Board::CELL_SIZE * 0.6, x + Board::CELL_SIZE * 0.67, y - Board::CELL_SIZE * 0.9, 4, colors[BLACK]); // Right leg   

}