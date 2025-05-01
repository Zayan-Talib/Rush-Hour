#ifndef BOARD_H_
#define BOARD_H_

#include "util.h"

class Board {

    private:

        static const int BOARD_WIDTH = 600;
        static const int BOARD_HEIGHT = 600;

        static const int StartX = 50;
        static const int StartY = 50;

        int grid [BOARD_HEIGHT][BOARD_WIDTH];

    public:

        // Constructor


        // Drawing the Board

        void DrawGrid ();


        // Getters
        
        int getWidth () const { return BOARD_WIDTH; }
        int getHeight () const { return BOARD_HEIGHT; }

};

#endif