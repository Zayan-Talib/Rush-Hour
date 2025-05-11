#ifndef PACKAGE_H_
#define PACKAGE_H_

#include "transportable.h"

class Package : public Transportable {

    public:

        // Constructor

        Package (Board* board, GameState* state);
        
        // Virtual destructor

        virtual ~Package () = default;

        void Draw () override;
        void DrawPackage (int x, int y);

};

#endif 