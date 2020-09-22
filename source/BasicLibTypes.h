//BasicLibTypes.h
//This file contains basic types and constants

#ifndef BASICLIBTYPES_H
#define BASICLIBTYPES_H

	#include <iostream>
	#include <fstream>
	#include <string>


	namespace BasicLib
	{
		// --1-- //
		//Define GOODCOMPILER or CRAPPYCOMPILER: to distinguish between MSVC++6 and MSVC++7
		//	MSVC++6 has issue with streaming 64-bit integers to/from streams.
		//	This define is used in many other files where MSVC++6 would cause problems.
		#ifdef WIN32
			#if _MSC_VER >= 1300
				#define GOODCOMPILER
			#else
				#define CRAPPYCOMPILER
			#endif
		#endif

		#ifdef __GNUC__
			#define GOODCOMPILER
		#endif

		// --2-- //
		//Define 8, 16, 32. and 64 bit integers:
		//(64-bit ints are useful for ms timers that will run for a long time - covers 
		// 292 million years)
		//	sint8
		//	uint8
		//  sint16
		//  uint16
		//  sint32
		//  uint32
		//  sint64
		//  uint64
		typedef signed char					sint8;
		typedef unsigned char				uint8;
		typedef signed short int			sint16;
		typedef unsigned short int			uint16;
		typedef signed long int				sint32;
		typedef unsigned long int			uint32;		
		//GCC
		#ifdef __GNUC__
			typedef long long int			sint64;
			typedef unsigned long long int	uint64;
		#endif
		//Visual C++
		#ifdef WIN32
			typedef __int64					sint64;
			typedef unsigned __int64		uint64;
		#endif

		// --3-- //
		//Common constants
		const double pi = 3.1415926535897932384626433832795;

	}
	//end namespace BasicLib

#endif

