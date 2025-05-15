#include "mode_menu.h"
#include "ui.h"

// Constructor

ModeMenu::ModeMenu (UI* ui) : 

    UIElement (true), 
    gameUI (ui), 
    selectedMode (-1),
    numButtons (3) {

    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int spacing = 20;

    int totalHeight = numButtons * buttonHeight + (numButtons - 1) * spacing;
    int startY = (totalHeight / 2 + gameUI -> getScreenHeight () / 2) - 100;
    int centerX = (gameUI -> getScreenWidth () - buttonWidth) / 2;

    string labels [] = {"Taxi", "Delivery", "Random"};

    for (int a = 0; a < numButtons; a++) {

        int y = startY - a * (buttonHeight + spacing);
        buttons [a] = new Button (centerX, y, buttonWidth, buttonHeight, labels [a], colors [BLUE], colors [GREEN], colors [WHITE], 10);

    }

}

// Drawing

void ModeMenu::Draw () {

    // Set Background Color
	// Range: 0 to 1

	glClearColor 
	(0, // Red 
	 0, // Green
	 0, // Blue
     0  // Alpha
    );  

    glClear (GL_COLOR_BUFFER_BIT);
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray

    DrawString (440, 550, "SELECT MODE", colors [RED]);
    // DrawString (400, 500, "1. Taxi Driver", colors [BLACK]);
    // DrawString (400, 450, "2. Delivery Driver", colors [BLACK]);
    // DrawString (400, 400, "3. Random", colors [BLACK]);

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> Draw ();

    }

}

// User Input

void ModeMenu::PrintKeys (unsigned char key) {

    switch (key) {
            
        case '1':
        
            selectedMode = 0;  // Taxi
            break;
        
        case '2':
        
            selectedMode = 1;  // Delivery
            break;
        
        case '3':

            selectedMode = GetRandInRange (0, 2);
            break;
    
    }

    if (key == '1' || key == '2' || key == '3') {

        gameUI -> getPlayerCar () -> setMode (selectedMode);

        if (gameUI -> getGameState () -> hasGameStarted ()) {

            gameUI -> setCurrentMenu (UI::MENU_HUD);

        }

        else {

            gameUI -> setCurrentMenu (UI::MENU_NAME_ENTRY);

        }

    }

    else if (key == KEY_ESC) {

        exit (0);

    }
 
}

void ModeMenu::MouseMove (int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseMove (x, y);

    }

}

void ModeMenu::MouseClick (int button, int state, int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseClick (button, state, x, y);
        
        if (buttons [a] -> getPressed ()) {

            buttons [a] -> setPressed (false);

            switch (a) {
            
                case 0:
                
                    selectedMode = 0;  // Taxi
                    break;
                
                case 1:
                
                    selectedMode = 1;  // Delivery
                    break;
                
                case 2:
        
                    selectedMode = GetRandInRange (0, 2);
                    break;
            
            }
        
            if (a == 0 || a == 1 || a == 2) {
        
                gameUI -> getPlayerCar () -> setMode (selectedMode);
        
                if (gameUI -> getGameState () -> hasGameStarted ()) {
        
                    gameUI -> setCurrentMenu (UI::MENU_HUD);
        
                }
        
                else {
        
                    gameUI -> setCurrentMenu (UI::MENU_NAME_ENTRY);
        
                }
        
            }

        }

    }


}