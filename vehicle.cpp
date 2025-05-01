#include "vehicle.h"

void Vehicle::DrawCar () {
    
    DrawSquare (x, y, 20, colors [BLACK]);
    glutPostRedisplay ();

}

void Vehicle::moveLeft () {

    if (x - 30 >= gameBoard -> getLeft ()) {
        x -= 30;
    }

}

void Vehicle::moveRight () {

    if (x + 30 <= gameBoard -> getRight ()) {
    
        x += 30;
    
    }

}

void Vehicle::moveUp () {

    if (y + 30 <= gameBoard -> getTop ()) {
    
        y += 30;
    
    }

}

void Vehicle::moveDown () {

    if (y - 30 >= gameBoard -> getBottom ()) {
    
        y -= 30;
    
    }

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