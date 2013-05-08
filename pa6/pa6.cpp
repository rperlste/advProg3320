/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    May 6, 2013
 * SSID:    101130094
 * Purpose: Assignment 6 - Text Editor
 *          This is a simple line editor. It allows for the manipulation
 *****************************************************************************/


#include "pa6functions.h"

int main( int argc, const char* argv[] ){
    
    pa6functions::GreetUser();

    // Get filename from either command line or cin
    std::string filename;
    if( argc < 2 ){
        pa6functions::GetFilename( filename );
    } else {
        filename = argv[1];
    }

    // Run the text editor
    try{
        pa6functions::RunTextEditor( filename );
    } catch ( pa6functions::pa6exception e ){
        std::cerr << "\n\n" << e.what() << "\n\n";
    } catch ( std::bad_alloc e ){
        std::cerr << "\n\n" << e.what() << "\n\n";
    }

    return 0;
} 