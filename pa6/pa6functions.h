#ifndef _PA6_FUNCTIONS_H
#define _PA6_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <ctype.h>
#include <limits.h>
#include "TextEditor.h"

/***** namespace pa6functions **************************************************

class pa6exception

This a simple std::exception implementation for handling the various errors that
can occur while using the text editor program.


void GreetUser();
POST:   Prints a description of the program for the user.

void PrintTitle();
POST:   Prints the "Text Editor" ascii title.

void RunTextEditor( const std::string& );
POST:   Runs the text editor.

void GetFilename( std::string& );
POST:   Asks for a filename from the user if none was provided.

void TestValidFilename( const std::string& filename );
POST:   Throws an exception if the filename is invalid.

void RunMenu( TextEditor& );
POST:   Runs the menu for the text editor, accessing menu functions, and
        retrieving a menu choice from the user.

bool ExecuteMenuChoice( TextEditor&, char );
POST:   Executes the corresponding menu choice, or does nothing.

void PrintMenu();
POST:   Prints the menu to cout, so the user can make menu choices.

void GetInput( char& );
POST:   Retrieves a char from std::cin

void GetInput( std::string& );
POST:   Retrieves a string from std::cin

void GetInt( int& );
POST:   Retreives an int from std::cin, and only allows for an int.
        There are no demotions of strings or chars.

void RefreshCin();
POST:   Refreshes std::cin's buffer to allow for multiple entries from the user

bool StrIsDigit( const std::string& );
POST:   Return true if the string is an integer, otherwise it does not.

void PressEnterToContinue(unsigned);
POST:   Pauses the program. Asks the user to press enter to continue.

void Read( TextEditor& );
POST:   Executes the TextEditors's read function

void Write( TextEditor& );
POST:   Executes the TextEditors's write function

void Insert( TextEditor& );
POST:   Executes the TextEditors's insert function

void Delete( TextEditor& );
POST:   Executes the TextEditors's delete function

void FindAndReplace( TextEditor& );
POST:   Executes the TextEditors's replace function

void LineCount( TextEditor& );
POST:   Executes the TextEditors's lineCount function

void View( TextEditor& );
POST:   Executes the TextEditors's view function

void Clear( TextEditor& );
POST:   Executes the TextEditors's clear function

*******************************************************************************/

namespace pa6functions{
    // Classes and containers
    class pa6exception : public std::exception {
    public:
        pa6exception( std::string what ):_what(what) {}
        const char* what(){ return _what.c_str(); }
        virtual ~pa6exception() throw() {}
    private:
        std::string _what;
    };

    // Functions
    void GreetUser();
    void PrintTitle();
    void RunTextEditor( const std::string& );
    void GetFilename( std::string& );
    void TestValidFilename( const std::string& filename );
    void RunMenu( TextEditor& );
    bool ExecuteMenuChoice( TextEditor&, char );
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