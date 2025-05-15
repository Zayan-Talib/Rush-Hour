#ifndef UI_ELEMENT_H_
#define UI_ELEMENT_H_

#include "../utility/util.h"

class UIElement {
    
    protected:

        bool visible;

    public:

        // Constructor
        
        UIElement (bool isVisible = true);
        virtual ~UIElement () = default;

        // Inerited Methods
        
        virtual void Draw () = 0;
        virtual void PrintKeys (unsigned char key);
        virtual void NonPrintKeys (int key);
        virtual void MouseClick (int button, int state, int x, int y);
        virtual void MouseMove (int x, int y);

        // Visibility controls

        bool isVisible () const { return visible; }
        void setVisible (bool isVisible) { visible = isVisible; }
        void toggle () { visible = !visible; }
    
};

#endif 