#include "package.h"
#include "../world/board.h"

// Constructor

Package::Package (Board* board, GameState* state) : 

    Transportable (board, state, 6) 

{}

// Draw

void Package::Draw () {

    for (int row = 0; row < Board::CELL_COUNT; row++) {

        for (int col = 0; col < Board::CELL_COUNT; col++) {

            if (gameBoard -> getCellValue (row, col) == 6) {

                int x = Board::GRID_LEFT + (col * Board::CELL_SIZE);
                int y = Board::GRID_TOP + 21 - (row * Board::CELL_SIZE) - Board::CELL_SIZE;

                DrawPackage (x, y);

            }

        }

    }

}

void Package::DrawPackage(int x, int y) {

    float* BoxColor = colors[ORANGE];
    float* TapeColor = colors[YELLOW];
    float* EdgeColor = colors[BROWN];
    float* ShadowColor = colors[GRAY];
    float* LabelColor = colors[WHITE];
    float* BarcodeColor = colors[BLACK];

    int width = 20;
    int height = 16;

    x += 5;
    y += 5;

    // Main box face
    DrawRectangle(x, y, width, height, BoxColor);

    // Vertical tape strip down the middle
    DrawRectangle(x + width / 2 - 2, y, 4, height, TapeColor);

    // Tape edge hanging slightly over top front (adds realism)
    DrawRectangle(x + width / 2 - 2, y - 2, 4, 2, TapeColor);

    // Diagonal corner tape (optional aesthetic)
    DrawLine(x + 2, y + 2, x + 7, y + 7, 2, TapeColor);

    // Label base
    DrawRectangle(x + width - 7, y + height - 6, 6, 4, LabelColor);

    // Barcode on label
    DrawLine(x + width - 6, y + height - 5, x + width - 6, y + height - 2, 1, BarcodeColor);
    DrawLine(x + width - 4, y + height - 5, x + width - 4, y + height - 2, 1, BarcodeColor);
    DrawLine(x + width - 3, y + height - 5, x + width - 3, y + height - 2, 1, BarcodeColor);

    // Box edges
    DrawLine(x, y, x + width, y, 1, EdgeColor);                      // Top
    DrawLine(x, y + height, x + width, y + height, 1, EdgeColor);   // Bottom
    DrawLine(x, y, x, y + height, 1, EdgeColor);                    // Left
    DrawLine(x + width, y, x + width, y + height, 1, EdgeColor);    // Right

    // Optional bottom shadow
    DrawRectangle(x + 2, y + height + 1, width - 4, 2, ShadowColor);
}

