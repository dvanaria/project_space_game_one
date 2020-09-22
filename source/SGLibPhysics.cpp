#include <stdio.h>	//for sqrt
#include <math.h>	//for sqrt

#include "SGLibPhysics.h"

namespace SGLib
{
		Vector CreateVectorAtoB( Point a, Point b )
		{
			//The definition of a vector is "the displacement from point a to point b"
			Vector c;

			c.x = b.x - a.x;
			c.y = b.y - a.y;
			c.z = b.z - a.z;

			return c;
		}

		Vector CreateVectorAtoB( Vector a, Vector b )
		{
			//this version of CreateVectorAtoB uses Vectors as points
			Vector c;

			c.x = b.x - a.x;
			c.y = b.y - a.y;
			c.z = b.z - a.z;

			return c;
		}
		
		double VectorMagnitude( Vector j )
		{
			//uses pythagorean theorem to find magnitude
			double result;

			result = sqrt( ((j.x*j.x) + (j.y*j.y) + (j.z*j.z)) );

			return result;
		}

		double Distance( Point p1, Point p2 )
		{
			Vector v = CreateVectorAtoB( p1, p2 );

			return VectorMagnitude( v );
		}

		Vector NormalizeVector( Vector V )
		{
			//"to normalize" means to alter a vector's components so that the length of the vector = 1
			
			//To do this, scale the vector by the inverse of it's length
			double length = VectorMagnitude( V );
			
			if (length != 0)
				length = 1 / length;

			V.x = V.x * length;
			V.y = V.y * length;
			V.z = V.z * length;

			return V;
		}

		Vector ScaleVector( Vector V, double s )
		{
			//to scale a vector, multiply each of it's components by s
			V.x = V.x * s;
			V.y = V.y * s;
			V.z = V.z * s;

			return V;
		}

		Vector CurbVector( Vector V, double mag )
		{
			//by "curb" I mean to scale this vector so that it's new magnitude is "mag"
			//To do this, first normalize V, then scale it by mag
			V = NormalizeVector( V );
			V = ScaleVector( V, mag );

			return V;
		}
}