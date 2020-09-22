#ifndef SGLIBGLOBAL_H
#define SGLIBGLOBAL_H

#include <string>

#include "BasicLibTime.h"

using std::string;
using namespace BasicLib;

	namespace SGLib
	{
		const int		organics				= 0;
		const int		computers				= 1;
		const int		robots					= 2;
		const int		fuel					= 3;
		const int		ships					= 4;
		const int		numCommodities			= 3;
		const double	radiusReal				= 150000000;
		const double	radiusMap				= 10;
		const int		diameterMap				= 20;
		const int		numShips				= 1;
		const int		numPorts				= 10;
		const int		numMarkets				= 10;
		const double	fps						= 50;
		const double	looplockMS				= (1/fps) * 1000;
		const double	gametimeMultiplier		= 60;
		const double	gametimeLoopValueMS		= looplockMS * gametimeMultiplier;
		const double	autopilotMultiplier		= 1.5;
		const int		startShipsAtIndex		= 12;
		const int		shipArraySize			= startShipsAtIndex + numShips;
		const int		playerShipIndex			= startShipsAtIndex + 0;
		const double	priceFuel				= 47.99;

		const int		FPS						= 50;
		const int		MSperFRAME				= (int)(((double)1/(double)FPS) * 1000);

		std::string FormatDouble2( double x );

		double BigRand( void );

		string FormatDoubleWithCommas( double d );

		double SintoHrs( double s );

		double SintoMin( double s );
	}

#endif