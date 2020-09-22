#ifndef SGLIBBOARD_H
#define SGLIBBOARD_H

#include "SGLibShip.h"
#include "SGLibPort.h"
#include "SGLibMarket.h"
#include "SGLibGlobal.h"

	namespace SGLib
	{
		void CreateObjects( void );
		void SaveMarkets( void );
		void LoadMarkets( void );
		void SavePorts( void );
		void LoadPorts( void );
		void SaveShips( void );
		void LoadShips( void );
		int  ConvertRealToMapX( double x );
		int  ConvertRealToMapY( double y );
		void MapCommand( void );
		void MarketCommand( void );
		void BuildTargetList( void );
		void TargetCommand( void );
		void HelpCommand( void );
		void StatusCommand( void );
		void AutopilotUpdateShip( int ms, Ship& ship, Port& port );
		void DockCommand( void );
		void TargetXCommand( char ID );
		void StartNewGame( void );
		void StartSavedGame( void );
		void EndGame( void );
		void UpdateObjects( void );
		void BuyCommand( int c );
		void SellCommand( int c );
	}

#endif






