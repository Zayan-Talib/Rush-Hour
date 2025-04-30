//============================================================================
// Zayan Talib
// 24i-6514
// Data Science (A)
// OOP - 2nd Semester 
// Final Project - Rush Hour
//============================================================================

// Definitions

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;


void SetCanvasSize (int width, int height) {
	
	// Arguments: width and height (in pixels)
	// Use this function to set the size of your game window
	// Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1, height-1)

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, width, 0, height, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

}

int xI = 400, yI = 400;

void drawCar () {
	
	DrawSquare (xI, yI, 20, colors [WHITE]);
	glutPostRedisplay ();

}

bool flag = true;

void moveCar () {
	
	if (xI > 10 && flag) {

		xI -= 10;

		cout << "going left";
		
		if (xI < 100) {
			flag = false;
		}

	}

	else if (xI < 1010 && !flag) {
		
		cout << "go right";
		
		xI += 10;
		
		if (xI > 900) {
			flag = true;
		}
			
	}

}

// Draw Canvas

void GameDisplay () {

	// Set Background Color
	// Range: 0 to 1

	glClearColor 
	(0, // Red 
	 0, // Green
	 0, // Blue
     0  // Alpha
    );  
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray
	
	// Update Colors
	glClear (GL_COLOR_BUFFER_BIT);
	
	// Red Square
	DrawSquare (400, 20, 40, colors [RED]);
	
	// Green Square
	DrawSquare (250, 250, 20, colors [GREEN]); 
	
	// Display Score
	DrawString (50, 800, "Score=0", colors [MISTY_ROSE]);
	
	// Trianlge Vertices v1 (300,50), v2 (500,50), v3 (400,250)
	DrawTriangle (300, 450, 340, 450, 320, 490, colors [MISTY_ROSE]); 
	
	// DrawLine (int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine (550, 50, 550, 480, 10, colors [MISTY_ROSE]);	
	
	DrawCircle (50, 670, 10, colors [RED]);
	DrawCircle (70, 670, 10, colors [RED]);
	DrawCircle (90, 670, 10, colors [RED]);
	
	DrawRoundRect (500, 200, 50, 100, colors [DARK_SEA_GREEN], 70);
	DrawRoundRect (100, 200, 100, 50, colors [DARK_OLIVE_GREEN], 20);	
	DrawRoundRect (100, 100, 50, 100, colors [DARK_OLIVE_GREEN], 30);
	DrawRoundRect (200, 100, 100, 50, colors [LIME_GREEN], 40);
	DrawRoundRect (350, 100, 100, 50, colors [LIME_GREEN], 20);
	
	drawCar ();
	glutSwapBuffers (); // Do Not Modify

}

void NonPrintableKeys (int key, int x, int y) {
	
	// Arguments: key (ASCII of the key pressed), x and y (coordinates of mouse pointer)

	if (key == GLUT_KEY_LEFT) {
		
		xI -= 10;

	} 
	
	else if (key == GLUT_KEY_RIGHT) {
	
		xI += 10;
	
	} 
	
	else if (key == GLUT_KEY_UP) {

		yI += 10;
	
	}

	else if (key == GLUT_KEY_DOWN) {
	
		yI -= 10;
	
	}

	// Call the function whenever you want to redraw the screen

	glutPostRedisplay ();

}

void PrintableKeys (unsigned char key, int x, int y) {
	
	// Arguments: key (ASCII of the key pressed), x and y (coordinates of mouse pointer)

	if (key == 27 /* Escape key ASCII */) {

		exit (1);

	}

	if (key == 'b' || key == 'B') {

		cout << "b pressed" << endl;

	}

	glutPostRedisplay ();

}

void Timer (int m) {

	// Implement Functionality Here
	
	moveCar ();

	glutTimerFunc (100, Timer, 0);

}
 
void MousePressedAndMoved (int x, int y) {
	
	// Auto Called When Mouse is moved inside the window
	// Arguments: x and y (coordinates of mouse pointer)
	// Use this function to find the direction of shooting

	cout << x << " " << y << endl;
	glutPostRedisplay ();

}

void MouseMoved (int x, int y) {
	
	//cout << x << " " << y << endl;
	glutPostRedisplay ();

}

void MouseClicked (int button, int state, int x, int y) {

	// Auto Called When Mouse is clicked inside the window
	// Arguments: button (Left, Middle or Right), state (button is pressed or released), x and y (coordinates of mouse pointer)

	if (button == GLUT_LEFT_BUTTON) {
	
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} 
	
	else if (button == GLUT_RIGHT_BUTTON) {
		
		cout<<"Right Button Pressed"<<endl;

	}

	glutPostRedisplay ();

}

int main (int argc, char*argv []) {

	int width = 1020, height = 840; 				

	InitRandomizer (); 								// Seed the RNG by current time
	
	glutInit (&argc, argv); 						// Initialize Graphics Library
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA); 	// Color Display Mode
	glutInitWindowPosition (50, 50); 				// Initial Window Position
	glutInitWindowSize (width, height); 			// Window Size
	glutCreateWindow ("Rush Hour"); 				// Title
	SetCanvasSize (width, height); 					// Pixels

	// Register your functions to the library

	glutDisplayFunc (GameDisplay);
	glutSpecialFunc (NonPrintableKeys);
	glutKeyboardFunc (PrintableKeys);
	
	// Timer function called every 1000.0 / FPS milliseconds

	glutTimerFunc (1000.0, Timer, 0);

	glutMouseFunc (MouseClicked);
	glutPassiveMotionFunc (MouseMoved);
	glutMotionFunc (MousePressedAndMoved);

	glutMainLoop ();

	return 1;

}

#endif /* RushHour_CPP_ */
