#include "SGLibPhysics.h"
#include "SGLibShip.h"

#include <iomanip>
#include <istream>
#include <ostream>

using std::left;
using std::setw;
using std::endl;

using namespace std;



namespace SGLib
{
	void CreateShip( Ship& s, int id, int classNum, Point pos, Point tar, int targetID )
	{
		s.ID = id;

		LevelShip( s, classNum );

		s.position = pos;
		s.target = tar;
		s.targetID = targetID;
		SetHeading( s );
		SetVelocityKMperS( s, 0 );
		int i;
		for( i=0; i<numCommodities; i++ )
			s.cargo[i] = 0;
		s.fuel = (double)(rand()%(int)s.fuelCapacity);
		DockShip( s );
	}

	void UpdateShipMS( Ship& s, long time )
	{
		//Think of a Ship as a mechanical windup toy:
		//You wind it up (AddFuel)
		//point it in the direction you want it to go (SetTarget)
		//and then let it take care of itself (UpdateShipMS) = move itself, reduce fuel, stop if out of fuel
		if( VectorMagnitude( s.velocity ) > 0 )
		{
			//use Newton's laws to update position x1 = x0 + v0t (constant velocity = no acceleration)
			double t = (double)time / 1000;
			s.position.x = s.position.x + (s.velocity.x * t);
			s.position.y = s.position.y + (s.velocity.y * t);
			s.position.z = s.position.z + (s.velocity.z * t);

			if( !s.docked )
			{
				//use up fuel units
				s.fuel -= (s.fuelPerMS * time);

				if( s.fuel < 0 )
				{
					//out of fuel
					if( VectorMagnitude( s.velocity ) > 0 )
					{
						cout << endl;
						cout << "You have run out of fuel!" << endl << endl;
						cout << ">";
					}

					s.fuel = 0;
					SetVelocityKMperS( s, 0 );
				}
			}
		}
	}

	void SetHeading( Ship& s )
	{
		s.heading = CreateVectorAtoB( s.position, s.target );
	}

	void SetVelocityKMperS( Ship& s, double v )
	{
		if( v > s.maxVelocityKMperS )
			v = s.maxVelocityKMperS;

		s.velocity = CurbVector( s.velocity, v );
	}
	
	double DistanceToTarget( Ship& s )
	{
		return VectorMagnitude( s.heading );
	}

	double CurrentVelocity( Ship& s )
	{
		return VectorMagnitude( s.velocity );
	}

	void DockShip( Ship& s )
	{
		s.docked = true;

		s.velocity = CurbVector( s.velocity, 0 );

		s.position = s.target;

		SetHeading( s );
	}

	void SetTarget( Ship& s, int targetID, Point targetPOS )
	{
		s.docked = false;

		s.target = targetPOS;//maybe this isn't needed...

		s.targetID = targetID;

		//Autopilot will adjust velocity
		//UpdateShip will use fuel, etc.
	}

	int TotalCargo( Ship& ship )
	{
		int total = 0;

		int i;
		for( i=0; i<numCommodities; i++ )
			total += ship.cargo[i];

		return total;
	}

	int RemainingCargoSpace( Ship& ship )
	{
		return ship.cargoCapacity - TotalCargo( ship ); 
	}

	int PercentCargoCapacity( Ship& ship )
	{
		int total = TotalCargo( ship );
		int cap = ship.cargoCapacity;

		double percent = (double)total / (double)cap;

		return (int)(percent * 100);
	}

	void AddCargo( Ship& ship, int quantity, int commodity )
	{
		if( (TotalCargo(ship) + quantity) > ship.cargoCapacity )
			quantity = ship.cargoCapacity - TotalCargo(ship);

		ship.cargo[commodity] += quantity;
	}

	void RemoveCargo( Ship& ship, int commodity )
	{
		ship.cargo[commodity] = 0;
	}

	double RemainingFuelSpace( Ship& ship )
	{
		//round off after the subtraction:
		//12 capacity, fuel = 6.2?  
		//	12 - 6.2 = 5.8
		// (int) = 5
		return ship.fuelCapacity - ship.fuel;	
	}

	void AddFuel( Ship& ship, int quantity )
	{
		if( quantity > ship.fuelCapacity )
			quantity = ship.fuelCapacity;

		ship.fuel += quantity;
	}

