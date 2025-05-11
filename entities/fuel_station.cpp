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
                int y = Board::GRID_TOP + 21 - (row * Board::CELL_SIZE) - Board::CELL_SIZE;

                DrawStation (x, y);

            }

        }

    }

}

void FuelStation::DrawStation (int x, int y) {

    float* BlackColor = colors [BLACK];
    float* GreenColor = colors [GREEN];
    float* LightGreenColor = colors [LIME_GREEN];
    float* WhiteColor = colors [WHITE];
    
    int width = 20;
    int height = 30;
    
    DrawRectangle (x + 5, y, width, height, BlackColor);
    
    DrawRectangle (x + 8, y + height - 13, width - 6, 10, LightGreenColor);  // Top green area
    DrawRectangle (x + 8, y + height - 23, width - 6, 10, GreenColor);       // Bottom green area
    
    // Screen/display area (black rectangle within the top green area)
    
    DrawRectangle (x + 11, y + height - 11, width - 12, 6, BlackColor);
    
    // White area within the screen (small white rectangle)
    
    DrawRectangle (x + 13, y + height - 9, 4, 2, WhiteColor);
    
    // Gray base/platform at the bottom
    
    DrawRectangle (x, y, Board::CELL_SIZE, 5, BlackColor);
    DrawRectangle (x + 2, y + 1, Board::CELL_SIZE - 4, 3, colors [DARK_GRAY]);

    
}