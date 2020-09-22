#ifndef SGLIBMARKET_H
#define SGLIBMARKET_H

#include <string>
#include "SGLibGlobal.h"

using std::string;

namespace SGLib
{
	struct Market
	{
		int		price[numCommodities];
		string	name[numCommodities];
		char	letterOfMarket;  
		int		idNum;
	};

	void CreateMarket( Market& m, char letterName, int idNum );
	void UpdateMarket( Market& m );
	void RollMarket100Turns( Market& m );
	std::ostream& operator<<( std::ostream& s, Market& m );		
	std::istream& operator>>( std::istream& s, Market& m );
}

#endif