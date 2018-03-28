//---------------------------------------------------------------------------
//Program: Skeleton for Task 1c – group assignment
//Author: Squad DELTA
//Last updated: 21/03/2018
//---------------------------------------------------------------------------

//Go to 'View > Task List' menu to open the 'Task List' pane listing the initial amendments needed to this program

//---------------------------------------------------------------------------
//----- include libraries
//---------------------------------------------------------------------------

//include standard libraries
#include <iostream>	
#include <iomanip> 
#include <conio.h> 
#include <cassert> 
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <vector>
using namespace std;

//include our own libraries
#include "RandomUtils.h"    //for Seed, Random
#include "ConsoleUtils.h"	//for Clrscr, Gotoxy, etc.
#include "TimeUtils.h"		//Date and time library used for generating the time in game with each key press

//---------------------------------------------------------------------------
//----- define constants
//---------------------------------------------------------------------------


//defining the size of the grid
const int  SIZEX(29);    	//horizontal direction
const int  SIZEY(15);		//vertical direction

							//defining symbols used for display of the grid and content
const char SPOT('@');   	//character representing spot
const char TUNNEL(' ');    	//character representing the tunnel in the array
const char WALL('#');    	//character representing the border
const char HOLE('0');		//character representing the holes
const char PILL('*');		//character representing the pills
const char ZOMBIE('Z');		//character representubg the zombies


							//defining the command letters to move the spot on the maze
const int  UP(72);			//up arrow
const int  DOWN(80); 		//down arrow
const int  RIGHT(77);		//right arrow
const int  LEFT(75);		//left arrow


							//defining the other command letters for the user
const char QUIT('Q');		//to end the game


							//limits
const int holeLimit = 12;	// amount of holes allowed to be generated in any game
const int pillLimit = 8;	// amount of pulls allowed to be generated in any game
const int zombieLimit = 4;

string Name;
struct Item {
	int x, y;
	char symbol;
};

//---------------------------------------------------------------------------
//----- run game
//---------------------------------------------------------------------------

int main()
{
	//function declarations (prototypes)
	void startScreen();
	void initialiseGame(char g[][SIZEX], char m[][SIZEX], Item& spot, int& lives, int& pillCount, vector<char>& ZOMBIES);
	void paintGame(const char g[][SIZEX], string mess);
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	void updateGameData(const char g[][SIZEX], Item& spot, const int key, string& mess, int& lives, int& pillCount, Item& pill);
	void updateGrid(char grid[][SIZEX],char maze[][SIZEX], const Item spot);
	void endProgram();




	//local variable declarations 
	char grid[SIZEY][SIZEX];										//grid for display
	char maze[SIZEY][SIZEX];										//structure of the maze
	vector<char> ZOMBIES = { ZOMBIE, ZOMBIE, ZOMBIE, ZOMBIE };		//vector declaration that contains 4 different zombies
	Item spot = { 0, 0, SPOT }; 									//spot's position and symbol
	Item pill = { PILL };
	string message("LET'S START...");								//current message to player

	const int maximumLives = 5;
	int lives = maximumLives;
	int pillCount = pillLimit;

	//action...
	startScreen(); //
	Seed();															//seed the random number generator
	//SetConsoleTitle("Spot and Zombies Game - FoP 2017-18");
	initialiseGame(grid, maze, spot, lives, pillCount, ZOMBIES);	//initialise grid (incl. walls and spot)
	paintGame(grid, message);										//display game info, modified grid and messages
	int key;														//current key selected by player
	do {
		key = getKeyPress(); 														//read in  selected key: arrow or letter command
		if (isArrowKey(key))
		{
			updateGameData(grid, spot, key, message, lives, pillCount, pill);		//move spot in that direction
			updateGrid(grid, maze, spot);											//update grid information
		}
		else
			message = "INVALID KEY!";	//set 'Invalid key' message
		paintGame(grid, message);		//display game info, modified grid and messages
	} while (!wantsToQuit(key));		//while user does not want to quit
	endProgram();						//display final message
	return 0;
}


//---------------------------------------------------------------------------
//----- initialise game state
//---------------------------------------------------------------------------

void initialiseGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, int& lives, int& pillCount, vector<char>& ZOMBIES)
{ //initialise grid and place spot in middle
	void setInitialMazeStructure(char maze[][SIZEX], vector<char>& ZOMBIES);
	void setSpotInitialCoordinates(Item& spot);
	void updateGrid(char grid[][SIZEX], char maze[][SIZEX], const Item spot);

	setInitialMazeStructure(maze, ZOMBIES);		//initialise maze
	setSpotInitialCoordinates(spot);
	updateGrid(grid, maze, spot);		//prepare grid
}

void setSpotInitialCoordinates(Item& spot)
{ //set spot coordinates inside the grid at random at beginning of game
  //If Spot spawns on the WALL, it changes direction by one.
	if (spot.x == WALL)
	{
		spot.x -= 1;
	}
	if (spot.y == WALL)
	{
		spot.y -= 1;
	}
	spot.y = Random(SIZEY - 2);      //vertical coordinate in range [1..(SIZEY - 2)]
	spot.x = Random(SIZEX - 2);      //horizontal coordinate in range [1..(SIZEX - 2)]


}

void setInitialMazeStructure(char maze[][SIZEX], vector<char>& ZOMBIES)
{ //set the position of the walls in the maze
  //initialise maze configuration
	char initialMaze[SIZEY][SIZEX]; 	//local array to store the maze structure

										//replaced method of drawing the maze using 2 FOR loops, one nested. Instead of the old method that was used before.
	for (int row(0); row < SIZEY; ++row) //for each column
	{
		for (int col(0); col < SIZEX; ++col) //for each column
		{
			if ((row == 0) || (row == SIZEY - 1))		//Top and Bottom
				initialMaze[row][col] = WALL;			//Draw WALL symbol
			else
				if ((col == 0) || (col == SIZEX - 1))	//Left and Right
					initialMaze[row][col] = WALL;		//Draw WALL symbol
				else
					initialMaze[row][col] = TUNNEL;		//Draw TUNNEL symbol
		}
	}

	//with '#' for wall, ' ' for tunnel, etc. 
	//copy into maze structure with appropriate symbols
	for (int row(0); row < SIZEY; ++row)
		for (int col(0); col < SIZEX; ++col)
			switch (initialMaze[row][col])
			{
				//not a direct copy, in case the symbols used change
			case '#': maze[row][col] = WALL; break;
			case ' ': maze[row][col] = TUNNEL; break;
			}


	//spawn for the holes
	for (int i = 0; i < holeLimit; i++)
	{
		/*rand() with remainder simply will give you shitty results
		nothing you can do*/
		int randX = Random(SIZEX - 1); // Random value for X
		int randY = Random(SIZEY - 1); // Random value for Y
		while (maze[randX][randY] != TUNNEL)//make random X and Y within the TUNNEL range.
		{
			randX = Random(SIZEY - 2);      //vertical coordinate in range [1..(SIZEY - 2)]
			randY = Random(SIZEX - 2);      //horizontal coordinate in range [1..(SIZEX - 2)]
		}
		while (maze[randX - 2][randY - 2] == HOLE)
		{
			randX = Random(SIZEY - 2);
			randY = Random(SIZEX - 2);
		}
		maze[randX][randY] = HOLE; //If everything works, insert HOLE there.
	}


	//Pills
	for (int i = 0; i < pillLimit; i++)
	{
		int randX = Random(SIZEX - 1);
		int randY = Random(SIZEY - 1);
		while (maze[randX][randY] != TUNNEL)
		{
			randX = Random(SIZEX - 2);
			randY = Random(SIZEY - 2);
			while (maze[randX][randY] == HOLE)
			{
				randX = Random(SIZEX - 2);
				randY = Random(SIZEY - 2);
			}
		}
		maze[randX][randY] = PILL;



	}

	//seeding the zombies

	maze[1][1] = ZOMBIES[0];			//spawns the first zombie in the top left corner
	maze[1][27] = ZOMBIES[1];			//spawns the second zombie in the top right corner
	maze[13][1] = ZOMBIES[2];			//spawns the third zombie in the bottom left corner
	maze[13][27] = ZOMBIES[3];			//spawns the fourth zombie in the bottom right corner

}

//---------------------------------------------------------------------------
//----- update grid state
//---------------------------------------------------------------------------

