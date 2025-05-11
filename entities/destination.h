#ifndef Destination_H_
#define Destination_H_

#include "structure.h"

class Destination : public Structure  {

    public:

        // Constructor

        Destination (Board* board, GameState* state);

        // Destructor

        virtual ~Destination () = default;

        void Draw () override;

        void DrawDestination (int currentmode);

};

#endif 