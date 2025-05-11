#include "main_menu.h"
#include "ui.h"

// Constructor

MainMenu::MainMenu (UI* ui) : 

    UIElement (true), 
    parentUI (ui),
    numButtons (4) {

    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int spacing = 20; // space between buttons
    const int numButtons = 4;

    Button* buttons [numButtons];

    int totalHeight = numButtons * buttonHeight + (numButtons - 1) * spacing;
    int startY = (parentUI -> getScreenHeight () - totalHeight) / 2;
    int centerX = (parentUI -> getScreenWidth () - buttonWidth) / 2;

    string labels [] = {"Play", "Options", "Leaderboard", "Exit"};

    for (int a = 0; a < numButtons; a++) {

        int y = startY + a * (buttonHeight + spacing);
        buttons [a] = new Button (centerX, y, buttonWidth, buttonHeight, labels [a], colors [BLUE], colors [LIGHT_BLUE], colors [WHITE], 10);

    }

}

// Destructor

MainMenu::~MainMenu () {

    delete buttons;

}

// Drawing

void MainMenu::Draw () {

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
    
    DrawString (400, 600, "RUSH HOUR", colors [RED]);
    DrawString (400, 500, "1. Play Game", colors [WHITE]);
    DrawString (400, 450, "2. View Leaderboard", colors [WHITE]);
    DrawString (400, 400, "3. Exit", colors [WHITE]);

    for (int a = 0; a < numButtons; a++) {

        //buttons [a].Draw ();

    }

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