#ifndef GAME_OVER_MENU_H_
#define GAME_OVER_MENU_H_

#include "ui_element.h"

class UI;

class GameOverMenu : public UIElement {
    
    private:
        
        UI* gameUI;
        
    public:

        // Constructor

        GameOverMenu (UI* ui);


        void Draw () override;
        void PrintKeys (unsigned char key) override;

};

#endif 