#ifndef FUEL_STATION_H_
#define FUEL_STATION_H_

#include "structure.h"

class FuelStation : public Structure {

    public:

        // Constructor

        FuelStation (Board* board, GameState* state);
        
        // Virtual destructor

        virtual ~FuelStation () = default;

        void Draw () override;

};

#endif 