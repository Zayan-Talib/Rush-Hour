#ifndef BUTTON_H_
#define BUTTON_H_

#include "../utility/util.h"

class Button {

    public:

        int x;
        int y;

        int width; 
        int height;

        int rounding;
    
        string label;
    
        float* backgroundColor;
        float* hoverColor;
        float* textColor;
    
        bool isHovered;
        bool isPressed;
    
        Button (float x, float y, int width, int height, string label, float* bgColor, float* hoverColor, float* textColor, int round = 0);
    
        void Draw ();
        void MouseClick (int button, int state, int x, int y);
        void MouseMove (int x, int y);

        bool getPressed () const { return isPressed; }
        void setPressed (bool press) { isPressed = press; }

        bool ContainsPoint (int px, int py) const;

};

#endif