#include "ui.h"

// Constructor

UI::UI (GameState* state, PlayerCar* car, Board* board) : 
    
    currentMenuID (MENU_MAIN),     
    gameState (state), 
    playerCar (car),
    gameBoard (board) {
    
    gameState -> setUI (this);
    
    // Initialize player name

    for (int a = 0; a < 50; a++) {

        playerName [a] = '\0';
    
    }

    // Create menus
    
    leaderboardMenu = new Leaderboard (this);
    mainMenu = new MainMenu (this);
    nameMenu = new NameMenu (this);
    modeMenu = new ModeMenu (this);
    gameOverMenu = new GameOverMenu (this);
    hud = new HUD (this);

    // Set initial menu
    
    currentMenu = mainMenu;

    // Audio

    audio = new Audio (this);

}

// Destructor

UI::~UI () {

    delete leaderboardMenu;
    delete mainMenu;
    delete nameMenu;
    delete modeMenu;
    delete gameOverMenu;
    delete hud;

    delete audio;
    
}

// Drawing

void UI::Draw () {

    if (currentMenu) {

        currentMenu -> Draw ();
    
    }

}

// User Input

void UI::HandlePrintKeys (unsigned char key) {

    if (currentMenu) {

        currentMenu -> PrintKeys (key);

    }

}

void UI::HandleNonPrintKeys (int key) {

    if (currentMenu) {

        currentMenu -> NonPrintKeys (key);

    }

}

void UI::setCurrentMenu (int menuID) {

    switch (menuID) {

        case MENU_MAIN:

            currentMenu = mainMenu;
            break;

        case MENU_MODE_SELECT:

            currentMenu = modeMenu;
            break;
        
        case MENU_NAME_ENTRY:
        
            currentMenu = nameMenu;
            break;
        
        case MENU_GAME_OVER:
        
            currentMenu = gameOverMenu;
            break;

        case MENU_LEADERBOARD:

            currentMenu = leaderboardMenu;
            break;

        case MENU_HUD:

            currentMenu = hud;
            break;

    }

    currentMenuID = menuID;

}

void UI::backToMainMenu () {

    // First stop the game
    
    gameState -> setGameOver ();  
    gameState -> resetGameState ();
    
    // Reset all game objects
    
    gameBoard -> ResetBoard ();
    playerCar -> Reset ();
    
    // Clear player name
    
    for (int a = 0; a < 50; a++) {
    
        playerName[a] = '\0';
    
    }
    
    // Switch to main menu
    
    setCurrentMenu (MENU_MAIN);

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

