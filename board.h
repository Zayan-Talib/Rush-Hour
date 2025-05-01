#ifndef BOARD_H_
#define BOARD_H_

#include "util.h"

class Board {

    private:

        static const int CELL_SIZE = 30;
        static const int CELL_COUNT = 24; // 24 cells in each row and column

        static const int BOARD_WIDTH = CELL_SIZE * CELL_COUNT;
        static const int BOARD_HEIGHT = CELL_SIZE * CELL_COUNT;

        static const int GRID_LEFT = 150;
        static const int GRID_RIGHT = GRID_LEFT + BOARD_WIDTH;
        static const int GRID_TOP = 750;
        static const int GRID_BOTTOM = GRID_TOP - BOARD_HEIGHT + 20;
        
        int ** grid;

    public:

        // Constructor

        Board () {
            
            grid = new int * [CELL_COUNT];
            
            for (int a = 0; a < CELL_COUNT; a++) {
                grid [a] = new int [CELL_COUNT];
            }

            for (int a = 0; a < CELL_COUNT; a++) {
                for (int b = 0; b < CELL_COUNT; b++) {
                    grid [a][b] = 0;
                }
            }

        }

        // Destructor

        ~Board () {
            
            for (int a = 0; a < CELL_COUNT; a++) {

                delete [] grid [a];

            }

            delete [] grid;

        }

        // Drawing the Board

        void DrawGrid ();

        void DrawBuildings ();

        // Getters
        
        int getWidth () const { return BOARD_WIDTH; }
        int getHeight () const { return BOARD_HEIGHT; }

        int getLeft () const { return GRID_LEFT; }
        int getRight () const { return GRID_RIGHT; }
        int getTop () const { return GRID_TOP; }
        int getBottom () const { return GRID_BOTTOM; }

};

#endif