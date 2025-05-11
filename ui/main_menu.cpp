#include "main_menu.h"
#include "ui.h"

// Constructor

MainMenu::MainMenu (UI* ui) : 

    UIElement (true), 
    gameUI (ui),
    numButtons (3) {

    const int buttonWidth = 200;
    const int buttonHeight = 50;
    const int spacing = 20;

    int totalHeight = numButtons * buttonHeight + (numButtons - 1) * spacing;
    int startY = (totalHeight / 2 + gameUI -> getScreenHeight () / 2) - 100;
    int centerX = (gameUI -> getScreenWidth () - buttonWidth) / 2;

    string labels [] = {"Play", "Leaderboard", "Exit"};

    for (int a = 0; a < numButtons; a++) {

        int y = startY - a * (buttonHeight + spacing);
        buttons [a] = new Button (centerX, y, buttonWidth, buttonHeight, labels [a], colors [BLUE], colors [GREEN], colors [WHITE], 10);

    }

}

// Destructor

MainMenu::~MainMenu () {

    for (int a = 0; a < numButtons; a++) {

        delete buttons [a];
     
    }

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

    glClear (GL_COLOR_BUFFER_BIT);

    int x = 480;
    int y = 550;

    float * WheelColor = colors [WHITE];
    float * WindowColor = colors [SILVER];
    float * CarColor = nullptr;
    float * TopColor = nullptr;

    if (true) {
    
        CarColor = colors [YELLOW];
        TopColor = colors [WHITE];
    
    } 
    
    else {
    
        CarColor = colors [BROWN];
        TopColor = colors [BLUE];
    
    }

    // Car Body (tripled)
    DrawRectangle(x - 6, y, 72, 30, CarColor);           // Main body
    DrawRectangle(x + 3, y + 21, 54, 30, CarColor);      // Upper body

    // Windows (tripled)
    DrawRectangle(x + 9, y + 27, 21, 15, WindowColor);   // Left window
    DrawRectangle(x + 30, y + 27, 21, 15, WindowColor);  // Right window

    // Wheels (tripled)
    int wheelSize = 9;
    DrawCircle(x + 9, y, wheelSize, WheelColor);         // Left wheel
    DrawCircle(x + 48, y, wheelSize, WheelColor);        // Right wheel

    // Top (tripled)
    DrawRectangle(x + 15, y + 48, 30, 18, TopColor);     // Roof
    
    DrawString (450, 680, "RUSH HOUR", colors [RED]);
    // DrawString (400, 500, "1. Play Game", colors [WHITE]);
    // DrawString (400, 450, "2. View Leaderboard", colors [WHITE]);
    // DrawString (400, 400, "3. Exit", colors [WHITE]);

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> Draw ();

    }

    DrawString (410, 100, "By Zayan Talib (24i-6514)", colors [WHITE]);

}

// User Input

void MainMenu::PrintKeys (unsigned char key) {

    switch (key) {
            
        case '1':
    
            gameUI -> setCurrentMenu (UI::MENU_MODE_SELECT);
            break;

        case '2':

            gameUI -> setCurrentMenu (UI::MENU_LEADERBOARD);
            break;
        
        case '3':
    
            exit (0);
            break;

        case KEY_ESC:

            exit (0);
            break;
    
        default:
        
            break;
    
    }

}

void MainMenu::MouseMove (int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseMove (x, y);

    }

}

void MainMenu::MouseClick (int button, int state, int x, int y) {

    for (int a = 0; a < numButtons; a++) {

        buttons [a] -> MouseClick (button, state, x, y);
        
        if (buttons [a] -> getPressed ()) {

            buttons [a] -> setPressed (false);

            switch (a) {
            
                case 0:
            
                    gameUI -> setCurrentMenu (UI::MENU_MODE_SELECT);
                    break;
        
                case 1:
        
                    gameUI -> setCurrentMenu (UI::MENU_LEADERBOARD);
                    break;
                
                case 2:
            
                    exit (0);
                    break;
        
                default:
                
                    break;
            
            }

        }

    }


}