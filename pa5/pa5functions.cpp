/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 24, 2013
 * SSID:    101130094
 * Purpose: Assignment 5 - Bin Sort
 *          In this program, an input file is parsed, and the contents are
            sorted using bin sort.
 *****************************************************************************/
#include "pa5functions.h"


void pa5functions::GreetUser(){
    std::cout << "This program demonstrates the use of a bin sort.\n"
        << "Bin sort is desirable because the average case run time is\n"
        << "O(n+k), however the worst case is O(n^2).\n"
        << "The algorithm utilizes distributive sorting, a type of divide\n"
        << "and conquer where a collection is partitioned into small blocks\n"
        << "based on a range, and the blocks are sorted. The shortcoming\n"
        << "of the sort is that is memory inefficient.\n\n"
        << "Buckets are respresented as an array of linked lists.\n"
        << "In this program, k = range of the elements that will be sorted.\n\n"
        << "The purpose to read an input file of student records and test\n"
        << "scores, sort the student records by test score using bin sort,\n"
        << "and then output the sorted list.\n\n";
}

void pa5functions::ReadInputFile( const char* inputFile,
                                  RecordList& recordList ){
    // File validation
    std::fstream fin( inputFile );
    if( !fin ){
        throw pa5_exception( "Invalid input file." );
    }

    // Parse the file line by line and tokenize
    std::string currentLine;
    std::list<std::string> currentTokens;
    std::list<std::string>::iterator tokenIter;
    while( !fin.eof() ){
        currentLine.clear();
        currentTokens.clear();

        getline( fin, currentLine );
        // Handle poorly formed, but not invalid input input
        if( currentLine.size() == 0 ){
            continue;
        }
        TokenizeString( currentLine, currentTokens, ',' );
        if( currentTokens.size() != 3 ){
            throw pa5_exception( "Invalid input file - format or data error." );
        }

        tokenIter = currentTokens.begin();
        StudentRecord record;
        record.name      = *(tokenIter);
        record.ssn       = *(++tokenIter);
        record.testScore = atoi((*(++tokenIter)).c_str());

        // Normalize string length.
        record.name = record.name.substr(0,12);
        record.ssn = record.ssn.substr(0,9);

        recordList.push_back( record );
    }
    fin.close();
}

void pa5functions::TokenizeString( std::string toTokenize,
                                   std::list<std::string>& tokenList,
                                   char delimiter ){
    std::string currentToken;
    for( int i = 0; i < toTokenize.size(); ++ i ){
        if( toTokenize[i] == delimiter ){
            tokenList.push_back( currentToken );
            currentToken.clear();
        } else {
            currentToken += toTokenize[i];
        }
    }
    tokenList.push_back( currentToken );
}

void pa5functions::BinSort( RecordList& recordList, RecordList* bucketList ){
    for( RecordList::iterator it = recordList.begin();
         it != recordList.end();
         ++ it ){
             bucketList[it->testScore].push_back( (*it) );
    }
}

void pa5functions::PrintBinList( RecordList* bucketList, unsigned size ){
    std::cout << "Name           SSN            Score\n"
        << std::string( 35, '-' );
    for( int i = size-1; i >= 0; -- i ){
        for( RecordList::iterator it = bucketList[i].begin();
             it != bucketList[i].end();
             ++ it ){
                 std::cout << "\n"
                     << it->name << std::string( WIDTH - it->name.size(), ' ' )
                     << it->ssn  << std::string( WIDTH - it->ssn.size(), ' ' )
                     << it->testScore;
        }
    }
    std::cout << "\n";
}
