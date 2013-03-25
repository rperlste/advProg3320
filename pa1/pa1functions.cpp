#include "pa1functions.h"


void pa1functions::PrintGreeting(){
    std::cout   << "\n\nThis program finds the roots of non-linear equations"
                << "\nutilizing both Newton's Method and the Secant Method."
                << "\n\nNewton's Method will be used to find the root of the equation:"
                << "\ne^x - 1.5 - atan(x)"
                << "\n\nThe Secant Method will be used to find the root of the equation:"
                << "\nx^3 - sinh(x) + 4x^2 + 6x + 9\n\n";
}

int pa1functions::Run(){

    // Ensure the lists are empty.
    newtonOutput.clear();
    secantOutput.clear();

    // Find roots of non-linear equations
    newtonOutput = NewtonsMethod( NEWTON_X0, 
                                  NEWTON_MAX, 
                                  NEWTON_DELTA, 
                                  NEWTON_EPSILON );
    secantOutput = SecantMethod(  SECANT_A, 
                                  SECANT_B, 
                                  SECANT_MAX, 
                                  SECANT_DELTA, 
                                  SECANT_EPSILON );
    
    // Print table, return error code if one occurs
    if( pa1functions::PrintTables() == EXIT_FAILURE )
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int pa1functions::PrintTables(){
    // Validate the lists have data
    if ( newtonOutput.empty() || secantOutput.empty() ){
        std::cout << "\nThere was an error reading the data.";
        return EXIT_FAILURE;
    }

    std::cout << std::setprecision( PRECISION );

    // Newton Method
    std::cout << "\nNewton's Method"
        << "\n" << std::setw( TABLE_MARGIN ) << "k" << std::setw( TABLE_WIDTH ) 
        << "x_i" << std::setw( TABLE_WIDTH )
        << "f(x)"
        << "\n" << std::string( TABLE_DIVIDER_WIDTH, '-' );

    int k = 0;
    for ( ListIterator it = newtonOutput.begin(); it != newtonOutput.end(); ++ it, ++ k ){
        std::cout << "\n" << std::setw( TABLE_MARGIN ) << k << std::setw( TABLE_WIDTH )
            << it->first << std::setw( TABLE_WIDTH )
            << it->second << std::setw( TABLE_WIDTH );
    }

    // Secant Method
    std::cout << "\n\n\nSecant Method" 
        << "\n" << std::setw( TABLE_MARGIN ) << "k" << std::setw( TABLE_WIDTH ) 
        << "a" << std::setw( TABLE_WIDTH )
        << "f(a)" << "\n"
        << std::string( TABLE_DIVIDER_WIDTH, '-' );

    k = 0;
    for ( ListIterator it = secantOutput.begin(); it != secantOutput.end(); ++ it, ++ k ){
        std::cout << "\n" << std::setw( TABLE_MARGIN ) << k << std::setw( TABLE_WIDTH )
            << it->first << std::setw( TABLE_WIDTH )
            << it->second << std::setw( TABLE_WIDTH );
    }

    std::cout << "\n\n";

    return EXIT_SUCCESS;
}
