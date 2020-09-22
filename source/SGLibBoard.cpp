#include "SGLibShip.h"
#include "SGLibPort.h"
#include "SGLibMarket.h"
#include "SGLibGlobal.h"
#include "SGLibBoard.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cstdlib>		//for rand() and srand() and RAND_MAX
#include <ctime>  		//for rand() and srand()
#include <sstream>

using std::ofstream;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::showpoint;
using std::stringstream;

	namespace SGLib
	{
		Market	market	[ numMarkets ];
		Port	port	[ numPorts ];
		Ship	ship	[ shipArraySize ];

		long updateMarket;

		double	playerAccount;

		void CreateObjects( void )
		{
			int i;
			for( i=0; i<numMarkets; i++)
			{
				CreateMarket( market[i], 'A'+i, i );
				RollMarket100Turns( market[i] );
			}

			CreatePort( port[0], "Arapahoe",	'A', 0 );
			CreatePort( port[1], "Berthoud",	'B', 1 );
			CreatePort( port[2], "Centennial",	'C', 2 );
			CreatePort( port[3], "Durango",		'D', 3 );
			CreatePort( port[4], "Eldora",		'E', 4 );
			CreatePort( port[5], "Fowler",		'F', 5 );
			CreatePort( port[6], "Gunnison",	'G', 6 );
			CreatePort( port[7], "Hooper",		'H', 7 );
			CreatePort( port[8], "Idalia",		'I', 8 );
			CreatePort( port[9], "Julesburg",	'J', 9 );

			CreateShip( ship[ playerShipIndex ], playerShipIndex, 1, port[4].position, port[4].position, port[4].idNum );

			updateMarket = 0;

			playerAccount = (rand()%6000) + 5000;

			SaveMarkets();
			SaveShips();
			SavePorts();
		}

		void SaveMarkets( void )
		{
			ofstream MarketFile( "markets.txt", ios::trunc );

			int i;
			for( i=0; i<numMarkets; i++)
				MarketFile << market[i];

			MarketFile.close();
		}

		void LoadMarkets( void )
		{
			ifstream MarketFile( "markets.txt" );

			int i;
			for( i=0; i<numMarkets; i++)
				MarketFile >> market[i];

			MarketFile.close();

			updateMarket = 0;
		}

		void SavePorts( void )
		{
			ofstream PortFile( "ports.txt", ios::trunc );

			int i;
			for( i=0; i<numPorts; i++)
				PortFile << port[i];

			PortFile.close();	
		}

		void LoadPorts( void )
		{
			ifstream PortFile( "ports.txt" );

			int i;
			for( i=0; i<numPorts; i++)
				PortFile >> port[i];

			PortFile.close();	
		}

		void SaveShips( void )
		{
			ofstream ShipFile( "ships.txt", ios::trunc );
			int i;
			for( i=playerShipIndex; i<shipArraySize; i++)
				ShipFile << ship[i];
			ShipFile.close();	

			ofstream PlayerFile( "player.txt", ios::trunc );
			PlayerFile << playerAccount;
			PlayerFile.close();
		}

		void LoadShips( void )
		{
			ifstream ShipFile( "ships.txt" );
			int i;
			for( i= playerShipIndex ; i<shipArraySize; i++)
				ShipFile >> ship[i];
			ShipFile.close();	

			ifstream PlayerFile( "player.txt" );
			PlayerFile >> playerAccount;
			PlayerFile.close();
		}

		int ConvertRealToMapX( double x )
		{
			double scale;
			double tempX;

			scale = radiusReal / radiusMap;

			tempX = x / scale;

			tempX += radiusMap;

			return (int)tempX;
		}

		int ConvertRealToMapY( double y )
		{
			double scale;
			double tempY;

			scale = radiusReal / radiusMap;

			tempY = y / scale;

			tempY += radiusMap;

			tempY = (diameterMap - tempY);

			return (int)tempY;
		}

  		void MapCommand( void )
		{
			int rowY;
			int columnX;
			int mapX, mapY;
			char map[diameterMap][diameterMap];

			for( rowY=0; rowY<diameterMap; rowY++ )
			{
				for( columnX=0; columnX<diameterMap; columnX++ )
				{
					map[rowY][columnX] = '.';
				}
			}

			mapX = ConvertRealToMapX( ship[ playerShipIndex ].position.x );
			mapY = ConvertRealToMapY( ship[ playerShipIndex ].position.y );
			map[ mapY ][ mapX ]	= 'x';

			mapX = ConvertRealToMapX( ship[ playerShipIndex ].target.x );
			mapY = ConvertRealToMapY( ship[ playerShipIndex ].target.y );
			map[ mapY ][ mapX ]	= 'o';

			int i;
			for( i=0; i<numPorts; i++ )
			{
				mapX = ConvertRealToMapX( port[i].position.x );
				mapY = ConvertRealToMapY( port[i].position.y );
				map[ mapY ][ mapX ] = port[i].letterName;
			}

			for( rowY=0; rowY<diameterMap; rowY++ )
			{
				for( columnX=0; columnX<diameterMap; columnX++ )
				{
					cout << map[rowY][columnX] << " ";
				}

				cout << endl;
			}
		}

		void MarketCommand( void )
		{
			cout << "STATION" << "\t\t" << "ORGANICS" << "\t" << "COMPUTERS" << "\t" << "ROBOTS" << endl;

			int i;
			for( i=0; i<numMarkets; i++)
				cout << market[i];
		}

		struct Target
		{
			char	letterName;
			string	name;
			double	proximity;
			string	proximityString;
			double	ETA;
			long	fuelNeeded;
		};

		vector<Target> targetList;

		void BuildTargetList( void )
		{
			Target t;

			int i;
			for( i=0; i<numPorts; i++ )
			{
				t.letterName		= port[i].letterName;
				t.name				= port[i].name;
				t.proximity			= Distance( ship[ playerShipIndex ].position, port[i].position );
				t.proximityString	= FormatDoubleWithCommas( t.proximity );
				t.ETA				= SintoHrs( t.proximity/ship[ playerShipIndex ].maxVelocityKMperS );
				t.fuelNeeded		= (long)(t.ETA * ship[ playerShipIndex ].fuelPerHour );

				targetList.push_back( t );
			}
		}

		bool operator<(const Target& t1, const Target& t2 )
		{
			return t1.proximity < t2.proximity;
		}

		void TargetCommand( void )
		{
			targetList.clear();
			BuildTargetList();

			sort( targetList.begin(), targetList.end() );

			cout << left << setw(11) << "SELECT";
			cout << left << setw(15) << "STATION";
			cout << left << setw(20) << "PROXIMITY (km)";
			cout << left << setw(14) << "ETA (hrs)";
			cout << left << setw(11) << "FUEL";
			cout << endl;
			
			int i;
			for( i=0; i<numPorts; i++ )
			{
				cout << left << setw(11)	<< targetList[i].letterName;
				cout << left << setw(15)	<< targetList[i].name;
				cout << left << setw(20)	<< targetList[i].proximityString;
				cout << left << setw(14)	<< fixed << setprecision(1) << showpoint << targetList[i].ETA;
				cout << left << setw(11)	<< targetList[i].fuelNeeded;

				cout << endl;
			}

			cout << "Current Fuel Level: " << ship[ playerShipIndex ].fuel << endl;
		}

		void HelpCommand( void )
		{
			cout << "Commands available:" << endl;
			cout << " help" << endl;
			cout << " save" << endl;
			cout << " target (A,B,C,D,E,F,G,H,I,J)" << endl;
			cout << " dock" << endl;
			cout << " map" << endl;
			cout << " status" << endl;
			cout << " market" << endl;
			cout << " sell" << endl;
			cout << " buy (organics, computers, robots, fuel, ship)" << endl;
			cout << " quit" << endl << endl;
			cout << "Some commands can be used alone or with additional arguments.  Additional arguments  " << endl;
			cout << "are listed in parenthesis above.  The \'target\' command, for example, when used alone " << endl;
			cout << "will present a list of all available targets, in order of proximity to your current  " << endl;
			cout << "position.  The \'target x\' command, where \'x\' is the letter of the station you wish   " << endl;
			cout << "to fly to, will engage the automatic pilot and begin the journey to your destination." << endl;
			cout << "                                                                                     " << endl;
			cout << "When you arrive within the vicinity of your target, the autopilot will alert you with" << endl;
			cout << "a message.  You can then use the \'dock\' command to land.                             " << endl;
			cout << "                                                                                     " << endl;
			cout << "The \'market\' command will list all the current prices for goods at each station, +/- " << endl;
			cout << "the difference from the market average.  To make a profit, remember to buy low and   " << endl;
			cout << "sell high.                                                                           " << endl;
			cout << "                                                                                     " << endl;
			cout << "The \'map\' command will give you a two-dimensional representation of local space, but " << endl;
			cout << "remember that this can only be used as a general approximation, as true space is in  " << endl;
			cout << "all directions.                                                                      " << endl;
		}

		void StatusCommand( void )
		{
			stringstream ss;
			string temp;
			int percent;

			cout  << left << setw(12) << "AUTOPILOT:";
			if( !ship[ playerShipIndex ].docked )
				cout << "Enroute to " << port[ ship[ playerShipIndex ].targetID ].name << endl;
			else	
				cout << "Docked at " << port[ ship[ playerShipIndex ].targetID ].name << endl;

			cout << left << setw(12) << "VELOCITY: ";
			ss << FormatDoubleWithCommas(VectorMagnitude( ship[playerShipIndex].velocity ));
			ss << " km/s";
			temp = ss.str();
			cout << left << setw(25) << temp;
			ss.str("");
			temp = "";
			percent = (int)( ( VectorMagnitude(ship[ playerShipIndex ].velocity) / ship[ playerShipIndex ].maxVelocityKMperS ) * 100 );
			cout << "(" << percent << "% of " << FormatDoubleWithCommas(ship[ playerShipIndex ].maxVelocityKMperS) << ")" << endl;
			temp = "";

			cout << left << setw(12) << "FUEL:";
			ss << ship[ playerShipIndex ].fuel;
			ss << " units";
			temp = ss.str();
			cout << left << setw(25) << temp;
			ss.str("");
			temp = "";
			percent = (int)( ( (double)ship[ playerShipIndex ].fuel / (double)ship[ playerShipIndex ].fuelCapacity ) * 100 );
			cout << "(" << percent << "% of " << ship[ playerShipIndex ].fuelCapacity << ")" << endl;
			temp = "";

			cout << left << setw(12) << "TARGET:";
			cout << left << setw(25) << port[ ship[ playerShipIndex ].targetID ].name;
			cout << "[" << FormatDoubleWithCommas( VectorMagnitude(ship[playerShipIndex].heading) );
			cout << " km,";
			double proximity = VectorMagnitude(ship[playerShipIndex].heading);
			double ETA		 = SintoHrs( proximity/ship[playerShipIndex].maxVelocityKMperS );
			cout << " ETA " << fixed << setprecision(1) << showpoint << ETA;
			cout << " hrs (";
			cout << (int)(ETA * 60) << " min)]" << endl;
			ss.str("");
			temp = "";

			cout << left << setw(12) << "CARGO:";
			ss << "ORG: ";
			ss << ship[playerShipIndex].cargo[organics] << " COM: ";
			ss << ship[playerShipIndex].cargo[computers] << " ROB: ";
			ss << ship[playerShipIndex].cargo[robots];
			temp = ss.str();
			cout << left << setw(25) << temp;
			cout << "(" << PercentCargoCapacity( ship[playerShipIndex] ) << "% of " << ship[playerShipIndex].cargoCapacity;
			cout << ")" << endl;				
			ss.str("");
			temp = "";

			cout << left << setw(12) << "ACCOUNT:";
			cout << "$" << FormatDoubleWithCommas( playerAccount );
			cout << endl;
			ss.str("");
			temp = "";
		}

		void AutopilotUpdateShip( int ms, Ship& ship, Port& port )
		{
			if( ship.docked )
			{
				//Match parent's heading and velocity
				// - can't match port's heading becuase it doesn't have one!
				ship.velocity = port.velocity;

				//UpdateShip will move position (and !docked then no fuel used)
			}
			else
			{
				//Ship isn't docked, so it's heading toward it's target
				if( Distance( ship.position, ship.target ) < ship.autopilotRange )
				{
					//This is a hack to send a message immediately (and once) the player gets in range
					//note: for future games with moving targets, this won't work
					if( VectorMagnitude( ship.velocity ) > 0 )
					{	cout << endl;
						cout << "Arriving in vacinity of " << port.name << endl;
						cout << "Within dock range" << endl;
						cout << "Powering down engines" << endl << endl;
						cout << ">";
					}

					//CASE 1: target is within range
					//ship.heading = port.heading;  Again, port doesn't have a heading
					ship.velocity = port.velocity;
				}
				else
				{
					//CASE 2: target is still out of autopilot stop range
					ship.target = port.position; //Is it me, or is the target Point not needed??
					ship.heading = CreateVectorAtoB( ship.position, ship.target );
					ship.velocity = ship.heading;
					ship.velocity = CurbVector( ship.velocity, ship.maxVelocityKMperS );
					if( ship.fuel == 0 )
						ship.velocity = CurbVector( ship.velocity, 0 );
				}
			}
		}

		void UpdateObjects( void )
		{
			int i;
			for( i=playerShipIndex; i<shipArraySize; i++)
				AutopilotUpdateShip( MSperFRAME, ship[i], port[ship[i].targetID] );	
			
			for( i=playerShipIndex; i<shipArraySize; i++)
				UpdateShipMS( ship[i], MSperFRAME*gametimeMultiplier );

			updateMarket += MSperFRAME*gametimeMultiplier;
			if( updateMarket > 1000*60*60 )
			{	
				for( i=0; i<numMarkets; i++) 
					UpdateMarket( market[i] );
				
				updateMarket = 0;
			}
		}

		void DockCommand( void )
		{
			//heading is used in the autopilot calculation
			SetHeading( ship[playerShipIndex] );

			if( DistanceToTarget( ship[playerShipIndex] ) < ship[playerShipIndex].autopilotRange )
			{
				DockShip( ship[playerShipIndex] );
				cout << "Docking at " << port[ship[playerShipIndex].targetID].name << " Station." << endl;
			}
			else
			{
				cout << "Target is out of dock range." << endl;
			}
		}

		void TargetXCommand( char ID )
		{
			int i = ID - 'A';

			ship[playerShipIndex].docked	= false;
			ship[playerShipIndex].target	= port[i].position;
			ship[playerShipIndex].targetID	= port[i].idNum;

			cout << "Autopilot set for " << port[ ship[playerShipIndex].targetID ].name << ". Engines set to full power." << endl;
		}

		void BuyCommand( int c )
		{
			if( ship[playerShipIndex].docked )
			{
				if( c == organics || c == computers || c == robots )
				{
					double HowManyCanIAfford = playerAccount / ( market[ship[playerShipIndex].targetID].price[c] );
					double HowMuchRoomLeft	 = RemainingCargoSpace( ship[playerShipIndex] );

					if( HowManyCanIAfford < HowMuchRoomLeft )
					{
						if( (int)HowManyCanIAfford > 0 )
						{
							cout << "Buying " << (int)HowManyCanIAfford << " ";
							cout << market[ship[playerShipIndex].targetID].name[c] << " for ";
							cout << market[ship[playerShipIndex].targetID].price[c] << " credits per unit." << endl;
							AddCargo( ship[playerShipIndex], (int)HowManyCanIAfford, c );
							playerAccount -= (int)HowManyCanIAfford * market[ship[playerShipIndex].targetID].price[c];
						}
						else
							cout << "You can't afford any " << market[ship[playerShipIndex].targetID].name[c] << "." << endl;
					}
					else
					if( HowMuchRoomLeft < HowManyCanIAfford )
					{
						if( (int)HowMuchRoomLeft > 0 )
						{
							cout << "Buying " << (int)HowMuchRoomLeft << " ";
							cout << market[ship[playerShipIndex].targetID].name[c] << " for ";
							cout << market[ship[playerShipIndex].targetID].price[c] << " credits per unit." << endl;
							AddCargo( ship[playerShipIndex], (int)HowMuchRoomLeft, c );
							playerAccount -= (int)HowMuchRoomLeft * market[ship[playerShipIndex].targetID].price[c];
						}
						else
							cout << "You don't have any room left for " << market[ship[playerShipIndex].targetID].name[c] << "." << endl;
					}
				}
				else
				if( c == fuel )
				{
					double HowManyCanIAfford = playerAccount / priceFuel;
					double HowMuchRoomLeft	 = RemainingFuelSpace( ship[playerShipIndex] );
					
					if( HowManyCanIAfford < HowMuchRoomLeft )
					{
						if( (int)HowManyCanIAfford > 0 )
						{
							cout << "Buying " << (int)HowManyCanIAfford << " ";
							cout << "units of fuel for " << priceFuel << " per unit." << endl;
							AddFuel( ship[playerShipIndex], (int)HowManyCanIAfford );
							playerAccount -= (int)HowManyCanIAfford * priceFuel;
						}
						else
							cout << "You can't afford any fuel." << endl;
					}
					else
					if( HowMuchRoomLeft < HowManyCanIAfford )
					{
						if( (int)HowMuchRoomLeft > 0 )
						{
							cout << "Buying " << (int)HowMuchRoomLeft << " ";
							cout << "units of fuel for " << priceFuel << " per unit." << endl;
							AddFuel( ship[playerShipIndex], (int)HowMuchRoomLeft );
							playerAccount -= (int)HowMuchRoomLeft * priceFuel;
						}
						else
							cout << "You don't have any room left for more fuel." << endl;
					}
				}
				else
				if( c == ships )
				{
					double valueOfCurrentShip = ship[playerShipIndex].value * 0.67;

					if( ship[playerShipIndex].shipClass < 5 )
					{
						Ship newship;
						LevelShip( newship, ship[playerShipIndex].shipClass + 1 );
						double valueOfNextShip = newship.value;
						
						cout << "Your current ship is worth $" << FormatDoubleWithCommas(valueOfCurrentShip) << endl;

						if( playerAccount + valueOfCurrentShip > valueOfNextShip )
						{
							cout << "Buying a Level " << (ship[playerShipIndex].shipClass + 1);
							cout << " class ship for $" << FormatDoubleWithCommas(valueOfNextShip) << endl;

							LevelShip( ship[playerShipIndex], (ship[playerShipIndex].shipClass + 1) );

							playerAccount += valueOfCurrentShip;
							playerAccount -= valueOfNextShip;
						}
						else
						{
							double needThisMuch = valueOfNextShip - (playerAccount + valueOfCurrentShip);
							cout << "You need an additional $" << FormatDoubleWithCommas(needThisMuch);
							cout << " to buy a Level " << (ship[playerShipIndex].shipClass + 1) << " class ship" << endl;
						}
					}
					else
					{
						cout << "You already have the biggest ship they make you greedy bastard." << endl;
					}			
				}
			}
			else
				cout << "You must be docked at a space station to buy and sell goods" << endl;
		}

		void SellCommand( int c )
		{
			if( ship[playerShipIndex].docked )
			{
				if( ship[playerShipIndex].cargo[c] > 0 )
				{
					cout << "Selling " << ship[playerShipIndex].cargo[c] << " ";
					cout << market[ship[playerShipIndex].targetID].name[c] << " for ";
					cout << market[ship[playerShipIndex].targetID].price[c] << " credits per unit." << endl;
					playerAccount += ship[playerShipIndex].cargo[c] * market[ship[playerShipIndex].targetID].price[c];
					RemoveCargo( ship[playerShipIndex], c );
				}
				else
				{
					cout << "You have no " << market[ship[playerShipIndex].targetID].name[c] << " to sell." << endl;
				}
			}
			else
				cout << "You must be docked at a space station to buy and sell goods" << endl;
		}

		void StartNewGame( void )
		{
			srand((unsigned)time(0));

			CreateObjects();

			cout << "New game created." << endl;
			cout << "Please type 'help' for the list of commands." << endl << endl;
		}

		void StartSavedGame( void )
		{
			srand((unsigned)time(0));

			//to make sure not missing anything
			CreateObjects();

			LoadMarkets();
			LoadPorts();
			LoadShips(); //loads account also

			cout << "Previously saved game now loaded." << endl;
			cout << "Please type 'help' for the list of commands." << endl << endl;
		}

		void EndGame( void )
		{
			cout << endl << endl;

			cout << "Created by Darron Vanaria 03/22/08" << endl << endl;
		}
	}