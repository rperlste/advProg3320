#ifndef _PA6_FUNCTIONS_H
#define _PA6_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <ctype.h>
#include "TextEditor.h"


namespace pa6functions{
    // Classes and containers
    class pa6exception : public std::exception {
    public:
        pa6exception( std::string what ):_what(what) {}
        const char* what(){ return _what.c_str(); }
    private:
        std::string _what;
    };

    // Functions
    void GreetUser();
    void PrintTitle();
    void RunTextEditor( const std::string& );
    void GetFilename( std::string& );
    void TestValidFilename( const std::string& fileName );
    void RunMenu( TextEditor& );
    void PrintMenu();
    void GetInput( char& );
    void GetInput( std::string& );
    void GetInt( int& );
    void RefreshCin();
    bool StrIsDigit( const std::string& );
    void PressEnterToContinue(unsigned);

    // TextEditor wrapper functions.
    void Read( TextEditor& );
    void Write( TextEditor& );
    void Insert( TextEditor& );
    void Delete( TextEditor& );
    void FindAndReplace( TextEditor& );
    void LineCount( TextEditor& );
    void View( TextEditor& );
    void Clear( TextEditor& );
}


#endif