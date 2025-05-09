#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include "entity.h"

class Structure : public Entity {

    protected:

        int type;       // Type of structure

    public:

        // Constructor

        Structure (Board* board, int startCellX, int startCellY, int type);
        
        // Virtual destructor

        virtual ~Structure () = default;

        // Inherited pure virtual method

        virtual void Draw () override = 0;

        // Getters

        int getType () const { return type; }

};

#endif 