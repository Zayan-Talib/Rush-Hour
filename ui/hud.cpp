#include "hud.h"
#include "ui.h"

// Constructor

HUD::HUD (UI* ui) : 

	gameUI (ui)

{}

// Drawing

void HUD::Draw () {
		
	// Display remaining time
	
	int minutes = gameUI -> getGameState () -> getRemainingTime () / 60;
	int seconds = gameUI -> getGameState () -> getRemainingTime () % 60;

	string timeStr = "Time: " + Num2Str (minutes) + ":" + (seconds < 10 ? "0" : "") + Num2Str (seconds);
	DrawString (900, 800, timeStr, colors [RED]);
	
	// Display Score
	
	string scoreStr = "Score = " + Num2Str (gameUI -> getGameState () -> getScore ());
	DrawString (900, 770, scoreStr, colors [RED]);

	string moneyStr = "Money = $" + Num2Str(gameUI -> getPlayerCar () -> getMoney ());
	DrawString(900, 740, moneyStr, colors[GREEN]);

	// Display fuel level
	
	string fuelStr = "Fuel = " + Num2Str (gameUI -> getPlayerCar () -> getFuelLevel ());
	DrawString (30, 770, fuelStr, colors [RED]);

	// Display Mode

	string modeStr = "Mode: " + string (gameUI -> getPlayerCar () -> getCurrentMode () == 0 ? "TAXI" : "DELIVERY");
	DrawString (30, 800, modeStr, colors [BLUE]);

	// Display carrying status
	string carryingStr;
	
	if (gameUI -> getPlayerCar () -> getCurrentMode () == 0) {
		carryingStr = gameUI -> getPlayerCar () -> isCarryingPassenger () ? "Carrying: Passenger" : "Carrying: Nothing";
	} 
	else {
		carryingStr = gameUI -> getPlayerCar () -> isCarryingPackage () ? "Carrying: Package" : "Carrying: Nothing";
	}
	
	DrawString (440, 800, carryingStr, colors [GREEN]);

	// Jobs Completed

	string jobsStr;

	jobsStr = "Jobs Completed: " + Num2Str (gameUI -> getGameState () -> getJobsCompleted ());

	DrawString (420, 20, jobsStr, colors [BLACK]);

	gameUI -> getPlayerCar () -> DrawFuelMeter ();

	gameUI -> getBoard () -> DrawBoard (gameUI -> getPlayerCar () -> getCurrentMode ());
	
	gameUI -> getPlayerCar () -> Draw ();

	if (gameUI -> getBoard () -> isFuelStation (gameUI -> getPlayerCar () -> getX (), gameUI -> getPlayerCar () -> getY ())) {

		string FuelOptionStr1, FuelOptionStr2, FuelOptionStr3, FuelOptionStr4, FuelOptionStr5;

		FuelOptionStr1 = "You are at a";
		FuelOptionStr2 = "Fuel Station";
		FuelOptionStr3 = "Press 'F' to";
		FuelOptionStr4 = "refuel 50 fuel";
		FuelOptionStr5 = "It costs $20";

		DrawString (20, 700, FuelOptionStr1, colors [BLACK]);
		DrawString (20, 680, FuelOptionStr2, colors [BLACK]);
		DrawString (890, 700, FuelOptionStr3, colors [BLACK]);
		DrawString (890, 680, FuelOptionStr4, colors [BLACK]);
		DrawString (890, 620, FuelOptionStr5, colors [BLACK]);

	}

	if (gameUI -> getBoard () -> isModeStation (gameUI -> getPlayerCar () -> getX (), gameUI -> getPlayerCar () -> getY ())) {

		string ModeOptionStr1, ModeOptionStr2, ModeOptionStr3, ModeOptionStr4;

		ModeOptionStr1 = "You are at a";
		ModeOptionStr2 = "Garage";
		ModeOptionStr3 = "Press 'P' to";
		ModeOptionStr4 = "switch modes";

		DrawString (20, 700, ModeOptionStr1, colors [BLACK]);
		DrawString (20, 680, ModeOptionStr2, colors [BLACK]);
		DrawString (890, 700, ModeOptionStr3, colors [BLACK]);
		DrawString (890, 680, ModeOptionStr4, colors [BLACK]);

	}

} 

// User Input

void HUD::PrintKeys (unsigned char key) {

	if (key == KEY_ESC) {
	
		exit (0);

	}

	if (key == 'g' || key == 'G') {

		gameUI -> getGameState () -> forceGameOver ();

	}

	if (key == 'r' || key == 'R') {

		gameUI -> getBoard () -> ResetBoard ();
		gameUI -> getPlayerCar () -> ResetPosition ();

	}

	if (key == 'q' || key == 'Q') {

		gameUI -> getPlayerCar () -> fullFuel ();

	}

	if (key == 'w' || key == 'W') {

		gameUI -> getGameState () -> addScore (10);

	}

	if (key == 'm' || key == 'M') {

		gameUI -> getPlayerCar () -> addMoney (10);

	}

	if (key == 'j' || key == 'J') {

		gameUI -> getGameState () -> increaseJobsCompleted ();

	}

	if (key == 'd' || key == 'D') {

		gameUI ->  getPlayerCar () -> dropCarrying ();

	}

	if (key == 'f' || key == 'F') {

		if (gameUI -> getBoard () -> tryRefuel (gameUI -> getPlayerCar ())) {
			
		}

	}

	if (key == 'v' || key == 'V') {

		gameUI -> getAudio () -> ToggleAudio ();

	}

	if (key == 'p' || key == 'P') {
	
		gameUI -> setCurrentMenu (UI::MENU_MODE_SELECT);
	
	}

	if (key == ' ') {
	
		gameUI -> getPlayerCar () -> pickupOrDropoff ();
	
	}

}

void HUD::NonPrintKeys (int key) {

	if (key == GLUT_KEY_LEFT) {
			
		gameUI -> getPlayerCar () -> moveLeft ();

	} 
	
	else if (key == GLUT_KEY_RIGHT) {
	
		gameUI -> getPlayerCar () -> moveRight ();
	
	} 
	
	else if (key == GLUT_KEY_UP) {

		gameUI -> getPlayerCar () -> moveUp ();
	
	}

	else if (key == GLUT_KEY_DOWN) {
	
		gameUI -> getPlayerCar () -> moveDown ();
	
	}

}