#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include "ui_element.h"

class UI;

class MainMenu : public UIElement {
    
    private:
        
        UI* parentUI;

    public:

        // Constructor
        
        MainMenu (UI* ui);

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;

};

#endif 