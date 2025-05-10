#include "name_menu.h"
#include "ui.h"

// Constructor

NameMenu::NameMenu (UI* ui) : 
    
    UIElement (true), 
    parentUI (ui) 
    
{}

// Drawing

void NameMenu::Draw () {

    DrawString (400, 600, "ENTER YOUR NAME:", colors [RED]);
    DrawString (400, 500, string (parentUI -> getPlayerName ()) + "_", colors [BLACK]);
    DrawString (400, 400, "Press ENTER when done", colors [BLACK]);

}

// User Input

void NameMenu::PrintKeys (unsigned char key) {

    if (key == KEY_ENTER) {
        
        parentUI -> gameState -> startGame ();
    
    }

    else if (key == KEY_BACKSPACE) {
    
        parentUI -> removeLastCharFromPlayerName ();
    
    }

    else {

        parentUI -> appendToPlayerName (key);

    }
 
}