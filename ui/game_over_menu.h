#ifndef GAME_OVER_MENU_H_
#define GAME_OVER_MENU_H_

#include "ui_element.h"
#include "button.h"

class UI;

class GameOverMenu : public UIElement {
    
    private:
        
        UI* gameUI;
        
        Button * buttons [3];
        int numButtons;
        
    public:

        // Constructor

        GameOverMenu (UI* ui);

        void Draw () override;
        void PrintKeys (unsigned char key) override;
        void MouseMove (int x, int y) override;
        void MouseClick (int button, int state, int x, int y) override;

};

#endif 