	std::ostream& operator<<( std::ostream& s, Ship& ship )
	{
		s << ship.ID;
		s << "\t" << FormatDouble2(ship.position.x);
		s << "\t" << FormatDouble2(ship.position.y);
		s << "\t" << FormatDouble2(ship.position.z);	
		s << "\t" << FormatDouble2(ship.target.x);
		s << "\t" << FormatDouble2(ship.target.y);
		s << "\t" << FormatDouble2(ship.target.z);
		s << "\t" << FormatDouble2(ship.heading.x);
		s << "\t" << FormatDouble2(ship.heading.y);
		s << "\t" << FormatDouble2(ship.heading.z);	
		s << "\t" << FormatDouble2(ship.velocity.x);
		s << "\t" << FormatDouble2(ship.velocity.y);
		s << "\t" << FormatDouble2(ship.velocity.z);
		int i;
		for( i=0; i<numCommodities; i++ )
			s << "\t" << ship.cargo[i];
		s << "\t" << ship.fuel;
		s << "\t" << ship.docked;
		s << "\t" << ship.targetID;

		s << "\t" << ship.shipClass;
		s << "\t" << FormatDouble2(ship.maxVelocityKMperS);
		s << "\t" << FormatDouble2(ship.maxVelocityKMperMS);
		s << "\t" << ship.cargoCapacity;
		s << "\t" << ship.fuelPerHour;
		s << "\t" << ship.fuelPerMS;
		s << "\t" << ship.fuelCapacity;
		s << "\t" << FormatDouble2(ship.autopilotRange);
		s << "\t" << FormatDouble2(ship.value);

		return s;
	}

	std::istream& operator>>( std::istream& s, Ship& ship )
	{
		s >> ship.ID;
		s >> ship.position.x;
		s >> ship.position.y;
		s >> ship.position.z;	
		s >> ship.target.x;
		s >> ship.target.y;
		s >> ship.target.z;
		s >> ship.heading.x;
		s >> ship.heading.y;
		s >> ship.heading.z;	
		s >> ship.velocity.x;
		s >> ship.velocity.y;
		s >> ship.velocity.z;
		int i;
		for( i=0; i<numCommodities; i++ )
			s >> ship.cargo[i];
		s >> ship.fuel;
		s >> ship.docked;
		s >> ship.targetID;

		s >> ship.shipClass;
		s >> ship.maxVelocityKMperS;
		s >> ship.maxVelocityKMperMS;
		s >> ship.cargoCapacity;
		s >> ship.fuelPerHour;
		s >> ship.fuelPerMS;
		s >> ship.fuelCapacity;
		s >> ship.autopilotRange;
		s >> ship.value;

		return s;
	}

	void LevelShip( Ship& s, int c )
	{
		double maxJumpPerLoopKM;

		s.shipClass = c;
		
		if( c==1 )
		{
			s.maxVelocityKMperS		= 38973;
			s.maxVelocityKMperMS	= s.maxVelocityKMperS / 1000;
			s.cargoCapacity			= 23;
			s.fuelPerHour			= 2;
			s.fuelPerMS				= s.fuelPerHour / 60 / 60 / 1000;
			s.fuelCapacity			= 14;
			maxJumpPerLoopKM		= s.maxVelocityKMperMS * gametimeLoopValueMS;
			s.autopilotRange		= maxJumpPerLoopKM * autopilotMultiplier;			
			s.value					= 47220;
		}

		if( c==2 )
		{
			s.maxVelocityKMperS		= 32977;
			s.maxVelocityKMperMS	= s.maxVelocityKMperS / 1000;
			s.cargoCapacity			= 46;
			s.fuelPerHour			= 3;
			s.fuelPerMS				= s.fuelPerHour / 60 / 60 / 1000;
			s.fuelCapacity			= 24;
			maxJumpPerLoopKM		= s.maxVelocityKMperMS * gametimeLoopValueMS;
			s.autopilotRange		= maxJumpPerLoopKM * autopilotMultiplier;
			s.value					= 89718;
		}

		if( c==3 )
		{
			s.maxVelocityKMperS		= 26981;
			s.maxVelocityKMperMS	= s.maxVelocityKMperS / 1000;
			s.cargoCapacity			= 92;
			s.fuelPerHour			= 4;
			s.fuelPerMS				= s.fuelPerHour / 60 / 60 / 1000;
			s.fuelCapacity			= 40;
			maxJumpPerLoopKM		= s.maxVelocityKMperMS * gametimeLoopValueMS;
			s.autopilotRange		= maxJumpPerLoopKM * autopilotMultiplier;
			s.value					= 170464;
		}

		if( c==4 )
		{
			s.maxVelocityKMperS		= 20985;
			s.maxVelocityKMperMS	= s.maxVelocityKMperS / 1000;
			s.cargoCapacity			= 184;
			s.fuelPerHour			= 5;
			s.fuelPerMS				= s.fuelPerHour / 60 / 60 / 1000;
			s.fuelCapacity			= 69;
			maxJumpPerLoopKM		= s.maxVelocityKMperMS * gametimeLoopValueMS;
			s.autopilotRange		= maxJumpPerLoopKM * autopilotMultiplier;
			s.value					= 323882;
		}

		if( c==5 )
		{
			s.maxVelocityKMperS		= 14990;
			s.maxVelocityKMperMS	= s.maxVelocityKMperS / 1000;
			s.cargoCapacity			= 368;
			s.fuelPerHour			= 6;
			s.fuelPerMS				= s.fuelPerHour / 60 / 60 / 1000;
			s.fuelCapacity			= 117;
			maxJumpPerLoopKM		= s.maxVelocityKMperMS * gametimeLoopValueMS;
			s.autopilotRange		= maxJumpPerLoopKM * autopilotMultiplier;
			s.value					= 615376;
		}
	}
}

