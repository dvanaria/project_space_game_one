#include "SGLibMarket.h"
#include "SGLibGlobal.h"

#include <string>	//for all strings
#include <iostream>	//for cin and cout objects
#include <ostream>	//for overloading << operator 
#include <cstdlib>	//for rand() and srand()
#include <ctime>	//for rand() and srand()
#include <fstream>	//to create ifstream and ofstream objects

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::ios;

namespace SGLib
{
	const double marketCapHigh	= 1.09;
	const double marketCapLow	= 0.91;

	struct Commodity
	{
		int		basePrice;
		int		fluxPrice;
		string	name;
	};

	Commodity commodity[numCommodities];

	void BuildCommodityBase( void )
	{
		commodity[organics].basePrice	= 73;
		commodity[computers].basePrice	= 186;
		commodity[robots].basePrice		= 497;

		commodity[organics].fluxPrice	= 1;
		commodity[computers].fluxPrice	= 2;
		commodity[robots].fluxPrice		= 3;

		commodity[organics].name		= "orgranics";
		commodity[computers].name		= "computers";
		commodity[robots].name			= "robots";
	}

	void CreateMarket( Market& m, char letterName, int idNum )
	{
		BuildCommodityBase();

		m.price[organics]	= commodity[organics].basePrice;
		m.price[computers]	= commodity[computers].basePrice;
		m.price[robots]		= commodity[robots].basePrice;

		m.name[organics]	= commodity[organics].name;
		m.name[computers]	= commodity[computers].name;
		m.name[robots]		= commodity[robots].name;

		m.letterOfMarket	= letterName;
		m.idNum				= idNum;
	}

	std::ostream& operator<<( std::ostream& s, Market& m )
	{
		s << m.letterOfMarket << "\t\t";

		int i;
		for( i=0; i<numCommodities; i++)
		{
			if( (m.price[i] - commodity[i].basePrice) < 0 )
				s << (m.price[i] - commodity[i].basePrice) << "\t\t";
			else
				s << "+" << (m.price[i] - commodity[i].basePrice) << "\t\t";
		}

		s << endl;

		return s;
	}
		
	std::istream& operator>>( std::istream& s, Market& m )
	{
		s >> m.letterOfMarket;

		int i;
		for( i=0; i<numCommodities; i++)
		{
			s >> m.price[i];

			m.price[i] += commodity[i].basePrice;
		}

		return s;
	}

	void UpdateMarket( Market& m )
	{
		int j;

		for( j=0; j<numCommodities; j++ )
		{
			if( rand()%2 == 1 )
				m.price[j] += ((rand()%commodity[j].fluxPrice) + 1);
			else
				m.price[j] -= ((rand()%commodity[j].fluxPrice) + 1);

			if( m.price[j] > (commodity[j].basePrice * marketCapHigh) )
				m.price[j] = (commodity[j].basePrice * marketCapHigh);
			else 
			if( m.price[j] < ((commodity[j].basePrice * marketCapLow)) )
				m.price[j] = (commodity[j].basePrice * marketCapLow);
		}
	}	

	void RollMarket100Turns( Market& m )
	{
		int i;
		for( i=0; i<100; i++)
			UpdateMarket( m );
	}
}

