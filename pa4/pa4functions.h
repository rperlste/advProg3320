/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 15, 2013
 * SSID:    101130094
 * Purpose: Assignment 4 - Hash Table and Club Dues
            In this program, two input files are read, parsed, loaded into
            hash tables, and then extracted for outputs via cout and output
            to a file.
 
 ****** PRE / POST CONDITIONS **************************************************

 class pa4exception 
 Simple exception implementation used for progating errors.

void GreetUser();
PRE:    None
POST:   Prints a short message about the purpose of hash tables and the
        purpose of the program.

void ReadInput( const char*,
                const char*,
                StudentRecordTable&,
                CompensationRateTable& );
PRE:    None
POST:   Attempts to open the input files, reports errors if any exist.
        Then populates the student records and the compensation rates tables.

void CalculateAndOutputDues( const char*,
                                StudentRecordTable&,
                                CompensationRateTable& );
PRE:    None
POST:   Outputs the dues owed to std::cout and to the output file.

void OstreamOutput( std::ostream&,
                    StudentRecordTable&,
                    CompensationRateTable& );
PRE:    None
POST:   Outputs a formatted table of membership dues to ostream.

 *****************************************************************************/


#ifndef _PA4_FUNCTIONS_H
#define _PA4_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <utility>
#include <exception>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "hash.h"

namespace pa4functions {

    class pa4exception : public std::exception {
    public:
        pa4exception( std::string what ):_what(what){}
        const char* what() { return _what.c_str(); }
        ~pa4exception() throw() {}
    private:
        std::string _what;
    };

    struct StudentRecord {
        std::string name;
        float monthlyParticipation[12];
        float yearlyDues;
    };

    typedef HashTable<std::string, StudentRecord> StudentRecordTable;
    typedef HashTable<float, float> CompensationRateTable;

    const unsigned DEC_PRECISION = 1;
    const unsigned COUT_WIDTH = 6;

    void GreetUser();
    void ReadInput( const char* ,
                    const char*,
                    StudentRecordTable&,
                    CompensationRateTable& );
    void CalculateAndOutputDues( const char*,
                                 StudentRecordTable&,
                                 CompensationRateTable& );
    void OstreamOutput( std::ostream&,
                        StudentRecordTable&,
                        CompensationRateTable& );
}

#endif