void updateGrid(char grid[][SIZEX], char maze[][SIZEX],const Item spot)
{ //update grid configuration after each move
	void setMaze(char g[][SIZEX], const char b[][SIZEX]);
	void placeItem(char g[][SIZEX], const Item spot);
	void Collision(const Item spot, char grid[][SIZEX]);

	setMaze(grid, maze);	//reset the empty maze configuration into grid
	placeItem(grid, spot);	//set spot in grid

	Collision(spot, maze); //CHECKS IF SPOT HAD COLLIDED WITH ANY ITEMS


}

void setMaze(char grid[][SIZEX], const char maze[][SIZEX])
{ //reset the empty/fixed maze configuration into grid
	for (int row(0); row < SIZEY; ++row)
		for (int col(0); col < SIZEX; ++col)
			grid[row][col] = maze[row][col];
}



void placeItem(char g[][SIZEX], const Item item)
{ //place item at its new position in grid  X-29 Y-15
	g[item.y][item.x] = item.symbol;
}

//CHECKS IF SPOT MEETS ANY ITEMS ON THE GRID
void Collision(const Item spot, char grid[][SIZEX])
{ 
	if (grid[spot.y][spot.x] == PILL) //If collided with pill
	{
		grid[spot.y][spot.x] = TUNNEL; //Replace with tunnel
	}
}
//---------------------------------------------------------------------------
//----- move items on the grid
//---------------------------------------------------------------------------
void updateGameData(const char g[][SIZEX], Item& spot, const int key, string& mess, int& lives, int& pillCount, Item& pill)
{ //move spot in required direction
	bool isArrowKey(const int k);
	void setKeyDirection(int k, int& dx, int& dy);
	void removePill(int currentX, int currentY, Item& pill, const char g[][SIZEX]);
	assert(isArrowKey(key));

	//reset message to blank
	mess = "                                         ";		//reset message to blank

															//calculate direction of movement for given key
	int dx(0), dy(0);
	setKeyDirection(key, dx, dy);

	const int currentX(0);
	const int currentY(0);

	if (lives == 0)
	{
		mess = "YOU LOST!";
		system("pause");
	}
	else {
		//check new target position in grid and update game data (incl. spot coordinates) if move is possible
		switch (g[spot.y + dy][spot.x + dx])
		{			//...depending on what's on the target position in grid...
		case TUNNEL:		//can move
			spot.y += dy;	//go in that Y direction
			spot.x += dx;	//go in that X direction
			break;
		case WALL:  							//in the event the player collides with a wall, player cannot move past it
			mess = "CANNOT GO THERE!";
			break;
		case HOLE:								//in the event the player collides with a hole, decrease lives by 1
			lives = lives - 1;
			mess = "YOU FELL INTO A HOLE... LIVES REMAINING: " + to_string(lives);
			spot.y += dy;
			spot.x += dx;
			break;
		case PILL:								//in the event the player collides with a pill, increase lives by 1
			lives = lives + 1;
			spot.y += dy;
			spot.x += dx;
			--pillCount;
			mess = "YOU ATE A PILL... PILLS REMAINING: " + to_string(pillCount);
			break;
		case ZOMBIE:							//in the event the zombie collides with the player, decrease livess by 1
			lives -= 1;
			spot.y += dy;
			spot.x += dx;
			mess = "YOU GOT BITTEN BY A ZOMBIE, OUCHIES!! " + to_string(lives);
			break;
		}
	}
}

//---------------------------------------------------------------------------
//----- process key
//---------------------------------------------------------------------------
void setKeyDirection(const int key, int& dx, int& dy)
{ //calculate direction indicated by key
	bool isArrowKey(const int k);
	assert(isArrowKey(key));
	switch (key)	//...depending on the selected key...
	{
	case LEFT:  	//when LEFT arrow pressed...
		dx = -1;	//decrease the X coordinate
		dy = 0;
		break;
	case RIGHT: 	//when RIGHT arrow pressed...
		dx = +1;	//increase the X coordinate
		dy = 0;
		break;
	case UP: 	//when UP arrow pressed...
		dx = 0;	//decrease the Y coordinate
		dy = -1;
		break;
	case DOWN: 	//when DOWN arrow pressed...
		dx = 0;	//increase the Y coordinate
		dy = +1;
		break;
	}

}

int getKeyPress()
{ //get key or command (in uppercase) selected by user
  //KEEP THIS FUNCTION AS GIVEN
	int keyPressed;
	keyPressed = _getch();			//read in the selected arrow key or command letter
	while (keyPressed == 224) 		//ignore symbol following cursor key
		keyPressed = _getch();
	keyPressed = (int)toupper(keyPressed);
	return keyPressed;		//return it in uppercase 
}

