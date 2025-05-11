#ifndef UI_H_
#define UI_H_

#include "../utility/util.h"
#include "../world/game_state.h"
#include "../entities/player_car.h"
#include "../world/board.h"
#include "leaderboard.h"
#include "main_menu.h"
#include "name_menu.h"
#include "mode_menu.h"
#include "game_over_menu.h"
#include "hud.h"

#include "../world/audio.h"

class UIElement;

class UI {
    
    private:

        // User

        char playerName [50];

        // Member Objects

        Leaderboard* leaderboardMenu;
        MainMenu* mainMenu;
        NameMenu* nameMenu;
        ModeMenu* modeMenu;
        GameOverMenu* gameOverMenu;
        HUD* hud;
        
        int currentMenuID;
        UIElement* currentMenu;

        GameState* gameState;
        PlayerCar* playerCar;
        Board* gameBoard;

        Audio* audio;
        
    public:

        // Shared state
        
        GameState* getGameState () const { return gameState; }
        PlayerCar* getPlayerCar () const { return playerCar; }
        Board* getBoard () const { return gameBoard; }

        HUD* getHUD () const { return hud; }
        Leaderboard* getLeaderboard () const { return leaderboardMenu; }
        ModeMenu* getModeMenu () const { return modeMenu; }
        Audio* getAudio () const { return audio; }

        // Options
     
        static const int MENU_MAIN = 0;
        static const int MENU_LEADERBOARD = 1;
        static const int MENU_MODE_SELECT = 2;
        static const int MENU_NAME_ENTRY = 3;
        static const int MENU_GAME_OVER = 4;
        static const int MENU_HUD = 5;

        // Constructor
        
        UI (GameState* state, PlayerCar* car, Board* gameBoard);
        
        // Destructor
        
        ~UI ();

        // Drawing

        void Draw ();

        // User Input

        void HandleClick (int x, int y);
        void HandlePrintKeys (unsigned char key);
        void HandleNonPrintKeys (int key);

        // User

        const char* getPlayerName () const { return playerName; }
        void setPlayerName (const char* name) { strcpy (playerName, name); }
        void appendToPlayerName (char c);
        void removeLastCharFromPlayerName ();

        // Menu State
        
        void setCurrentMenu (int menuID);
        
        int getCurrentMenuID () const { return currentMenuID; }
        UIElement* getCurrentMenu () const { return currentMenu; }

        // Game Over

        void backToMainMenu ();

        // Selected Mode

        int getSelectedMode () const { return modeMenu -> getSelectedMode (); }

};

#endif 