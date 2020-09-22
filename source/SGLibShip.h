#ifndef SGLIBSHIPS
#define SGLIBSHIPS

#include "SGLibPhysics.h"
#include "SGLibGlobal.h"

	namespace SGLib
	{
		struct Ship
		{
			int		ID;

			Point	position;
			Point	target;
			Vector	heading;
			Vector	velocity;
			int		cargo[numCommodities];
			double	fuel;
			bool	docked;
			int		targetID;

			int		shipClass;
			double	maxVelocityKMperS;
			double	maxVelocityKMperMS;
			int		cargoCapacity;
			double	fuelPerHour;
			double	fuelPerMS;
			double	fuelCapacity;
			double	autopilotRange;
			double	value;
		};

		void	CreateShip( Ship& s, int id, int classNum, Point pos, Point tar, int targetID );
		void	UpdateShipMS( Ship& s, long time );
		void	SetHeading( Ship& s );
		void	SetVelocityKMperS( Ship& s, double v );
		double	DistanceToTarget( Ship& s );
		double	CurrentVelocity( Ship& s );
		void	DockShip( Ship& s );
		void	SetTarget( Ship& s, int targetID, Point targetPOS );
		int		TotalCargo( Ship& ship );
		int		RemainingCargoSpace( Ship& ship );
		int		PercentCargoCapacity( Ship& ship );
		void	AddCargo( Ship& ship, int quantity, int commodity );
		void	RemoveCargo( Ship& ship, int commodity );
		double	RemainingFuelSpace( Ship& ship );
		void	AddFuel( Ship& ship, int quantity );
		std::ostream& operator<<( std::ostream& s, Ship& ship );
		std::istream& operator>>( std::istream& s, Ship& ship );
		void	LevelShip( Ship& s, int c );
	}

#endif