bool isArrowKey(const int key)
{	//check if the key pressed is an arrow key (also accept 'K', 'M', 'H' and 'P')
	return (key == LEFT) || (key == RIGHT) || (key == UP) || (key == DOWN);
}
bool wantsToQuit(const int key)
{	//check if the user wants to quit (when key is 'Q' or 'q')
	return key == QUIT;
}

//---------------------------------------------------------------------------
//----- display info on screen
//---------------------------------------------------------------------------
void startScreen()
{

	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	showMessage(clDarkGrey, clYellow, 10, 0, ": SPOT AND ZOMBIES :");
	//SQUAD NAMES AND GROUP NUMBER
	showMessage(clBlack, clYellow, 55, 10, "GROUP SE1-2017-18");
	showMessage(clBlack, clWhite, 55, 11, "Stelios");
	showMessage(clBlack, clWhite, 55, 12, "Dan              ");
	showMessage(clBlack, clWhite, 55, 13, "Haroon - 28600233");

	//Date and Time is displayed when the application starts it gets current time when the application have started.
	showMessage(clBlack, clYellow, 55, 0, "DATE: " + GetDate()); //Getting exact date.
	showMessage(clBlack, clYellow, 55, 1, "TIME: " + GetTime()); //Getting exact time.

																 //display menu options available
	showMessage(clBlack, clYellow, 55, 3, "TO MOVE USE KEYBOARD ARROWS ");
	showMessage(clBlack, clYellow, 55, 4, "TO FREEZE ZOMBIES PRESS 'F' ");
	showMessage(clBlack, clYellow, 55, 5, "TO KILL ZOMBIES PRESS 'K'   ");
	showMessage(clBlack, clYellow, 55, 6, "TO QUIT ENTER 'Q'           ");
	// player enters his name
	showMessage(clBlack, clGreen, 10, 5, "Please enter your Name: ");
	getline(cin, Name);
	while (Name.empty())
	{
		showMessage(clBlack, clYellow, 10, 5, "You didn't enter your name, try again : ");
		getline(cin, Name);
	}

}
string tostring(int x)
{	//convert an integer to a string
	std::ostringstream os;
	os << x;
	return os.str();
}

void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message)
{	//display a string using specified colour at a given position 
	Gotoxy(x, y);
	SelectBackColour(backColour);
	SelectTextColour(textColour);
	cout << message;
}
void paintGame(const char g[][SIZEX], string mess)
{ //display game title, messages, maze, spot and other items on screen
	string tostring(char x);
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);

	void paintGrid(const char g[][SIZEX]);


	//display game title
	showMessage(clBlack, clYellow, 0, 0, "Spot the zombies");
	//Date and Time is displayed when the application starts it gets current time when the application have started.
	showMessage(clDarkGrey, clYellow, 55, 0, "DATE: " + GetDate()); //Getting exact date.
	showMessage(clDarkGrey, clYellow, 55, 1, "TIME: " + GetTime()); //Getting exact time.

																	//display menu options available
	showMessage(clDarkGrey, clYellow, 55, 3, "TO MOVE USE KEYBOARD ARROWS ");
	showMessage(clDarkGrey, clYellow, 55, 4, "TO FREEZE ZOMBIES PRESS 'F' ");
	showMessage(clDarkGrey, clYellow, 55, 5, "TO KILL ZOMBIES PRESS 'K'   ");
	showMessage(clDarkGrey, clYellow, 55, 6, "TO QUIT ENTER 'Q'           ");

	showMessage(clDarkGreen, clYellow, 55, 10, "Welcome " + Name);

	//print auxiliary messages if any
	showMessage(clBlack, clWhite, 40, 8, mess);	//display current message


												//display grid contents
	paintGrid(g);
}
void paintGrid(const char g[][SIZEX])
{ //display grid content on screen
	SelectBackColour(clBlack);
	SelectTextColour(clWhite);
	Gotoxy(0, 2);
	for (int row(0); row < SIZEY; ++row)
	{
		for (int col(0); col < SIZEX; ++col)
			cout << g[row][col];	//output cell content
		cout << endl;
	}
}

void endProgram()
{
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	showMessage(clRed, clYellow, 40, 8, "");
	system("pause");	//hold output screen until a keyboard key is hit
}


