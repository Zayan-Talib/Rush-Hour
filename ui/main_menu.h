#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "ui_element.h"
#include "button.h"

class UI;

class MainMenu : public UIElement {
    
    private:
        
        UI* gameUI;

        Button * buttons [3];
        int numButtons;

    public:

        // Constructor
        
        MainMenu (UI* ui);

        // Destructor

        ~MainMenu ();

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;
        void MouseMove (int x, int y) override;
        void MouseClick (int button, int state, int x, int y) override;

};

#endif 