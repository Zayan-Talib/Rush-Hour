#ifndef HUD_H_
#define HUD_H_

#include "ui_element.h"

class UI;

class HUD : public UIElement {

    private:
    
        UI* gameUI;
        
    public:

        // Constructor

        HUD (UI* ui);

        // Draw

        void Draw () override;
        void PrintKeys (unsigned char key) override;
        void NonPrintKeys (int key) override;

};

#endif 