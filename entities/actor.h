#ifndef ACTOR_H_
#define ACTOR_H_

#include "entity.h"

class Actor : public Entity {

    protected:
    
        float speed;        // Movement speed
        bool active;        // Whether the actor is active/alive

    public:

        // Constructor
        
        Actor (Board* board, GameState* state, float speed = 1.0f, int startCellX = 0, int startCellY = 0);
        
        // Virtual destructor
        
        virtual ~Actor () = default;

        // Inherited pure virtual method
        
        virtual void Draw () override = 0;

        // Actor-specific methods

        virtual void Move (int newCellX, int newCellY) = 0;
        virtual bool canMoveTo (int newCellX, int newCellY) { return active; };
        
        // Getters

        float getSpeed () const { return speed; }
        bool isActive () const { return active; }

        // Setters
        
        void setSpeed (float newSpeed) { speed = newSpeed; }
        void setActive (bool isActive) { active = isActive; }

};

#endif