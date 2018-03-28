////---------------------------------------------------------------------------
////Program: Skeleton for Task 1c – group assignment
////Author: Pascale Vacher
////Last updated: 26 February 2018
////---------------------------------------------------------------------------
//
////Go to 'View > Task List' menu to open the 'Task List' pane listing the initial amendments needed to this program
//
////---------------------------------------------------------------------------
////----- include libraries
////---------------------------------------------------------------------------
//
////include standard libraries
//#include <iostream>	
//#include <iomanip> 
//#include <conio.h> 
//#include <cassert> 
//#include <string>
//#include <sstream>
//#include <vector>
//#include <fstream>
//using namespace std;
//
////include our own libraries
//#include "RandomUtils.h"    //for Seed, Random
//#include "ConsoleUtils.h"	//for Clrscr, Gotoxy, etc.
//#include "TimeUtils.h"		//For time related functions
//
////---------------------------------------------------------------------------
////----- define constants
////---------------------------------------------------------------------------
//
////defining the size of the grid
//const int  SIZEX(25);    	//horizontal dimension
//const int  SIZEY(15);		//vertical dimension
//							//defining symbols used for display of the grid and content
//const char SPOT('@');   	//spot
//const char TUNNEL(' ');    	//tunnel
//const char WALL('#');    	//border
//const char HOLE('0');		//hole
//const char PILL('*');		//pill
//const char ZOMBIE('Z');		//Zombie
//							//defining the command letters to move the spot on the maze
//const int  UP(72);			//up arrow
//const int  DOWN(80); 		//down arrow
//const int  RIGHT(77);		//right arrow
//const int  LEFT(75);		//left arrow
//							//defining the other command letters
//const char QUIT('Q');		//to end the game
//const char FREEZE('F');		//to freeze the zombies
//const char EAT('E');		//to eat the pills
//const char KILL('X');		//to kill the zombies
//
//const char EOFM('/');
//
//const int ZomCoordinates[2][4] = { { 1, SIZEY - 2, 1, SIZEY - 2 },
//{ 1, 1, SIZEX - 2, SIZEX - 2 } };
//
//struct Item {
//	int x, y;
//	char symbol;
//};
//
////---------------------------------------------------------------------------
////----- run game
////---------------------------------------------------------------------------
//
//int main()
//{
//	system("color 8a");
//	//function declarations (prototypes)
//	void initialiseGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, vector<Item> Zombies);
//	void paintGame(const char g[][SIZEX], string mess, int Lives, string name, int PreviousBest);
//	bool wantsToQuit(const int key);
//	void updateLives(int& currentLives, int Change);
//	bool isArrowKey(const int k);
//	int  getKeyPress();
//	void updateGameData(char g[][SIZEX], Item& spot, int key, string& mess, int& Lives, vector<Item>& Zombies, bool ZombiesFrozen, bool ZombiesVisible, int& pillCount);
//	void updateGrid(char grid[][SIZEX], char maze[][SIZEX], const Item spot, vector<Item> Zombies, bool ZombiesVisible);
//	void endProgram();
////	bool Freezing(const int k);
////  bool Eating(const int key);
////	bool KillZombies(const int key);
////	void writeScoreToFile(string name, int Score);
////	int getPreviousScore(string name);
//	void updatePillCount(int& PillCount, int Amount); ////////////////////////////////
//
//
//	
//	string PrintStartScreen();
//	void RemoveAllOf(char maze[][SIZEX], char Symbol); //////////////////////////////
//
//	//local variable declarations 
//	char grid[SIZEY][SIZEX];			//grid for display
//	char maze[SIZEY][SIZEX];			//structure of the maze
//	Item spot = { 0, 0, SPOT }; 		//spot's position and symbol
//	vector<Item> Zombies;
//	string message("LET'S START...");	//current message to player
//	int Lives(3);
//	int playerHighestScore(-1);
//	//bool ZombiesFrozen = false;          //freezes the zombies
//	//bool ZombiesVisible = true;          // used for making the zombies disappear
//	//bool cheatsUsed(false);				//Keeps track of wheather the player used cheats or not
//	int pillCount(8);                       ////////////////////////////////////
//	//action...
//	Seed();								//seed the random number generator
//	SetConsoleTitle("Spot and Zombies Game - FoP 2017-18");
//
//	Zombies.push_back({ ZomCoordinates[1][0], ZomCoordinates[0][0], ZOMBIE });
//	Zombies.push_back({ ZomCoordinates[1][1], ZomCoordinates[0][1], ZOMBIE });
//	Zombies.push_back({ ZomCoordinates[1][2], ZomCoordinates[0][2], ZOMBIE });
//	Zombies.push_back({ ZomCoordinates[1][3], ZomCoordinates[0][3], ZOMBIE });
//
//	string Name = PrintStartScreen();
//	playerHighestScore = getPreviousScore(Name);
//	if (playerHighestScore == -10)
//	{
//		writeScoreToFile(Name, -1);
//	}
//
//	initialiseGame(grid, maze, spot, Zombies);	//initialise grid (incl. walls and spot)
//	paintGame(grid, message, Lives, Name, playerHighestScore);			//display game info, modified grid and messages
//	int key;							//current key selected by player
//	do {
//		//TODO: command letters should not be case sensitive
//		key = getKeyPress(); 	//read in  selected key: arrow or letter command
//								//Freeze Key
//		if (Freezing(key))
//		{
//			ZombiesFrozen = !ZombiesFrozen;  // Set to the opposite state
//											 //cheatsUsed = true;
//		}
//		//Eat pills key
//		if (Eating(key))
//		{
//			RemoveAllOf(maze, PILL);
//			updateGrid(grid, maze, spot, Zombies, ZombiesVisible); //update grid information
//			updatePillCount(pillCount, -(pillCount));
//			cheatsUsed = true;
//		}
//		//Kill Zombies Key
//		if (KillZombies(key))  //When X key is pressed
//		{
//			ZombiesVisible = !ZombiesVisible; // Set to the opposite state
//			cheatsUsed = true;
//			if (ZombiesVisible)
//			{
//				Zombies[0].x = ZomCoordinates[1][0]; //Reset all the zombie starting locations to respawn zombies.
//				Zombies[0].y = ZomCoordinates[0][0];
//				Zombies[1].x = ZomCoordinates[1][1];
//				Zombies[1].y = ZomCoordinates[0][1];
//				Zombies[2].x = ZomCoordinates[1][2];
//				Zombies[2].y = ZomCoordinates[0][2];
//				Zombies[3].x = ZomCoordinates[1][3];
//				Zombies[3].y = ZomCoordinates[0][3];
//
//			}
//			updateGrid(grid, maze, spot, Zombies, ZombiesVisible);					//update grid information
//		}
//		if (isArrowKey(key))
//		{
//			if ((Lives <= 0) || (pillCount == 0))
//			{
//				if (cheatsUsed)
//				{
//					key = 'Q';
//				}
//				else
//				{
//					if (Lives > playerHighestScore)
//					{
//						writeScoreToFile(Name, Lives);
//						key = 'Q';
//					}
//				}
//			}
//			else
//			{
//				updateGameData(grid, spot, key, message, Lives, Zombies, ZombiesFrozen, ZombiesVisible, pillCount);//move spot in that direction
//				updateGrid(grid, maze, spot, Zombies, ZombiesVisible);					//update grid information
//			}
//		}
//		else
//			message = "INVALID KEY!";	//set 'Invalid key' message
//		paintGame(grid, message, Lives, Name, playerHighestScore);		//display game info, modified grid and messages
//	} while (!wantsToQuit(key));		//while user does not want to quit
//	endProgram();						//display final message
//	return 0;
//}
//
////---------------------------------------------------------------------------
////----- initialise game state
////---------------------------------------------------------------------------
//
//void initialiseGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, vector<Item> Zombies)
//{ //initialise grid and place spot in middle
//	void setInitialMazeStructure(char maze[][SIZEX], vector<Item> Zombies);
//	void setSpotInitialCoordinates(Item& spot);
//	void updateGrid(char grid[][SIZEX], char maze[][SIZEX], const Item spot, vector<Item> Zombies, bool ZombiesVisible);
//
//	setInitialMazeStructure(maze, Zombies);		//initialise maze
//	setSpotInitialCoordinates(spot);
//	updateGrid(grid, maze, spot, Zombies, true);		//prepare grid
//}
//
//void setSpotInitialCoordinates(Item& spot)
//{ //set spot coordinates inside the grid at random at beginning of game
//  //TODO: Spot should not spwan on inner walls
//	spot.y = Random(SIZEY - 2);      //vertical coordinate in range [1..(SIZEY - 2)]
//	spot.x = Random(SIZEX - 2);      //horizontal coordinate in range [1..(SIZEX - 2)]
//}
//
//void setInitialMazeStructure(char maze[][SIZEX], vector<Item> Zombies)
//{ //set the position of the walls in the maze
//  //TODO: initial maze configuration should be amended (size changed and inner walls removed)
//  //initialise maze configuration
//	char initialMaze[SIZEY][SIZEX] 	//local array to store the maze structure
//		= { { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#' },
//	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' } };
//	//with '#' for wall, ' ' for tunnel, etc. 
//	//copy into maze structure with appropriate symbols
//	for (int row(0); row < SIZEY; ++row)
//		for (int col(0); col < SIZEX; ++col)
//			switch (initialMaze[row][col])
//			{
//				//not a direct copy, in case the symbols used change
//			case '#': maze[row][col] = WALL; break;
//			case ' ': maze[row][col] = TUNNEL; break;
//			}
//	//Loop for each Hole that will be placed
//	for (int i = 0; i < 12; i++)
//	{
//		int randomx = 2 + Random(SIZEX - 2);//get a random x value
//		int randomy = 2 + Random(SIZEY - 2);//get a random y value
//		while (maze[randomy][randomx] != TUNNEL)//Make sure the random X,y are over a tunnel and nothing else
//		{
//			randomx = 2 + Random(SIZEX - 4);
//			randomy = 2 + Random(SIZEY - 2);
//		}
//		maze[randomy][randomx] = HOLE; //when it is above a tunnel, replace with a hole
//	}
//	//Loop through for each pill
//	for (int k = 0; k < 8; k++)
//	{
//		int randomx = Random(SIZEX - 2);//get a random x value
//		int randomy = Random(SIZEY - 2);//get a random y value
//		while (maze[randomy][randomx] != TUNNEL || maze[randomx][randomy] == HOLE)//Make sure the random X,y are over a tunnel and nothing else
//		{
//			randomx = Random(SIZEX - 2);
//			randomy = Random(SIZEY - 2);
//		}
//		maze[randomy][randomx] = PILL; //when it is above a tunnel, replace with a hole
//	}
//}
//
////---------------------------------------------------------------------------
////----- update grid state
////---------------------------------------------------------------------------
//void updatePillCount(int& PillCount, int Amount)
//{
//	PillCount += Amount;
//}
//
//void updateLives(int& currentLives, int Change)
//{
//	currentLives += Change;
//}
//
//
//void updateGrid(char grid[][SIZEX], char maze[][SIZEX], const Item spot, vector<Item> Zombies, bool ZombiesVisible)
//{ //update grid configuration after each move
//	void setMaze(char g[][SIZEX], const char b[][SIZEX]);
//	void placeItem(char g[][SIZEX], const Item spot);
//	void checkCollision(const Item spot, char grid[][SIZEX]);
//
//	setMaze(grid, maze);	//reset the empty maze configuration into grid
//	placeItem(grid, spot);	//set spot in grid
//
//	if (ZombiesVisible)
//	{
//		for (int i(0); i < Zombies.size(); i++)
//		{
//			placeItem(grid, Zombies[i]);     //Place the zombies in the corners
//		}
//	}
//
//	checkCollision(spot, maze); //Check for collisions with zombies or pills
//								//Set random 
//}
//void setMaze(char grid[][SIZEX], const char maze[][SIZEX])
//{ //reset the empty/fixed maze configuration into grid
//	for (int row(0); row < SIZEY; ++row)
//		for (int col(0); col < SIZEX; ++col)
//			grid[row][col] = maze[row][col];
//}
//
//void checkCollision(const Item spot, char grid[][SIZEX])
//{ //Checks for collisions between zombies, pills and spot
//	if (grid[spot.y][spot.x] == PILL) //If collided with pill
//	{
//		grid[spot.y][spot.x] = TUNNEL; //Replace with tunnel
//	}
//}
//
//void placeItem(char g[][SIZEX], const Item item)
//{ //place item at its new position in grid
//	g[item.y][item.x] = item.symbol;
//}
///////////THIS MAY BE USEFUL/////////////////////
//void placeChar(char g[][SIZEX], const char Symbol, int x, int y)
//{ //place item at its new position in grid
//	g[y][x] = Symbol;
//}
//
////---------------------------------------------------------------------------
////----- move items on the grid
////---------------------------------------------------------------------------
//void updateGameData(char g[][SIZEX], Item& spot, int key, string& mess, int& Lives, vector<Item>& Zombies, bool ZombiesFrozen, bool ZombiesVisible, int& pillCount) //Changed g to not a constant, so we can update the space to a tunnel
//{ //move spot in required direction
//	bool isArrowKey(const int k);
//	void setKeyDirection(int k, int& dx, int& dy);
//	void updateLives(int& currentLives, int Change);
//	void placeChar(char g[][SIZEX], const char Symbol, int x, int y);
//	void updateZombieLocation(vector<Item>& Zombies, int x, int y, Item Spot, char g[][SIZEX]);
//	assert(isArrowKey(key));
//	bool Freezing(const int key);
//	int  getKeyPress();
//	bool Eating(const int key);
//	void updatePillCount(int& PillCount, int Amount);
//	//reset message to blank
//	mess = "                                         ";		//reset message to blank
//
//															//calculate direction of movement for given key
//	int dx(0), dy(0);
//	setKeyDirection(key, dx, dy);
//
//	if (!ZombiesFrozen && ZombiesVisible)
//	{
//		updateZombieLocation(Zombies, dy, dx, spot, g);  //updates the zombies on the grid when F or X is pressed.
//	}
//
//	//check new target position in grid and update game data (incl. spot coordinates) if move is possible
//	switch (g[spot.y + dy][spot.x + dx])
//	{			//...depending on what's on the target position in grid...
//	case TUNNEL:		//can move
//		spot.y += dy;	//go in that Y direction
//		spot.x += dx;	//go in that X direction
//		break;
//	case WALL:  		//hit a wall and stay there
//		mess = "CANNOT GO THERE!";
//		break;
//	case HOLE:
//		mess = "SPOT FELL INTO A HOLE";
//		spot.y += dy;	//go in that Y direction
//		spot.x += dx;	//go in that X direction
//		updateLives(Lives, -1);
//		break;
//	case PILL:
//		mess = "SPOT ATE A PILL";
//		spot.y += dy;	//go in that Y direction
//		spot.x += dx;	//go in that X direction
//		updateLives(Lives, 1);
//		updatePillCount(pillCount, -1);
//		break;
//	case ZOMBIE:
//		mess = "SPOT HIT A ZOMBIE!";
//		spot.y += dy;
//		spot.x += dx;
//		updateLives(Lives, -1);
//		break;
//	}
//
//}
//void updateZombieLocation(vector<Item>& Zombies, int x, int y, Item Spot, char g[][SIZEX])
//{
//	for (int i(0); i < 4; i++) //Give zombies new coordinates
//	{
//		if (Zombies[i].x < Spot.x) Zombies[i].x += 1;//if zombie is to left of spot
//		else if (Zombies[i].x > Spot.x) Zombies[i].x -= 1;//If zombie is to the right of spot
//		if (Zombies[i].y < Spot.y) Zombies[i].y += 1; //If zombie is below spot
//		else if (Zombies[i].y > Spot.y) Zombies[i].y -= 1; //if zombie is above spot		
//	}
//	for (int k(0); k < 4; k++) //Loop through all zombies checking for collisions
//	{
//		for (int j(0); j < 4; j++)
//		{
//			if ((Zombies[j].x == Zombies[k].x) && (Zombies[j].y == Zombies[k].y) && (j != k))
//			{
//				Zombies[j].x = ZomCoordinates[1][j];
//				Zombies[j].y = ZomCoordinates[0][j];
//				Zombies[k].x = ZomCoordinates[1][k];
//				Zombies[k].y = ZomCoordinates[0][k];
//			}
//		}
//		if (g[Zombies[k].y][Zombies[k].x] == HOLE)
//		{
//			Zombies[k].x = ZomCoordinates[1][k];
//			Zombies[k].y = ZomCoordinates[0][k];
//		}
//	}
//	for (int i(0); i < 4; i++) //When all collisions are detected, reset zombies
//	{
//		g[Zombies[i].y][Zombies[i].x] = ZOMBIE;
//	}
//}
////---------------------------------------------------------------------------
////----- Text File Functions
////---------------------------------------------------------------------------
//void writeScoreToFile(string name, int Score)
//{
//	fstream fio;
//	string filename = name + ".txt";
//	fio.open(filename, ios::out);
//	fio << Score << EOFM;
//	fio.close();
//}
//int getPreviousScore(string name)
//{
//	ifstream fin(name + ".txt");
//	if (fin.fail())
//	{
//		return -10;
//	}
//	else
//	{
//		char indivCharacter;
//		string tempscore;
//		while ((indivCharacter = fin.get()) != EOFM)
//		{
//			tempscore += indivCharacter;
//		}
//		int score = atoi(tempscore.substr(0, 2).c_str());
//		return score;
//	}
//}
////---------------------------------------------------------------------------
////----- process key
////---------------------------------------------------------------------------
//void setKeyDirection(const int key, int& dx, int& dy)
//{ //calculate direction indicated by key
//	bool isArrowKey(const int k);
//	assert(isArrowKey(key));
//	switch (key)	//...depending on the selected key...
//	{
//	case LEFT:  	//when LEFT arrow pressed...
//		dx = -1;	//decrease the X coordinate
//		dy = 0;
//		break;
//	case RIGHT: 	//when RIGHT arrow pressed...
//		dx = +1;	//increase the X coordinate
//		dy = 0;
//		break;
//	case UP:        //when UP arrow pressed...
//		dx = 0;
//		dy = -1;	//Decrease the Y coordinate
//		break;
//	case DOWN:		//when the DOWN arrow pressed...
//		dx = 0;
//		dy = 1;		//Increase the Y coordinate
//		break;
//	}
//}
//
//int getKeyPress()
//{ //get key or command (in uppercase) selected by user
//  //KEEP THIS FUNCTION AS GIVEN
//	int keyPressed;
//	keyPressed = _getch();			//read in the selected arrow key or command letter
//	while (keyPressed == 224) 		//ignore symbol following cursor key
//		keyPressed = _getch();
//	return keyPressed;		//return it in uppercase 
//}
//
//bool isArrowKey(const int key)
//{	//check if the key pressed is an arrow key (also accept 'K', 'M', 'H' and 'P')
//	//TODO: UP and DOWN arrow keys should be detected
//	return (key == LEFT) || (key == RIGHT) || (key == UP) || (key == DOWN);
//}
//bool wantsToQuit(const int key)
//{	//check if the user wants to quit (when key is 'Q' or 'q')
//	return key == QUIT;
//}
//bool Freezing(const int key)
//{	//check if the user wants to freeze the zombies(when key is 'F')
//	return key == FREEZE;
//}
//bool Eating(const int key)
//{	//check if the user wants to eat pills (when key is 'E')
//	return key == EAT;
//}
//bool KillZombies(const int key)
//{	//check if the user wants to kill zombies (when key is 'X')
//	return key == KILL;
//}
//void RemoveAllOf(char maze[][SIZEX], char Symbol)  //Replaces zombies with the tunnel when killed
//{
//	for (int row(0); row < SIZEY; ++row)
//		for (int col(0); col < SIZEX; ++col)
//		{
//			{
//				if (maze[row][col] == Symbol)
//					maze[row][col] = TUNNEL;
//			}
//		}
//
//}
////---------------------------------------------------------------------------
////----- display info on screen
////---------------------------------------------------------------------------
//
//string tostring(int x)
//{	//convert an integer to a string
//	std::ostringstream os;
//	os << x;
//	return os.str();
//}
//string tostring(char x)
//{	//convert a char to a string
//	std::ostringstream os;
//	os << x;
//	return os.str();
//}
//void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message)
//{	//display a string using specified colour at a given position 
//	Gotoxy(x, y);
//	SelectBackColour(backColour);
//	SelectTextColour(textColour);
//	cout << message;
//}
//void paintGame(const char g[][SIZEX], string mess, int Lives, string name, int PreviousBest)
//{ //display game title, messages, maze, spot and other items on screen
//	string tostring(char x);
//	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
//	void paintGrid(const char g[][SIZEX]);
//	//display game title
//	showMessage(clDarkGrey, clYellow, 0, 0, "___GAME___");
//	showMessage(clGrey, clYellow, 40, 0, GetDate() + GetTime());
//
//	//display menu options available
//	showMessage(clGrey, clYellow, 40, 3, "TO MOVE USE KEYBOARD ARROWS ");
//	showMessage(clGrey, clYellow, 40, 4, "TO FREEZE ZOMBIES ENTER 'F' ");
//	showMessage(clGrey, clYellow, 40, 5, "TO KILL ZOMBIES ENTER 'X'   ");
//	showMessage(clGrey, clYellow, 40, 6, "TO EAT PILLS ENTER 'E'      ");
//	showMessage(clGrey, clYellow, 40, 7, "TO QUIT ENTER 'Q'           ");
//
//	//print auxiliary messages if any
//	showMessage(clDarkGrey, clWhite, 40, 8, mess);	//display current message
//
//	showMessage(clDarkGrey, clWhite, 40, 9, name);
//	showMessage(clDarkGrey, clWhite, 40, 10, "Previous Score: " + to_string(PreviousBest));
//
//	string s = to_string(Lives); //print current lives
//	showMessage(clDarkGrey, clWhite, 40, 12, "Lives: " + s);
//
//	//TODO: Show your course, your group number and names on screen
//
//	//display grid contents
//	paintGrid(g);
//}
//
//void paintGrid(const char g[][SIZEX])
//{ //display grid content on screen
//	SelectBackColour(clBlack);
//	SelectTextColour(clWhite);
//	Gotoxy(0, 2);
//	for (int row(0); row < SIZEY; ++row)
//	{
//		for (int col(0); col < SIZEX; ++col)
//			switch (g[row][col])
//			{
//			case HOLE:
//				SelectTextColour(clRed);
//				cout << g[row][col];
//				break;
//			case PILL:
//				SelectTextColour(clYellow);
//				cout << g[row][col];
//				break;
//			case WALL:
//				SelectTextColour(clWhite);
//				cout << g[row][col];
//				break;
//			case TUNNEL:
//				cout << g[row][col];
//				break;
//			case SPOT:
//				SelectTextColour(clWhite);
//				cout << g[row][col];
//				break;
//			case ZOMBIE:
//				SelectTextColour(clGreen);
//				cout << g[row][col];
//				break;
//			}
//		//cout << g[row][col];	//output cell content
//		cout << endl;
//	}
//}
//
//void endProgram()
//{
//	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
//	showMessage(clRed, clYellow, 40, 8, "");
//	showMessage(clGrey, clRed, 40, 11, "GAME OVER");
//	Gotoxy(40, 15);
//	system("pause");	//hold output screen until a keyboard key is hit
//}
//
//string PrintStartScreen()
//{
//	string NameToReturn;
//	showMessage(clBlack, clYellow, 40, 0, "DATE: " + GetDate());
//	showMessage(clBlack, clYellow, 40, 1, "TIME: " + GetTime());
//	showMessage(clBlack, clYellow, 40, 4, "TO MOVE USE KEYBOARD ARROWS ");
//	showMessage(clBlack, clYellow, 40, 5, "TO FREEZE ZOMBIES PRESS'F'");
//	showMessage(clBlack, clYellow, 40, 6, "TO KILL ZOMBIES PRESS'X'");
//	showMessage(clBlack, clYellow, 40, 7, "TO QUIT ENTER 'Q'");
//	showMessage(clBlack, clYellow, 10, 4, "--------------------");
//	showMessage(clBlack, clYellow, 10, 5, "| SPOT AND ZOMBIES |");
//	showMessage(clBlack, clYellow, 10, 6, "--------------------");
//	showMessage(clBlack, clYellow, 10, 10, "GROUP SE7 		 2017-18");
//	showMessage(clBlack, clYellow, 10, 11, "Harrison Deo		 26010941");
//	showMessage(clBlack, clYellow, 10, 12, "Ali Bajwa		 27018178");
//	showMessage(clBlack, clYellow, 10, 13, "Ismael Rabanipour      26017671");
//
//
//
//	showMessage(clBlack, clYellow, 10, 15, "Enter your name");
//
//	cin >> NameToReturn;
//	for (int i(0); i < 20; i++)
//	{
//		showMessage(clDarkGrey, clYellow, 0, i, "                                                                           ");
//
//	}
//	return NameToReturn;
//
//}