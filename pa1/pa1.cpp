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

#include <cstdlib>
#include <iostream>
#include "pa1functions.h"

int main(){

    pa1functions::PrintGreeting();
    pa1functions::Run();

    return EXIT_SUCCESS;
}