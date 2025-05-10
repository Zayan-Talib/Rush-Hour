#include "mode_menu.h"
#include "ui.h"

// Constructor

ModeMenu::ModeMenu (UI* ui) : 

    UIElement (true), 
    gameUI (ui), 
    selectedMode (-1) 
    
{}

// Drawing

void ModeMenu::Draw () {

    DrawString (400, 600, "SELECT MODE", colors [RED]);
    DrawString (400, 500, "1. Taxi Driver", colors [BLACK]);
    DrawString (400, 450, "2. Delivery Driver", colors [BLACK]);
    DrawString (400, 400, "3. Random", colors [BLACK]);

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
 
}