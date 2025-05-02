# Rush Hour Game

A 2D taxi/delivery driving game built with OpenGL where players navigate through a city grid, picking up passengers or delivering packages while managing fuel and time.

## Description

Rush Hour is a time-based driving game where players can choose between two roles:
- **Taxi Driver**: Pick up passengers and drop them at their destinations
- **Delivery Driver**: Collect packages and deliver them to marked locations

## Features

- Dynamic city grid with randomly generated:
  - Buildings and obstacles
  - Fuel stations
  - Passengers/packages and their destinations
- Dual game modes (Taxi/Delivery)
- Fuel management system
- Score tracking system
- 3-minute time limit
- Collision detection
- High score system

## Controls

- **Arrow Keys**: Move the vehicle
- **Spacebar**: Pick up/drop off passengers or packages
- **P**: Switch between taxi/delivery mode at mode stations
- **F**: Debug key to refill fuel
- **R**: Reset game
- **ESC**: Exit game

## Scoring

- Taxi Mode:
  - +10 points for successful passenger delivery
  - -5 points for hitting a person
  - -2 points for hitting obstacles
  - -3 points for hitting other cars

## Build Instructions

Requires:
- OpenGL
- GLUT
- C++ compiler

To compile on Linux:
```bash
 g++ -o rush_hour game.cpp util.cpp board.cpp vehicle.cpp menu.cpp -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage -pthread
```

To run:
```bash
./rush_hour
```

## Author
- Zayan Talib
- Data Science (A)
- 24i-6514