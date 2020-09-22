#include <string>		//for all strings
#include <iostream>		//for stringstream/showpoint/setprecistion
#include <iomanip>		//for stringstream/showpoint/setprecistion
#include <sstream>		//for stringstream/showpoint/setprecistion
#include <cstdlib>		//for rand() and srand() and RAND_MAX
#include <ctime>  		//for rand() and srand()

#include "SGLibGlobal.h"

using std::string;
using std::fixed;
using std::setprecision;
using std::showpoint;
using std::ostringstream;

namespace SGLib
{
	std::string FormatDouble2( double x )
	{
		std::stringstream str;

		str << std::fixed << std::showpoint << std::setprecision(2) << x;

		return str.str();
	}

	double BigRand( void )
	{
		int random_integer;
		double BIG_RAND_MAX		= radiusReal;
		double factor			= BIG_RAND_MAX / RAND_MAX; 

		random_integer = rand();

		if( rand()%2 == 1 )
			random_integer *= -1;

		return ((double)random_integer * factor);
	}

	string FormatDoubleWithCommas( double d )
	{
		ostringstream stm;
		stm << fixed << setprecision(0) << d;
		string str = stm.str();
		int n = str.size();
		for( int i=n-3; i>0; i-=3 )
			str.insert( i, 1, ',' );

		return str;
	}

	double SintoHrs( double s )
	{
		//how many minutes?
		s = s/60;

		//how many hours?
		s = s/60;

		return s;
	}

	double SintoMin( double s )
	{
		//how many minutes?
		s = s/60;

		return s;
	}
}