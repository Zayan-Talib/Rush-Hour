#ifndef UI_H_
#define UI_H_

#include "../utility/util.h"
#include "leaderboard.h"
#include "main_menu.h"
#include "name_menu.h"
#include "mode_menu.h"
#include "../world/game_state.h"

class UI {
    
    private:

        // User

        char playerName [50];

        // Member Objects

        Leaderboard* leaderboardMenu;
        MainMenu* mainMenu;
        NameMenu* nameMenu;
        ModeMenu* modeMenu;
        
        int currentMenu;

    public:

        // Shared state
        
        GameState* gameState;

        // Options

        static const int MENU_OPTIONS = 4;
        static const int MENU_MAIN = 0;
        static const int MENU_LEADERBOARD = 1;
        static const int MENU_MODE_SELECT = 2;
        static const int MENU_NAME_ENTRY = 3;

        // Constructor
        
        UI (GameState* state);
        
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
        
        void setCurrentMenu (int menu) { currentMenu = menu; }
        int getCurrentMenu () const { return currentMenu; }

        // Mode

        int getSelectedMode() const { return modeMenu -> getSelectedMode (); }

    
};

#endif 