#ifndef ENTITY_H_
#define ENTITY_H_

#include "../utility/util.h"

class Board;
class GameState;

class Entity {

    protected:

        // Essential Parameters
        
        int cellX, cellY;
        Board* gameBoard;
        GameState* gameState;

    public:
    
        // Constructor

        Entity (Board* board, GameState* state, int startCellX = 0, int startCellY = 0);
        virtual ~Entity () = default;

        // Pure Virtual Methods (Have to be overriden)
        
        virtual void Draw () = 0;

        // Default Getters

        int getCellX () const { return cellX; }
        int getCellY () const { return cellY; }
        Board* getBoard () const { return gameBoard; }

        // Default Setters
        
        void setCellX (int newX) { cellX = newX; }
        void setCellY (int newY) { cellY = newY; }

};

#endif