#include "ui.h"

// Constructor

UI::UI (GameState* state) : currentMenu (MENU_MAIN), gameState (state) {
    
    leaderboardMenu = new Leaderboard (this);
    mainMenu = new MainMenu (this);
    nameMenu = new NameMenu (this);
    modeMenu = new ModeMenu (this);

    for (int a = 0; a < 50; a++) {

        playerName[a] = '\0';

    }

}

// Destructor

UI::~UI () {

    delete leaderboardMenu;
    delete mainMenu;
    delete nameMenu;
    delete modeMenu;

}

// Drawing

void UI::Draw () {

    switch (currentMenu) {

        case MENU_MAIN:

            mainMenu -> Draw ();
            break;
            
        case MENU_LEADERBOARD:

            leaderboardMenu -> Draw ();
            break;
            
        case MENU_MODE_SELECT:

            modeMenu -> Draw ();
            break;
            
        case MENU_NAME_ENTRY:

            nameMenu -> Draw ();
            break;

    }

}

// User Input

void UI::HandlePrintKeys (unsigned char key) {

    switch (currentMenu) {

        case MENU_MAIN:

            mainMenu -> PrintKeys (key);
            break;
            
        case MENU_LEADERBOARD:

            leaderboardMenu -> PrintKeys (key);
            
            if (key == KEY_ESC) {
                currentMenu = MENU_MAIN;
            }

            break;
            
        case MENU_MODE_SELECT:

            modeMenu -> PrintKeys (key);
            break;
            
        case MENU_NAME_ENTRY:

            nameMenu -> PrintKeys (key);
            break;

    }

}

// User

void UI::appendToPlayerName (char c) {

    int len = strlen (playerName);

    if (len < 49) {

        playerName [len] = c;
        playerName [len + 1] = '\0';
    
    }

}

void UI::removeLastCharFromPlayerName () {

    int len = strlen (playerName);
    
    if (len > 0) {
    
        playerName [len - 1] = '\0';
    
    }

}

