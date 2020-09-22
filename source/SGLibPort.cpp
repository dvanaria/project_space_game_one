#include "SGLibPort.h"
#include "SGLibGlobal.h"

#include <iomanip>
#include <istream>
#include <ostream>

using std::left;
using std::setw;
using std::endl;

namespace SGLib
{
	void LocatePort( Port& p )
	{
		p.position.x = BigRand();
		p.position.y = BigRand();
		p.position.z = BigRand();

		p.velocity.x = 0;
		p.velocity.y = 0;
		p.velocity.z = 0;
	}

	void CreatePort( Port& p, string name, int letterName, int idNum )
	{
		LocatePort( p );

		p.name			= name;
		p.letterName	= letterName;
		p.idNum			= idNum;
	}

	std::ostream& operator<<( std::ostream& s, Port& p )
	{
		s << left << setw(15) << p.letterName;
		s << left << setw(15) << p.idNum;
		s << left << setw(15) << FormatDouble2(p.position.x);
		s << left << setw(15) << FormatDouble2(p.position.y);
		s << left << setw(15) << FormatDouble2(p.position.z);
		s << left << setw(15) << FormatDouble2(p.velocity.x);
		s << left << setw(15) << FormatDouble2(p.velocity.y);
		s << left << setw(15) << FormatDouble2(p.velocity.z);
		s << left << setw(15) << p.name << endl;

		return s;
	}

	std::istream& operator>>( std::istream& s, Port& p )
	{
		s >> p.letterName;
		s >> p.idNum;
		s >> p.position.x;
		s >> p.position.y;
		s >> p.position.z;
		s >> p.velocity.x;
		s >> p.velocity.y;
		s >> p.velocity.z;
		s >> p.name;

		return s;
	}
}
