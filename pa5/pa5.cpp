/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 24, 2013
 * SSID:    101130094
 * Purpose: Assignment 5 - Bin Sort
 *          In this program, an input file is parsed, and the contents are
            sorted using bin sort.
 *****************************************************************************/

#include "pa5functions.h"

int main( int argc, const char* argv[] ){

    if( argc < 2 ){
        std::cerr << "Too few arguments passed.";
        return 1;
    }

    // Instance record input list, and array of lists (the bins).
    pa5functions::RecordList studentRecords;
    pa5functions::RecordList binList[101];
     
    try{
        // Run the pa5functions
        pa5functions::GreetUser();
        pa5functions::ReadInputFile( argv[1], studentRecords );
        pa5functions::BinSort( studentRecords, binList );
        pa5functions::PrintBinList( binList, 101 );
    } catch ( pa5functions::pa5_exception e ){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}