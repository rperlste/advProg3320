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

void pa4functions::GreetUser(){
    std::cout 
        << "\nThis program utilizes a hash table to store data that has been"
        << "\nparsed from two seperate input files, then access the data"
        << "\nto print an output."
        << "\n\nA hash table is a data structure that uses an array to store"
        << "\nkey/value pairs. The array indexes are determined by a hashing"
        << "\nalgorithm which computes an offset based on the key value."
        << "\nThe goal is evenly distribute the data across the hash table,"
        << "\nthus minimizing collisions. Collisions still happen, and to"
        << "\nresolve this a number of methods can be used. One such method"
        << "\nis to recompute the address, taking into account that the"
        << "\ninitial hash address was invalid. The approach used in the"
        << "\nhash table implemented for this program is called \"chaining\"."
        << "\nChaining allows the table to grow to a large size by linking"
        << "\nany collisions using a simplified linked list."
        << "\n\nThe program reads data that represents the number of"
        << "\nvolunteer hours various members of a group have given each month,"
        << "\nand prints an output of the amount of group dues based on their"
        << "\ncontributions.\n\n";
}

void pa4functions::ReadInput( const char* memberVolunteerTime,
                              const char* compensationRates,
                              StudentRecordTable& recordTable,
                              CompensationRateTable& membershipCostTable ){

    // Open and verify files.
    std::fstream mvtFile( memberVolunteerTime );
    if( !mvtFile ){
        throw pa4exception( "Invalid member volunteer hours input file." );
    }
    std::fstream crFile( std::string(compensationRates).c_str() );
    if( !crFile ){
        throw pa4exception( "Invalid compensation rate input file." );
    }

    // Extract the student names and monthly contributions
    std::stringstream currentLine;
    std::string currentToken;
    while( !mvtFile.eof() ){

        // Extract line and begin tokenizing
        currentLine.clear();
        StudentRecord studentRecord;
        getline( mvtFile, currentToken );
        currentLine << currentToken;
        getline( currentLine, currentToken, ' ' );

        // Test for name
        if( atoi( currentToken.c_str() )){
            throw pa4exception("Invalid name value provided in input file.");
        }
        studentRecord.name = currentToken;

        // Extract each monthly contribution and validate input
        for( int i = 0; i < 12; ++ i ){
            if( currentLine.eof() ){
                throw pa4exception(
                    "Invalid monthly participation value in input file." );
            }
            getline( currentLine, currentToken, ' ' );
            if( !atoi( currentToken.c_str() )){
                throw pa4exception(
                    "Invalid monthly participation value in input file." );
            } else {
                studentRecord.monthlyParticipation[i] =
                    atoi(currentToken.c_str());
            }
        }
        recordTable.insert( studentRecord.name, studentRecord );
    }

    // Determine dues
    std::string hoursContributed;
    std::stringstream hoursContributedStream;
    std::string membershipCost;
    std::stringstream membershipCostStream;
    getline( crFile, hoursContributed );
    hoursContributedStream << hoursContributed;
    getline( crFile, membershipCost );
    membershipCostStream << membershipCost;

    // Load hash table with cost rates
    while( !hoursContributedStream.eof() && !membershipCostStream.eof() ){
        getline( hoursContributedStream, hoursContributed, ' ' );
        getline( membershipCostStream, membershipCost, ' ' );
        membershipCostTable.insert( atof(hoursContributed.c_str()),
                                  atof(membershipCost.c_str()) );
    }
}

void pa4functions::CalculateAndOutputDues(
    const char* outputFile,
    StudentRecordTable& recordTable,
    CompensationRateTable& membershipCostTable ){

    std::fstream outFile( outputFile );
    if( !outFile ){
        throw pa4exception( "Invalid output file." );
    }

    OstreamOutput( outFile, recordTable, membershipCostTable );
    OstreamOutput( std::cout, recordTable, membershipCostTable );
}

