#ifndef MODE_STATION_H_
#define MODE_STATION_H_

#include "structure.h"

class ModeStation : public Structure {

    public:

        // Constructor

        ModeStation (Board* board, GameState* state);
        
        // Virtual destructor

        virtual ~ModeStation () = default;

        void Draw () override;

};

#endif 