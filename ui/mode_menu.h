#ifndef MODE_MENU_H_
#define MODE_MENU_H_

#include "ui_element.h"

class UI;

class ModeMenu : public UIElement {
    
    private:
    
        UI* gameUI;
        int selectedMode;   // 0 for taxi, 1 for delivery

    public:
    
        // Constructor

        ModeMenu (UI* ui);

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;

        // Mode

        int getSelectedMode () const { return selectedMode; }
        

};

#endif 