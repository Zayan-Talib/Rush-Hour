#include "name_menu.h"
#include "ui.h"

// Constructor

NameMenu::NameMenu (UI* ui) : 
    
    UIElement (true), 
    gameUI (ui) 
    
{}

// Drawing

void NameMenu::Draw () {

    // Set Background Color
	// Range: 0 to 1

	glClearColor 
	(0, // Red 
	 0, // Green
	 0, // Blue
     0  // Alpha
    );  
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray

    DrawString (420, 600, "ENTER YOUR NAME:", colors [RED]);
    DrawString (420, 500, string (gameUI -> getPlayerName ()) + "_", colors [WHITE]);
    DrawString (400, 400, "Press ENTER when done", colors [WHITE]);

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

    else if (key == KEY_ESC) {

        exit (0);

    }

    else {

        gameUI -> appendToPlayerName (key);

    }
 
}