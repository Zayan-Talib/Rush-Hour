#ifndef BUILDING_H_
#define BUILDING_H_

#include "structure.h"

class Building : public Structure {

    public:

        // Constructor

        Building (Board* board, GameState* state);
        
        // Virtual destructor

        virtual ~Building () = default;

        void Draw () override;

};

#endif 