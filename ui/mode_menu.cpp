#include "mode_menu.h"
#include "ui.h"

// Constructor

ModeMenu::ModeMenu (UI* ui) : 

    UIElement (true), 
    parentUI (ui), 
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
            parentUI -> setCurrentMenu (UI::MENU_NAME_ENTRY);
            break;
        
        case '2':
        
            selectedMode = 1;  // Delivery
            parentUI -> setCurrentMenu (UI::MENU_NAME_ENTRY);
            break;
        
        case '3':

            selectedMode = GetRandInRange (0, 2);
            parentUI -> setCurrentMenu (UI::MENU_NAME_ENTRY);
            break;
    
    }
 
}