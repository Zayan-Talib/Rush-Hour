#include "vehicle.h"

void Vehicle::DrawCar () {

    float * CarColor = nullptr;

    if (currentMode == MODE_TAXI) {
        CarColor = colors [RED];
    } 
    else {
        CarColor = colors [BLUE];
    }
    
    DrawSquare (x, y, 20, CarColor);
    glutPostRedisplay ();

}

// Movement

void Vehicle::moveLeft () {

    if (canMove () && x - 30 >= gameBoard -> getLeft () && gameBoard -> isValidMove (x - 30, y)) {
        
        x -= 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveRight () {

    if (canMove () && x + 30 <= gameBoard -> getRight () && gameBoard -> isValidMove (x + 30, y)) {
        
        x += 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveUp () {

    if (canMove () && y + 30 <= gameBoard -> getTop () && gameBoard -> isValidMove (x, y + 30)) {
        
        y += 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

void Vehicle::moveDown () {

    if (canMove () && y - 30 >= gameBoard -> getBottom () && gameBoard -> isValidMove (x, y - 30)) {
        
        y -= 30;

        consumeFuel ();

        if (gameBoard -> isFuelStation (x, y)) {

            refillFuel ();

        }

    }

}

// Mode Switching

void Vehicle::switchMode () {

    if (gameBoard -> isModeStation (x, y)) {
    
        currentMode = (currentMode == MODE_TAXI) ? MODE_DELIVERY : MODE_TAXI;
    
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


// Passengers and Packages

void Vehicle::pickupOrDropoff() {
    if(currentMode == MODE_TAXI) {
        if(!hasPassenger && gameBoard->isPassenger(x, y)) {
            hasPassenger = true;
            gameBoard->removePassenger(x, y);
        }
        else if(hasPassenger && gameBoard->isPassengerDestination(x, y)) {
            hasPassenger = false;
            addScore(100);
        }
    }
    else { // Delivery mode
        if(!hasPackage && gameBoard->isPackage(x, y)) {
            hasPackage = true;
            gameBoard->removePackage(x, y);
        }
        else if(hasPackage && gameBoard->isPackageDestination(x, y)) {
            hasPackage = false;
            addScore(150);
        }
    }
}