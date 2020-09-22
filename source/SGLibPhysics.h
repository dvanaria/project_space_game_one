#ifndef SGLIBPHYSICS_H
#define SGLIBPHYSICS_H

	namespace SGLib
	{
		struct Point
		{
			double x;
			double y;
			double z;
		};

		struct Vector
		{
			double x;
			double y;
			double z;
		};
	
		Vector CreateVectorAtoB( Point a, Point b );

		Vector CreateVectorAtoB( Vector a, Vector b );
		
		double VectorMagnitude( Vector j );

		double Distance( Point p1, Point p2 );

		Vector NormalizeVector( Vector V );

		Vector ScaleVector( Vector V, double s );

		Vector CurbVector( Vector V, double mag );
	} 

#endif
