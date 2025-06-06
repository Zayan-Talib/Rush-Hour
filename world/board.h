#ifndef BOARD_H_
#define BOARD_H_

#include "../utility/util.h"
#include "../entities/player_car.h"
#include "../entities/npc_car.h"
#include "../entities/fuel_station.h"
#include "../entities/mode_station.h"
#include "../entities/building.h"
#include "../entities/destination.h"
#include "../entities/package.h"
#include "../entities/passenger.h"

class Board {

    private:

        static const int CELL_SIZE = 30;
        static const int CELL_COUNT = 24; // 24 cells in each row and column

        static const int BOARD_WIDTH = CELL_SIZE * CELL_COUNT;
        static const int BOARD_HEIGHT = CELL_SIZE * CELL_COUNT;

        static const int GRID_LEFT = 150;
        static const int GRID_RIGHT = GRID_LEFT + BOARD_WIDTH;
        static const int GRID_TOP = 750;
        static const int GRID_BOTTOM = GRID_TOP - BOARD_HEIGHT + 20;
        
        // Grid values:
        // 0 = Road
        // 1 = Building
        // 2 = Fuel Station
        // 3 = Mode Station
        // 4 = Passenger
        // 5 = Passenger Destination
        // 6 = Package
        // 7 = Package Destination
        // 8 = NPC Car

        int ** grid;

        // Buildings
        
        static const int BUILDING_PERCENT = 35;

        void GenerateBuildings ();
        bool isValidRoad (int row, int col);
        bool canReachAllCorners ();             
        void floodFill (bool visited [][24], int row, int col);

        // Fuel Station

        FuelStation* fuelstation;
        Building* building;
        ModeStation* modestation;
        Destination* destination;

        Package* package;
        Passenger* passenger;

        // Other Logic

        void PlaceItem (int itemType, int minCount, int maxCount);
        void GenerateDestination (int itemType);

        static const int FUEL_COST = 20;       // Cost to refuel

        static const int SPAWN_CHANCE = 30;
        static const int MIN_PASSENGERS = 2;
        static const int MAX_PASSENGERS = 4;
        static const int MIN_PACKAGES = 2;
        static const int MAX_PACKAGES = 3;

        // NPC Cars
        
        static const int MAX_NPC_CARS = 30;
        static const int INITIAL_NPC_CARS = 5;
        static const int NPC_CAR_TYPE = 8;
        
        NPCCar* npcCars [MAX_NPC_CARS];
        int numNPCCars;
        static constexpr float NPC_SPEED_MULT = 1.2f;  // Movement speed multiplier

    public:

        // Constructor

        Board ();

        // Destructor

        ~Board ();

        // Helpers
        
        int getWidth () const { return BOARD_WIDTH; }
        int getHeight () const { return BOARD_HEIGHT; }

        int getCellSize () const { return CELL_SIZE; }

        int getLeft () const { return GRID_LEFT; }
        int getRight () const { return GRID_RIGHT; }
        int getTop () const { return GRID_TOP; }    
        int getBottom () const { return GRID_BOTTOM; }
        
        int getCellValue (int row, int col) const;
        void setCellValue (int row, int col, int value) { grid [row][col] = value; }

        bool GridCheck (int x, int y, int check) const;
        bool isValidMove (int x, int y) const; 

        bool isRoad (int x, int y) const { return GridCheck (x, y, 0); }
        bool isFuelStation (int x, int y) const { return GridCheck (x, y, 2); }
        bool isModeStation (int x, int y) const { return GridCheck (x, y, 3); }
        bool isPassenger (int x, int y) const { return GridCheck (x, y, 4); }
        bool isPassengerDestination (int x, int y) const { return GridCheck (x, y, 5); }
        bool isPackage (int x, int y) const { return GridCheck (x, y, 6); }
        bool isPackageDestination (int x, int y) const { return GridCheck (x, y, 7); }

        // Drawing the Board

        void ResetBoard ();
        void DrawBoard (int currentMode);
        void DrawGrid ();

        // Placing Stuff

        void PlaceModeStation () { grid [CELL_COUNT - 1][0] = 3; }
        void PlaceFuelStations () { PlaceItem (2, MIN_PACKAGES, MAX_PACKAGES); }     
        void PlacePassengers () { PlaceItem (4, MIN_PASSENGERS, MAX_PASSENGERS);  }
        void PlaceDeliveryPoints () { PlaceItem (6, MIN_PACKAGES, MAX_PACKAGES); }
        
        // Passengers and Packages

        void removePassenger (int x, int y);
        void removePackage (int x, int y);
        void removePassengerDestination (int x, int y);
        void removePackageDestination (int x, int y);

        // Replenishing

        int countPassengers () const;
        int countPackages () const;

        void ReplenishItems (int currentMode);
        void trySpawnNewItem (int currentMode);

        bool tryRefuel (PlayerCar* car);

        // Friends

        friend class PlayerCar;
        friend class NPCCar;
        friend class FuelStation;
        friend class ModeStation;
        friend class Building;
        friend class Destination;
        friend class Package;
        friend class Passenger;

        // NPC Cars

        void addNPCCar ();
        void stepNPCCars ();
        
        bool isNPCCar (int x, int y) const { return GridCheck (x, y, NPC_CAR_TYPE); }
        void increaseNPCSpeed (float mult = NPC_SPEED_MULT);
        void resetNPCSpeed ();
        float getNPCSpeed () { return NPCCar::getGlobalSpeed (); }
        
};

#endif