#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "ui_element.h"
#include "button.h"

class UI;

class MainMenu : public UIElement {
    
    private:
        
        UI* parentUI;

        int numButtons;

        Button * buttons;

    public:

        // Constructor
        
        MainMenu (UI* ui);

        // Destructor

        ~MainMenu ();

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;

};

#endif 