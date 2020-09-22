#ifndef SGLIBPORT_H
#define SGLIBPORT_H

#include <string>
#include "SGLibPhysics.h"

using std::string;

	namespace SGLib
	{
		struct Port
		{
			Point	position;
			Vector	velocity;
			string	name;
			char	letterName;
			int		idNum;
		};

		void CreatePort( Port& p, string name, int letterName, int idNum );
		std::ostream& operator<<( std::ostream& s, Port& p );
		std::istream& operator>>( std::istream& s, Port& p );
	}

#endif
