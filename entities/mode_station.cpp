#include "mode_station.h"
#include "../world/board.h"

// Constructor

ModeStation::ModeStation (Board* board, GameState* state) : 

    Structure (board, state, 3) 

{}

// Draw

void ModeStation::Draw () {

    int x = Board::GRID_LEFT;
    int y = Board::GRID_TOP + 21 - ((Board::CELL_COUNT - 1) * Board::CELL_SIZE) - Board::CELL_SIZE;
    
    float* WallColor = colors[GRAY];
    float* RoofColor = colors[DARK_GRAY];
    float* DoorColor = colors[BLACK];
    float* LineColor = colors[WHITE];
    float* ShadowColor = colors[SLATE_GRAY];

    int bodyWidth = 28;
    int bodyHeight = 22;
    int roofHeight = 6;
    int doorHeight = 16;
    int doorWidth = 18;

    int centerX = x + 1;
    int baseY = y;

    // Roof - triangle shape
    DrawLine(centerX, baseY + bodyHeight, centerX + bodyWidth / 2, baseY + bodyHeight + roofHeight, 2, RoofColor);
    DrawLine(centerX + bodyWidth, baseY + bodyHeight, centerX + bodyWidth / 2, baseY + bodyHeight + roofHeight, 2, RoofColor);
    DrawLine(centerX, baseY + bodyHeight, centerX + bodyWidth, baseY + bodyHeight, 2, RoofColor);

    // Main building
    DrawRectangle(centerX, baseY, bodyWidth, bodyHeight, WallColor);

    // Left and right vertical edges (shadows for slight 3D effect)
    DrawLine(centerX, baseY, centerX, baseY + bodyHeight, 1, ShadowColor);
    DrawLine(centerX + bodyWidth - 1, baseY, centerX + bodyWidth - 1, baseY + bodyHeight, 1, ShadowColor);

    // Garage Door (centered)
    int doorX = centerX + (bodyWidth - doorWidth) / 2;
    int doorY = baseY + 3;
    DrawRectangle(doorX, doorY, doorWidth, doorHeight, DoorColor);

    // Horizontal shutter lines
    for (int i = 1; i <= 3; i++) {
        DrawLine(doorX + 1, doorY + i * (doorHeight / 4), doorX + doorWidth - 1, doorY + i * (doorHeight / 4), 1, LineColor);
    }

    // Bottom platform
    DrawRectangle(centerX - 1, baseY, bodyWidth + 2, 3, colors[BLACK]);
    DrawRectangle(centerX + 1, baseY + 1, bodyWidth - 2, 1, colors[DARK_GRAY]);


}