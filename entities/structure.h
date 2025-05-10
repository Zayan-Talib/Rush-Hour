#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include "entity.h"

class Structure : public Entity {

    protected:

        int type;                       

        // Type of structure
        // 0 = Road
        // 1 = Building
        // 2 = Fuel Station
        // 3 = Mode Station
        // 4 = Passenger
        // 5 = Passenger Destination
        // 6 = Package
        // 7 = Package Destination
        // 8 = NPC Car

    public:

        // Constructor

        Structure (Board* board, GameState* state, int type);
        
        // Virtual destructor

        virtual ~Structure () = default;

        // Inherited pure virtual method

        virtual void Draw () override = 0;

        // Getters

        int getType () const { return type; }

};

#endif 