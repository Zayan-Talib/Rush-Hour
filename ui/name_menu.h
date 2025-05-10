#ifndef NAME_MENU_H_
#define NAME_MENU_H_

#include "ui_element.h"

class UI;

class NameMenu : public UIElement {

    private:

        UI* parentUI;

    public:

        // Constructor

        NameMenu (UI* ui);

        // Main Methods

        void Draw () override;
        void PrintKeys (unsigned char key) override;

};

#endif 