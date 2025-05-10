#include "main_menu.h"
#include "ui.h"

// Constructor

MainMenu::MainMenu (UI* ui) : 

    UIElement (true), 
    parentUI (ui) 

{}

// Drawing

void MainMenu::Draw () {
    
    DrawString (400, 600, "RUSH HOUR", colors [RED]);
    DrawString (400, 500, "1. Play Game", colors [BLACK]);
    DrawString (400, 450, "2. View Leaderboard", colors [BLACK]);
    DrawString (400, 400, "3. Exit", colors [BLACK]);

}

// User Input

void MainMenu::PrintKeys (unsigned char key) {

    switch (key) {
            
        case '1':
    
            parentUI -> setCurrentMenu (UI::MENU_MODE_SELECT);
            break;

        case '2':

            parentUI -> setCurrentMenu (UI::MENU_LEADERBOARD);
            break;
        
        case '3':
    
            exit (0);
            break;
    
        default:
        
            break;
    
    }

}