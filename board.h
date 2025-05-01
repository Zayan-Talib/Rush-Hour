#ifndef BOARD_H_
#define BOARD_H_

#include "util.h"

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
        
        int ** grid;

        // Grid values:
        // 0 = Road
        // 1 = Building
        // 2 = Fuel Station
        // 3 = Mode Station
        // 4 = Passenger
        // 5 = Passenger Destination
        // 6 = Package
        // 7 = Package Destination

        // Buildings
        
        static const int BUILDING_PERCENT = 35;

        bool isValidRoad (int row, int col);    // Check if a road placement is valid
        bool canReachAllCorners ();             // Verify all corners are reachable
        void floodFill (bool visited [][24], int row, int col);

    public:

        // Constructor

        Board () {
            
            grid = new int * [CELL_COUNT];
            
            for (int a = 0; a < CELL_COUNT; a++) {
                grid [a] = new int [CELL_COUNT];
            }

            ResetBoard ();

        }

        // Destructor

        ~Board () {
            
            for (int a = 0; a < CELL_COUNT; a++) {

                delete [] grid [a];

            }

            delete [] grid;

        }

        // Getters
        
        int getWidth () const { return BOARD_WIDTH; }
        int getHeight () const { return BOARD_HEIGHT; }

        int getLeft () const { return GRID_LEFT; }
        int getRight () const { return GRID_RIGHT; }
        int getTop () const { return GRID_TOP; }
        int getBottom () const { return GRID_BOTTOM; }
        
        int getCellValue (int row, int col) const;
        bool isValidMove (int x, int y) const; 

        // Drawing the Board

        void ResetBoard ();
        void DrawGrid (int currentMode);

        // Buildings

        void GenerateBuildings ();
        void DrawBuildings ();
        bool isRoad (int row, int col) const { return grid [row][col] == 0; }

        // Fuel Stations

        void PlaceFuelStations ();
        void DrawFuelStations ();
        bool isFuelStation (int x, int y) const;

        // Mode Station

        void PlaceModeStation ();
        void DrawModeStation ();
        bool isModeStation (int x, int y) const;

        // Passengers and Packages

        void PlacePassengers ();
        void PlaceDeliveryPoints ();
        void DrawPassengersAndPackages (int currentMode);
        bool isPassenger (int x, int y) const;
        bool isPassengerDestination (int x, int y) const;
        bool isPackage (int x, int y) const;
        bool isPackageDestination (int x, int y) const;
        void removePassenger (int x, int y);
        void removePackage (int x, int y);


};

#endif