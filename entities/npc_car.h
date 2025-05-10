#ifndef NPC_CAR_H_
#define NPC_CAR_H_

#include "actor.h"

class NPCCar : public Actor {

    private:
    
        static constexpr float START_SPEED = 1.0f;
        static float GlobalSpeed;  // Static speed multiplier for all NPC cars

        bool isBlocked;       // Whether the NPC is currently blocked
        int targetCellX;      // Target cell X coordinate
        int targetCellY;      // Target cell Y coordinate
        int direction;        // 0 = up, 1 = right, 2 = down, 3 = left

        // Already inherited speed and active

    public:

        // Constructor
        
        NPCCar (Board* board, GameState* state);

        // From Actor (override)

        virtual void Draw () override;
        virtual void Move (int dX = 0, int dY = 0) override;
        virtual bool canMoveTo (int newCellX, int newCellY) override;

        // Getters
        
        bool getIsBlocked () const { return isBlocked; }
        int getDirection () const { return direction; }
        
        // Setters

        void setBlocked (bool blocked) { isBlocked = blocked; }
        void setDirection (int dir) { direction = dir; }

        static void setGlobalSpeed (float speed) { GlobalSpeed = speed; }
        static float getGlobalSpeed () { return GlobalSpeed; }

};

#endif 