void pa4functions::OstreamOutput( std::ostream& out,
                            StudentRecordTable& recordTable,
                            CompensationRateTable& membershipCostTable ){

    out << std::setprecision( 1 )
    << std::setiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::showpoint);

    out << "Club Dues\n---------\n\n";

    // Print monthly compensation and the total for the year.
    CompensationRateTable::iterator crtIt;
    float duesOwed;
    float totalDuesOwed;
    for( StudentRecordTable::iterator srtIt = recordTable.begin();
        srtIt != recordTable.end();
        ++ srtIt ){

        duesOwed = 0;
        totalDuesOwed = 0;

        out << srtIt->key << "\n"
            << "Jan" << std::setw(COUT_WIDTH)
            << "Feb" << std::setw(COUT_WIDTH)
            << "Mar" << std::setw(COUT_WIDTH)
            << "Apr" << std::setw(COUT_WIDTH)
            << "May" << std::setw(COUT_WIDTH)
            << "Jun" << std::setw(COUT_WIDTH)
            << "Jul" << std::setw(COUT_WIDTH)
            << "Aug" << std::setw(COUT_WIDTH)
            << "Sep" << std::setw(COUT_WIDTH)
            << "Oct" << std::setw(COUT_WIDTH)
            << "Nov" << std::setw(COUT_WIDTH)
            << "Dec"  << "\n";
        for( int i = 0; i < 12; ++ i ){
            crtIt = membershipCostTable.find(
                floor(srtIt->value.monthlyParticipation[i] ));

            // Exact match
            if( crtIt != membershipCostTable.end() ){
                duesOwed = crtIt->value;

            // Interpolation
            } else {
                int x = 0;
                int y = 0;

                CompensationRateTable::iterator itx;
                CompensationRateTable::iterator ity;

                // Interpolation - The mean of two adjacent values.
                try{
                    do {
                        -- x;
                        itx = membershipCostTable.find( 
                            floor(srtIt->value.monthlyParticipation[i]) + x );
                        if( x < -srtIt->value.monthlyParticipation[i] ){
                            throw pa4exception( "itx" );
                        }
                    } while( itx == membershipCostTable.end() );
                
                    do {
                        ++ y;
                        ity = membershipCostTable.find( 
                            floor(srtIt->value.monthlyParticipation[i]) + y);
                        if( y > srtIt->value.monthlyParticipation[i] ){
                            throw pa4exception( "ity" );
                        }
                    } while( ity == membershipCostTable.end() );
                    duesOwed = (itx->value + ity->value)/2;

                // Interpolation - Mean not possible, must scale based
                //                 on percentage. Otherwise propogate exception
                } catch ( pa4exception e ) {
                    if( std::string(e.what()) == "ity" ){
                        x = 0;
                         do {
                            -- x;
                            itx = membershipCostTable.find( 
                                floor(srtIt->value.monthlyParticipation[i])+x);
                            if( x < -srtIt->value.monthlyParticipation[i] ){
                                throw pa4exception( "Interpolation error!" );
                            }
                        } while( itx == membershipCostTable.end() );
                            (itx->key/srtIt->value.monthlyParticipation[i])
                                * itx->value ;
                    } else {
                        y = 0;
                        do {
                            ++ y;
                            ity = membershipCostTable.find( 
                                floor(srtIt->value.monthlyParticipation[i])+y);
                            if( y > srtIt->value.monthlyParticipation[i] ){
                                throw pa4exception( "Interpolation error!" );
                            }
                        } while( ity == membershipCostTable.end() );
                        duesOwed =  
                            (ity->key/srtIt->value.monthlyParticipation[i])
                                * ity->value ;
                    }
                }
            }
            totalDuesOwed += duesOwed;

            out << duesOwed;
            // Output dues in proper format
            if( duesOwed < 10.0 ){
                out<< std::string( 3, ' ' );
            } else {
                out << std::string( 2, ' ' );
            }
        }
        out << "\nYearly dues = " << totalDuesOwed << "\n\n";
    }
}

