#include "ui_element.h"

// Constructor

UIElement::UIElement (bool isVisible) : visible (isVisible) {} 

// Virtual function implementations

void UIElement::PrintKeys (unsigned char key) {
    // Default implementation does nothing
}

void UIElement::NonPrintKeys (int key) {
    // Default implementation does nothing
}

void UIElement::MouseClick (int button, int state, int x, int y) {
    // Default implementation does nothing
} 

void UIElement::MouseMove (int x, int y) {
    // Default implementation does nothing
} 