#include "button.h"
#include "ui.h"

// Constructor

Button::Button (float x, float y, int width, int height, string label, float* bgColor, float* hoverColor, float* textColor, int round) : 
    
    x (x), 
    y (y), 
    width (width), 
    height (height), 
    label (label),
    rounding (round),
    backgroundColor (bgColor), 
    hoverColor (hoverColor), 
    textColor (textColor),
    isHovered (false) {}

// Helpers

bool Button::ContainsPoint (int px, int py) const {

    return px >= x && px <= x + width && py >= y && py <= y + height;

}

// Draw

void Button::Draw () {

    float * currentColor;

    if (isHovered) {    
        currentColor = hoverColor;
    }
    else {
        currentColor = backgroundColor;
    }

    // Draw the rounded rectangle for the button background

    DrawRoundRect ((float)x, (float)y, (float)width, (float)height, currentColor, rounding);
    
    if (!label.empty()) {

        int textX = x + width / 2 - (label.length () * 9) / 2;
        int textY = y + height / 2 - 9;

        DrawString (textX, textY, label, textColor);
 
    }

}

// User Input

void Button::MouseMove (int mouseX, int mouseY) {

    isHovered = ContainsPoint (mouseX, mouseY);

    // if (isHovered) {

    //     cout << "Hovered!";

    // }

}

void Button::MouseClick (int button, int state, int mx, int my) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && ContainsPoint (mx, my)) {
    
        isPressed = true;
    
    }

}