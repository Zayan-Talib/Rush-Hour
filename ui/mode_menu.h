#ifndef MODE_MENU_H_
#define MODE_MENU_H_

#include "ui_element.h"
#include "button.h"

class UI;

class ModeMenu : public UIElement {
    
    private:
    
        UI* gameUI;
        int selectedMode;   // 0 for taxi, 1 for delivery

        Button * buttons [3];
        int numButtons;


    public:
    
        // Constructor

        ModeMenu (UI* ui);

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;
        void MouseMove (int x, int y) override;
        void MouseClick (int button, int state, int x, int y) override;

        // Mode

        int getSelectedMode () const { return selectedMode; }
        

};

#endif 