#ifndef TRANSPORTABLE_H_
#define TRANSPORTABLE_H_

#include "entity.h"

class Transportable : public Entity {

    protected:

        int type;                       

        // Type of Transportable

        // 4 = Passenger
        // 5 = Passenger Destination
        // 6 = Package
        // 7 = Package Destination

    public:

        // Constructor

        Transportable (Board* board, GameState* state, int type);
        
        // Virtual destructor

        virtual ~Transportable () = default;

        // Inherited pure virtual method

        virtual void Draw () override = 0;

        // Getters

        int getType () const { return type; }

};

#endif 