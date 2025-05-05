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
#include "board.h"
#include "vehicle.h"
#include "menu.h"

using namespace std;

//=================================== Game Screen =====================================

// Classes from other files

Board* gameBoard = new Board ();
Vehicle* playerCar = new Vehicle (gameBoard);
Menu* gameMenu = new Menu ();

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

	if (!gameMenu -> hasGameStarted ()) {
    
		gameMenu -> DrawMenu ();
    
	} 

	else if (playerCar -> isGameOver()) {
        
        // Game over screen - draw this instead of overlaying
        // Draw background
        DrawRectangle(0, 0, 1020, 840, colors[WHITE]);
        
        // Game over text
        string gameOverStr;
        if(playerCar->hasWon()) {
            gameOverStr = "CONGRATULATIONS! YOU WON!";
        } else if(playerCar->isTimeUp()) {
            gameOverStr = "TIME'S UP!";
        } else {
            gameOverStr = "GAME OVER - Score too low!";
        }
        
        // Draw final stats
        DrawString(400, 600, gameOverStr, colors[RED]);
		DrawString(400, 550, "Final Score: " + Num2Str(playerCar->getScore()), colors[BLACK]); 
		DrawString(400, 500, "Total Money: $" + Num2Str(playerCar->getMoney()), colors[BLACK]);
		DrawString(400, 450, "Time Remaining: " + Num2Str(playerCar->getRemainingTime()), colors[BLACK]);
		DrawString(400, 400, "Final Fuel Level: " + Num2Str(playerCar->getFuelLevel()) + "%", colors[BLACK]);
		DrawString(400, 350, "Press 'R' to restart or 'ESC' to quit", colors[BLACK]);
    
	}

	else {

		// Mid Game Text

		{
			
			// Display remaining time
			int minutes = playerCar -> getRemainingTime () / 60;
			int seconds = playerCar -> getRemainingTime () % 60;

			string timeStr = "Time: " + Num2Str (minutes) + ":" + (seconds < 10 ? "0" : "") + Num2Str (seconds);
			DrawString (150, 800, timeStr, colors [RED]);
			
			// Display Score
			string scoreStr = "Score = " + Num2Str (playerCar -> getScore ());
			DrawString (20, 800, scoreStr, colors [RED]);

			string moneyStr = "Money = $" + Num2Str(playerCar->getMoney());
			DrawString(20, 770, moneyStr, colors[GREEN]);

			// Display fuel level
			string fuelStr = "Fuel = " + Num2Str (playerCar -> getFuelLevel ());
			DrawString (20, 740, fuelStr, colors [RED]);

			// Display Mode

			string modeStr = "Mode: " + string (playerCar -> getCurrentMode () == 0 ? "TAXI" : "DELIVERY");
			DrawString (800, 800, modeStr, colors [BLUE]);

			// Display carrying status
			string carryingStr;
			
			if (playerCar -> getCurrentMode () == 0) {
				carryingStr = playerCar -> isCarryingPassenger () ? "Carrying: Passenger" : "Carrying: Nothing";
			} 
			else {
				carryingStr = playerCar -> isCarryingPackage () ? "Carrying: Package" : "Carrying: Nothing";
			}
			
			DrawString (400, 800, carryingStr, colors [GREEN]);

		}

		DrawCircle (50, 670, 10, colors [RED]);
		DrawCircle (70, 670, 10, colors [RED]);
		DrawCircle (90, 670, 10, colors [RED]);

		playerCar -> DrawFuelMeter ();

		gameBoard -> DrawBoard (playerCar -> getCurrentMode ());
		
		playerCar -> DrawCar ();

    }

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

	if (!playerCar -> isTimeUp ()) {
     
		if (key == GLUT_KEY_LEFT) {
			
			playerCar -> moveLeft ();

		} 
		
		else if (key == GLUT_KEY_RIGHT) {
		
			playerCar -> moveRight ();
		
		} 
		
		else if (key == GLUT_KEY_UP) {

			playerCar -> moveUp ();
		
		}

		else if (key == GLUT_KEY_DOWN) {
		
			playerCar -> moveDown ();
		
		}

	}

	// Call the function whenever you want to redraw the screen

	glutPostRedisplay ();

}

void PrintableKeys (unsigned char key, int x, int y) {
	
	// Arguments: key (ASCII of the key pressed), x and y (coordinates of mouse pointer)

	if (!gameMenu -> hasGameStarted ()) {
    
		gameMenu -> HandleKeypress (key);
    
		if (gameMenu -> hasGameStarted ()) {
        
			playerCar -> setMode (gameMenu -> getSelectedMode ());
        
		}
    
	} 
	
	else {
    
		if (key == 27 /* Escape key ASCII */) {

			delete playerCar;
			delete gameBoard;
	
			exit (1);
	
		}
	
		if (key == 'g' || key == 'G') {
	
			playerCar -> forceGameOver ();
			gameMenu -> addNewScore (playerCar -> getScore ());
	
		}

		if (key == 'r' || key == 'R') {
	
			gameBoard -> ResetBoard ();
			Vehicle* tempCar = new Vehicle (gameBoard);

			delete playerCar;

			playerCar = tempCar;
	
		}
	
		if (key == 'q' || key == 'Q') {
	
			playerCar -> fullFuel ();
	
		}

		if (key == 'f' || key == 'F') {
	
			if (gameBoard -> tryRefuel (playerCar)) {
				// Refuel successful
			}
	
		}
	
		if (key == 'p' || key == 'P') {
		
			playerCar -> switchMode ();
		
		}
	
		if (key == ' ') {
		
			playerCar -> pickupOrDropoff ();
		
		}
    
	
	}

	glutPostRedisplay ();

}

void MousePressedAndMoved (int x, int y) {
	
	// Auto Called When Mouse is moved inside the window
	// Arguments: x and y (coordinates of mouse pointer)
	// Use this function to find the direction of shooting

	//cout << x << " " << y << endl;
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
	
		// cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} 
	
	else if (button == GLUT_RIGHT_BUTTON) {
		
		playerCar -> printCurrentCell ();

	}

	glutPostRedisplay ();

}

//================================== Miscellaneous ===================================

void Timer (int m) {

	    // Update game time every second
		// FC = Frame Count

		static int TimeFC = 0;
		static int PassengerFC = 0;

		if (gameMenu -> hasGameStarted ()) {

			TimeFC++;
			PassengerFC++;

			if (TimeFC >= FPS) {
			
				if (!playerCar -> isTimeUp ()) {
			
					playerCar -> updateTime ();
					gameBoard -> updateAICars ();
			
				}
			
				TimeFC = 0;
			
			}

			if (PassengerFC >= FPS) {
				
				gameBoard -> trySpawnNewItem (playerCar -> getCurrentMode ());
						
				PassengerFC = 0;
			
			}

		}

		glutTimerFunc (1000.0 / FPS, Timer, 0); // Call the function again after 1000.0 / FPS milliseconds

}
 
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

	glutMainLoop ();

	// CleanUp

	delete playerCar;
    delete gameBoard;
	delete gameMenu;

	return 1;

}

#endif /* RushHour_CPP_ */