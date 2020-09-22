#include <time.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <sstream>

#include "BasicLibTime.h"
#include "SGLibGlobal.h"
#include "SGLibBoard.h"

using namespace std;
using namespace BasicLib;
using namespace SGLib;

bool gameOver;
bool gamePaused;
sint64 start;
sint64 end;
string input;

void TitleScreen( void )
{	
	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;
                       
	cout << "                                 SPACE GAME I                    " << endl << endl;
	cout << "                          \"A Stellar Waste Of Time\"                         " << endl;  

	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;	
	cout << endl;
}

void IntroScreen( void )
{
	cout << " Welcome to a day in the life of a Space Trader.  You are making a living by" << endl;
	cout << " transporting, buying, and selling goods at various space stations around your" << endl;
	cout << " local star system.  Your dream is to buy a bigger ship, to make money faster" << endl;
	cout << " and thus, retire as early as possible from this thankless job.  Just be" << endl;
	cout << " careful not to run out of fuel..." << endl;
}

void GameLoop(void);
void BuildCommandLine( void );
void ParseCommandLine( string str );

int main( void )
{
	string input;

	TitleScreen();
	IntroScreen();

	while( !gameOver )
	{
		cout << " 1. New Game" << endl;
		cout << " 2. Load Game" << endl;
		cout << " 3. Exit" << endl;
		if( gamePaused && !gameOver )
			cout << " 4. Return to Game" << endl; 

		cout << endl;

		cout << ">";

		cin >> input;

		if( input == "1" )
		{
			gamePaused = false;
			StartNewGame();
			GameLoop();
		}
		else
		if( input == "2" )
		{
			gamePaused = false;
			StartSavedGame();
			GameLoop();
		}
		else
		if( input == "3" )
		{
			EndGame();
			gameOver = true;
		}
		else
		if( input == "4" && gamePaused && !gameOver )
		{
			gamePaused = false;
			cout << "Returning to current game" << endl << endl;
			GameLoop();
		}
		else
			cout << "huh?" << endl << endl;	
	}

	return 0;
}

void GameLoop(void)
{
	gameOver = false;
	cout << ">";

	while( !gameOver && !gamePaused )
	{
		start = GetTimeMS();

			BuildCommandLine();	
			UpdateObjects();

		while( ((end=GetTimeMS()) - start) < MSperFRAME )
			;
	}
}

void BuildCommandLine( void )
{
	char c;

	if( kbhit() )
	{
		c = getche();

		if( c == '\r' || c == '\n')
		{
			ParseCommandLine( input );
			input = "";
		}
		else
		if( c == '\b' )
		{
			if( input.size() > 0 )
				input.erase( input.end() - 1 );
		}
		else
			input += c;			
	}
}

void ParseCommandLine( string str )
{
	cout << endl;

	stringstream ss;
	ss.str( str );
	string first;
	string second;
	ss >> first;
	ss >> second;

	if( first == "exit" || first == "quit" )
	{
		gamePaused = true;
		cout << "Game paused" << endl;
		cout << "Returning to Main Menu" << endl << endl;
		return;
	}
	else
	if( first == "help" )
		HelpCommand();
	else
	if( first == "map" )
		MapCommand();
	else
	if( first == "save" )
	{
		cout << "Game saved." << endl;

		SaveMarkets();
		SaveShips();
		SavePorts();
	}
	else
	if( first == "target" )
	{
		if( second == "A" || second == "a" )
			TargetXCommand( 'A' );
		else
		if( second == "B" || second == "b" )
			TargetXCommand( 'B' );
		else
		if( second == "C" || second == "c" )
			TargetXCommand( 'C' );
		else
		if( second == "D" || second == "d" )
			TargetXCommand( 'D' );
		else
		if( second == "E" || second == "e" )
			TargetXCommand( 'E' );
		else
		if( second == "F" || second == "f" )
			TargetXCommand( 'F' );
		else
		if( second == "G" || second == "g" )
			TargetXCommand( 'G' );
		else
		if( second == "H" || second == "h" )
			TargetXCommand( 'H' );
		else
		if( second == "I" || second == "i" )
			TargetXCommand( 'I' );
		else
		if( second == "J" || second == "j" )
			TargetXCommand( 'J' );
		else
			TargetCommand();
	}
	else
	if( first == "market" )
		MarketCommand();
	else
	if( first == "status" )
		StatusCommand();
	else
	if( first == "dock" )
		DockCommand();
	else
	if( first == "buy" )
	{
		if( second == "" )
			cout << "Buy organics, computers, robots, fuel, or ship?" << endl;
		else
		if( second == "organics" )
			BuyCommand( organics );
		else
		if( second == "computers" )
			BuyCommand( computers );
		else
		if( second == "robots" )
			BuyCommand( robots );		
		else
		if( second == "fuel" )
			BuyCommand( fuel );
		else
		if( second == "ship" )
			BuyCommand( ships );
	}
	else
	if( first == "sell" )
	{
		if( second == "" )
			cout << "Sell organics, computers, or robots?" << endl;
		else
		if( second == "organics" )
			SellCommand( organics );
		else
		if( second == "computers" )
			SellCommand( computers );
		else
		if( second == "robots" )
			SellCommand( robots );
	}
	cout << endl;
	cout << ">";
}
