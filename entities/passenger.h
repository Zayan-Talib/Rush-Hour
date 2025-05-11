#ifndef PASSENGER_H_
#define PASSENGER_H_

#include "transportable.h"

class Passenger : public Transportable {

    public:

        // Constructor

        Passenger (Board* board, GameState* state);
        
        // Virtual destructor

        virtual ~Passenger () = default;

        void Draw () override;
        void DrawPassenger (int x, int y);

};

#endif 