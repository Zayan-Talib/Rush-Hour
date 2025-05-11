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

#include "utility/util.h"
#include "world/board.h"
#include "world/game_state.h"
#include "ui/ui.h"
#include "entities/player_car.h"

// sudo apt update
// sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev libsdl2-mixer-dev libsdl2-dev


using namespace std;

//=================================== Game Screen =====================================

// Object Creation

Board* gameBoard = new Board ();
GameState* gameState = new GameState ();
PlayerCar* playerCar = new PlayerCar (gameBoard, gameState);
UI* gameUI = new UI (gameState, playerCar, gameBoard);

// Draw Canvas

void GameDisplay () {

	// Set Background Color
	// Range: 0 to 1

	glClearColor 
	(1, // Red 
	 1, // Green
	 1, // Blue
     0  // Alpha
    );  
	
	// R=G=B=1 -> White
	// R=G=B=0 -> Black
	// R=G=B=0.5 -> Gray
	
	// Update Colors

	glClear (GL_COLOR_BUFFER_BIT);

	gameUI -> Draw ();

	glutSwapBuffers (); // Do Not Modify

}

//=================================== Before Game =====================================

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

//=================================== User Input =====================================

void NonPrintableKeys (int key, int x, int y) {
	
	// Arguments: key (ASCII of the key pressed), x and y (coordinates of mouse pointer)

	gameUI -> HandleNonPrintKeys (key);

	// Call the function whenever you want to redraw the screen

	glutPostRedisplay ();

}

void PrintableKeys (unsigned char key, int x, int y) {
	
	// Arguments: key (ASCII of the key pressed), x and y (coordinates of mouse pointer)

	gameUI -> HandlePrintKeys (key);

	glutPostRedisplay ();

}

void MousePressedAndMoved (int x, int y) {
	
	// Auto Called When Mouse is moved inside the window
	// Arguments: x and y (coordinates of mouse pointer)
	// Use this function to find the direction of shooting

	glutPostRedisplay ();

}

void MouseMoved (int x, int y) {
	
	glutPostRedisplay ();

}

void MouseClicked (int button, int state, int x, int y) {

	// Auto Called When Mouse is clicked inside the window
	// Arguments: button (Left, Middle or Right), state (button is pressed or released), x and y (coordinates of mouse pointer)

	// cout << GLUT_DOWN << " " << GLUT_UP << endl;

	if (button == GLUT_LEFT_BUTTON) {
	

	} 
	
	else if (button == GLUT_RIGHT_BUTTON) {
		
	}

	glutPostRedisplay ();

}

//================================== Miscellaneous ===================================

void Timer (int m) {

    // Update game time every second
    // FC = Frame Count

    static int TimeFC = 0;
    static int PassengerFC = 0;
    static int CarsFC = 0;

    if (gameState -> hasGameStarted ()) {

        TimeFC++;
        PassengerFC++;
        CarsFC++;

        if (TimeFC >= FPS) {

			gameState -> checkGameStatus ();
        
            if (!gameState -> isTimeUp ()) {
        
                gameState -> updateTime ();
        
            }
        
            TimeFC = 0;
        
        }

        if (PassengerFC >= FPS) {
            
            gameBoard -> trySpawnNewItem (playerCar -> getCurrentMode ());
                    
            PassengerFC = 0;
        
        }

        if (CarsFC >= FPS / (2 * gameBoard -> getNPCSpeed ())) {

            if (!gameState -> isTimeUp ()) {
        
                gameBoard -> stepNPCCars ();
				playerCar -> checkCurrentCollision ();

            }
        
            CarsFC = 0;

        }

    }

    glutTimerFunc (1000.0 / FPS, Timer, 0); // Call the function again after 1000.0 / FPS milliseconds

}
 
//===================================== Audio =========================================


//======================================= Main =======================================

int main (int argc, char*argv []) {

	int width = 1020, height = 840; 				

	InitRandomizer (); 								// Seed the RNG by current time
	
	glutInit (&argc, argv); 						// Initialize Graphics Library
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA); 	// Color Display Mode
	glutInitWindowPosition (430, 70); 				// Initial Window Position
	glutInitWindowSize (width, height); 			// Window Size
	glutCreateWindow ("Rush Hour - Zayan Talib"); 	// Title
	SetCanvasSize (width, height); 					// Pixels

	// Register your functions to the library

	glutDisplayFunc (GameDisplay);
	glutSpecialFunc (NonPrintableKeys);
	glutKeyboardFunc (PrintableKeys);
	
	// Timer function called every 1000.0 / FPS milliseconds

	glutTimerFunc (1000.0 / FPS, Timer, 0);

	glutMouseFunc (MouseClicked);
	glutPassiveMotionFunc (MouseMoved);
	glutMotionFunc (MousePressedAndMoved);

	cout << endl << "=============================================================";
	cout << endl << "                       Starting Program";
	cout << endl << "=============================================================" << endl << endl;

	glutMainLoop ();

	cout << endl << "=============================================================";
	cout << endl << "                       Ending Program";
	cout << endl << "=============================================================" << endl << endl;

	// CleanUp

	delete playerCar;
	delete gameUI;
	delete gameState;
    delete gameBoard;

	return 0;

}

#endif /* RushHour_CPP_ */