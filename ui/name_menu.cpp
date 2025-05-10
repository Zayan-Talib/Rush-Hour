#include "name_menu.h"
#include "ui.h"

// Constructor

NameMenu::NameMenu (UI* ui) : 
    
    UIElement (true), 
    gameUI (ui) 
    
{}

// Drawing

void NameMenu::Draw () {

    DrawString (400, 600, "ENTER YOUR NAME:", colors [RED]);
    DrawString (400, 500, string (gameUI -> getPlayerName ()) + "_", colors [BLACK]);
    DrawString (400, 400, "Press ENTER when done", colors [BLACK]);

}

// User Input

void NameMenu::PrintKeys (unsigned char key) {

    if (key == KEY_ENTER) {
        
        gameUI -> getGameState () -> startGame ();
        gameUI -> getPlayerCar () -> setMode (gameUI -> getSelectedMode ());
    
    }

    else if (key == KEY_BACKSPACE) {
    
        gameUI -> removeLastCharFromPlayerName ();
    
    }

    else {

        gameUI -> appendToPlayerName (key);

    }
 
}