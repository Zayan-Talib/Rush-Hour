#ifndef NPC_CAR_H_
#define NPC_CAR_H_

#include "actor.h"

class NPCCar : public Actor {
    private:
        float aiSpeed;        // Speed of AI movement
        bool isBlocked;       // Whether the NPC is currently blocked
        int targetCellX;      // Target cell X coordinate
        int targetCellY;      // Target cell Y coordinate
        int movementDelay;    // Delay between movements
        int lastMoveTime;     // Time of last movement

    public:
        // Constructor
        NPCCar(Board* board, GameState* state, int startCellX, int startCellY, float aiSpeed = 0.5f);

        // From Actor (override)
        virtual void Draw() override;
        virtual void Move(int dX, int dY) override;
        virtual bool canMoveTo(int newCellX, int newCellY) override;

        // AI behavior
        void updateAI();
        void setTarget(int cellX, int cellY);
        bool isAtTarget() const;
        void findNewTarget();
        
        // Getters
        bool getIsBlocked() const { return isBlocked; }
        float getAISpeed() const { return aiSpeed; }
        
        // Setters
        void setAISpeed(float speed) { aiSpeed = speed; }
        void setBlocked(bool blocked) { isBlocked = blocked; }
};

#endif 