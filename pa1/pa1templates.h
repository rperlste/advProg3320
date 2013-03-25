/*
 *    Robert Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    HW1 - Newton and Secant Functions
 *    
 *    This program uses the Newton Method to calculate the root
 *    of the eqation: e^x - 1.5 - atan(x)
 *    It will also use the Secant Method to calculate the root
 *    of the equation: x^3 - sinh(x) + 4x^2 + 6x + 9
 */

/*************************** PRE/POST CONDITIONS *****************************

template<typename T> T    NewtonFunction( const T& x );
PRE:    The template parameter is castable to double or float.
POST:    Returns the value of the function e^x - 1.5 - atan(x)

template<typename T> T                SecantFunction( const T& x );
PRE:    The template parameter is castable to double or float.
POST:    Return the value of function x^3 - sinh(x) + 4x^2 + 6x + 9

template<typename T> T                NewtonFunctionDerivative( const T& x );
PRE:    The template parameter is castable to double or float.
POST:    Returns the value of the function e^x - ( 1 / ( x^2 + 1 )

template<typename T> void            Swap( T* t1, T* t2 );
PRE:    Class T utilizes the assignment operator.
POST:    Swaps the values of t1 and t2.

template<typename T> void            NewtonsMethod ( 
                                        T x0, 
                                        const T MAX,
                                        const T DELTA,
                                        const T EPSILON );
PRE:    The template parameter is castable to double or float.
POST:    Loads a linked list with values that will determine the functions root value.

template<typename T> void            SecantMethod (
                                        T a,
                                        T b,
                                        const T MAX,
                                        const T DELTA,
                                        const T EPSILON ));
PRE:    The template parameter is castable to double or float.
POST:    Loads a linked list with values that will determine the functions root value.

******************************************************************************/

#ifndef _pa1templates
#define _pa1templates

#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <list>
#include <cstdlib>

namespace pa1templates {

    typedef std::pair<double,double>    OutputPair;
    typedef std::list<OutputPair>        OutputList;
    typedef OutputList::iterator        ListIterator;

    template<typename T> T                NewtonFunction( const T& x );
    template<typename T> T                SecantFunction( const T& x );
    template<typename T> T                NewtonFunctionDerivative( const T& x );
    template<typename T> void            Swap( T* t1, T* t2 );
    template<typename T> OutputList        NewtonsMethod ( 
                                            T x0, 
                                            const T MAX,
                                            const T DELTA,
                                            const T EPSILON );
    template<typename T> OutputList        SecantMethod (
                                            T a,
                                            T b,
                                            const T MAX,
                                            const T DELTA,
                                            const T EPSILON );
}

#include "pa1templates.tem"

#endif