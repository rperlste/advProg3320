/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 24, 2013
 * SSID:    101130094
 * Purpose: Assignment 5 - Bin Sort
 *          In this program, an input file is parsed, and the contents are
            sorted using bin sort.
 *****************************************************************************/
#ifndef _PA5FUNCTIONS_H
#define _PA5FUNCTIONS_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <iomanip>
#include <cstdlib>

/******************************************************************************
 >>>>>  namespace pa5functions pre/post conditions  <<<<<

class pa5_exception;
    Simple std::exception. Used to propogate errors.

struct StudentRecord;
    The data container.

void GreetUser();
    Prints a short summary of bin sort and this program.

void ReadInputFile( const char*,
                    RecordList& );
    Pre:    The pointer to the file name is no to 0
    Post:   Parses input file into string of student records.


void TokenizeString( std::string, 
                     std::list<std::string>&,
                     char );
    Tokenizes a string based on a delimiter. List copies string values.  


void BinSort( RecordList&,
                RecordList* );
    Pre:    The binList is valid.
    Post:   Sorts the inputs into 101 buckets, for a range of 101... 
            This is too simple.
            Seriously.

void PrintBinList( RecordList*,
                    unsigned );
    Pre:    The binList is valid.
    Post:   Prints the binList.

*******************************************************************************/

namespace pa5functions {

    // Classes and containers
    class pa5_exception : public std::exception {
    public:
        pa5_exception( std::string what ):_what(what) {}
        const char* what() { return _what.c_str(); }
        ~pa5_exception() throw() {}
    private:
        std::string _what;
    };
    struct StudentRecord{
        StudentRecord() {}
        StudentRecord( std::string name,
                       std::string ssn,
                       unsigned testScore )
                       :name(name),ssn(ssn),testScore(testScore) {}

        std::string name;
        std::string ssn;
        unsigned testScore;
    };
    typedef std::list<StudentRecord> RecordList;

    // namespace functions
    void GreetUser();
    void ReadInputFile( const char*,
                        RecordList& );
    void TokenizeString( std::string, 
                         std::list<std::string>&,
                         char );
    void BinSort( RecordList&,
                  RecordList* );
    void PrintBinList( RecordList*,
                       unsigned );

    // Constants
    const unsigned WIDTH = 15;

}


#endif