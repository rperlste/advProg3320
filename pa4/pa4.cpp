/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 15, 2013
 * SSID:    101130094
 * Purpose: Assignment 4 - Hash Table and Club Dues
 *          In this program, two input files are read, parsed, loaded into
 *          hash tables, and then extracted for outputs via cout and output
 *          to a file.
 *****************************************************************************/

#include "pa4functions.h"
#include "hash.h"

unsigned hash( const int& i ){
    return 0;
}

int main( int argc, const char* argv[] ){
    if( argc < 4 ){
        std::cerr << "\nInsufficient argument quantity.\n";
        return 1;
    }
    pa4functions::StudentRecordTable studentRecordTable;
    pa4functions::CompensationRateTable membershipCostTable;
    pa4functions::GreetUser();
    try{
        pa4functions::ReadInput( argv[1], 
                                 argv[2], 
                                 studentRecordTable, 
                                 membershipCostTable );
        pa4functions::CalculateAndOutputDues( argv[3], 
                                              studentRecordTable, 
                                              membershipCostTable );
    } catch ( pa4functions::pa4exception e ){
        std::cerr << "\n" << e.what() << "\n";
        return 1;
    }
    return 0;
}