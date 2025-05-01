#include "vehicle.h"

void Vehicle::DrawCar () {
    
    DrawSquare (x, y, 20, colors [RED]);
    glutPostRedisplay ();

}

// Movement

void Vehicle::moveLeft () {

    if (canMove () && x - 30 >= gameBoard -> getLeft () && (gameBoard -> isValidMove (x - 30, y) || gameBoard -> isFuelStation (x - 30, y))) {
        
        x -= 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveRight () {

    if (canMove () && x + 30 <= gameBoard -> getRight () && (gameBoard -> isValidMove (x + 30, y) || gameBoard -> isFuelStation (x + 30, y))) {
        
        x += 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveUp () {

    if (canMove () && y + 30 <= gameBoard -> getTop () && (gameBoard -> isValidMove (x, y + 30) || gameBoard -> isFuelStation (x, y + 30))) {
        
        y += 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveDown () {

    if (canMove () && y - 30 >= gameBoard -> getBottom () && (gameBoard -> isValidMove (x, y - 30) || gameBoard -> isFuelStation (x, y - 30))) {
        
        y -= 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}


// Fuel

void Vehicle::consumeFuel () {

    currentFuel = MAX (0, currentFuel - FUEL_CONSUMPTION);

}

void Vehicle::refillFuel () {

    currentFuel = MIN (MAX_FUEL, currentFuel + REFILL_AMOUNT);

}

int Vehicle::getCellX () const {
    
    int cx = gameBoard -> getLeft();

    for (int a = 0; a < 24; a++) {
    
        if (x >= cx && x <= cx + 30) {
            return a;
        }
    
        cx += 30;
    
    }

    return -1;

}

int Vehicle::getCellY () const {

    int cy = gameBoard -> getTop();
    
    for (int a = 0; a < 24; a++) {
    
        if (y <= cy && y >= cy - 30) {
            return a;
        }
    
        cy -= 30;
    
    }

    return -1;

}

void Vehicle::printCurrentCell () const {

    cout << "Current Cell of Car: [" << getCellY () + 1 << "][" << getCellX () + 1 << "]" << endl;

}

