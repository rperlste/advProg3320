/*
 *	Robert Perlstein
 *	101130094
 *	Advanced Programming
 *	Spring 2013
 *	HW1 - Newton and Secant Functions
 *	
 *	This program uses the Newton Method to calculate the root
 *	of the eqation: e^x - 1.5 - atan(x)
 *	It will also use the Secant Method to calculate the root
 *	of the equation: x^3 - sinh(x) + 4x^2 + 6x + 9
 */

/*************************** PRE/POST CONDITIONS *****************************
							

void	PrintGreeting();
PRE:	None
POST:	Prints a greeting and program summary via std::cout

int		Run();
PRE:	None
POST:	Runs the two methods and prints the outputs

int		PrintTables();
PRE:	None
POST:	Prints the tables for both the Newton and Secant methods, the last values
		represent the approximate root. If no values exist for the tables, prints
		a small error message and aborts the program.

******************************************************************************/

#ifndef _pa1functions
#define _pa1functions

#include "pa1templates.h"

namespace pa1functions {
	
	using namespace pa1templates;

	static OutputList					newtonOutput;
	static OutputList					secantOutput;

	// OUTPUT CONSTANTS
	const int							TABLE_MARGIN = 2;
	const int							TABLE_WIDTH = 30;
	const int							TABLE_DIVIDER_WIDTH = 80;
	const int							PRECISION = 8;

	// NEWTON CONSTANTS
	const double						NEWTON_DELTA = std::pow( 10.0, -6.0 );
	const double						NEWTON_EPSILON = std::pow( 10.0, -6.0 );
	const double						NEWTON_MAX = 100.0;
	const double						NEWTON_X0 = 1.0;

	// SECANT CONSTANTS
	const double						SECANT_A = 6.0;
	const double						SECANT_B = 9.0;
	const double						SECANT_DELTA = std::pow( 10.0, -6.0 );
	const double						SECANT_EPSILON = std::pow( 10.0, -6.0 );
	const double						SECANT_MAX = 100.0;

	void								PrintGreeting();
	int									Run();
	int									PrintTables();

}

#endif