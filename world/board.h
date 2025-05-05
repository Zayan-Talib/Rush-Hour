#ifndef BOARD_H_
#define BOARD_H_

#include "../utility/util.h"
#include "../entities/vehicle.h"

class Vehicle;

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
        // 8 = AI Car

        int ** grid;

        // Buildings
        
        static const int BUILDING_PERCENT = 35;

        void GenerateBuildings ();
        bool isValidRoad (int row, int col);
        bool canReachAllCorners ();             
        void floodFill (bool visited [][24], int row, int col);

        // Other Logic

        void PlaceItem (int itemType, int minCount, int maxCount);
        void GenerateDestination (int itemType);

        static const int SPAWN_CHANCE = 30;
        static const int MIN_PASSENGERS = 2;
        static const int MAX_PASSENGERS = 4;
        static const int MIN_PACKAGES = 2;
        static const int MAX_PACKAGES = 3;

        // AI Cars

        static const int MAX_AI_CARS = 10;
        static const int INITIAL_AI_CARS = 3;
        static const int AI_CAR_TYPE = 8;  // New grid value for AI cars
        
        struct AICar {
            float x;       // Actual x position
            float y;       // Actual y position
            int row;      // Grid row position
            int col;      // Grid col position
            int direction; // 0=up, 1=right, 2=down, 3=left
            bool active;
        };
        
        AICar aiCars[MAX_AI_CARS];
        int numAICars;
        float aiSpeed;  // Movement speed multiplier
    
        bool canAIMoveTo(int row, int col) const;
        void addNewAICar();
        void moveAICar(AICar& car);
        

        // Other Systems

        static const int FUEL_COST = 20;       // Cost to refuel
        static const int WIN_SCORE = 100;      // Score needed to win

    public:

        // Constructor

        Board () : numAICars (0), aiSpeed (1.0f) {
            
            InitRandomizer ();

            grid = new int * [CELL_COUNT];
            
            for (int a = 0; a < CELL_COUNT; a++) {
            
                grid [a] = new int [CELL_COUNT];
            
            }

            ResetBoard ();

            for (int a = 0; a < INITIAL_AI_CARS; a++) {
            
                addNewAICar ();
            
            }

        }

        // Destructor

        ~Board () {
            
            for (int a = 0; a < CELL_COUNT; a++) {

                delete [] grid [a];

            }

            delete [] grid;

        }

        // Helpers
        
        int getWidth () const { return BOARD_WIDTH; }
        int getHeight () const { return BOARD_HEIGHT; }

        int getLeft () const { return GRID_LEFT; }
        int getRight () const { return GRID_RIGHT; }
        int getTop () const { return GRID_TOP; }    
        int getBottom () const { return GRID_BOTTOM; }
        
        int getCellValue (int row, int col) const;
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
        void DrawModeStation ();
        void DrawBuildings ();
        void DrawFuelStations ();
        void DrawPassengersAndPackages (int currentMode);
        void DrawAICars ();

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

        bool tryRefuel (Vehicle* car);

        // AI Cars

        void stepAICars ();
        bool isAICar(int x, int y) const;
        void incrementSpeed() { aiSpeed = MIN (3.0f, aiSpeed * 1.2f); }  // 20% speed increase
        void addCar() { if(numAICars < MAX_AI_CARS) addNewAICar(); } 
        
        float getAISpeed () const { return aiSpeed; }

};

#endif