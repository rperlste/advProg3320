#ifndef _TEXT_EDITOR_H
#define _TEXT_EDITOR_H

#include <list>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

/***** class TextEditor ********************************************************

This is a simple text editor class that allows for line edits, modifications, 
inserts, and removals. The file is read in and written out via fstream.
The file's text buffer is a linked list.

Functionality:
TextEditor( const std::string& );
POST:   Instances a TextEditor with the argument as the filename.

bool read();
PRE:    The file is valid. Throws exception otherwise.
POST:   Reads the contents of the file and stores them in the text buffer.

bool write();
PRE:    The file is valid. Throws exception otherwise.
POST:   Dumps the contents of the text buffer into the file. Overwrites existing
        file data.

bool insertLine( unsigned, const std::string& );
POST:   Inserts a line at the location specified, or at the end of the text
        document. Indexing starts at 1, but passing a 0 will insert at the front
        as well.

bool deleteLine( unsigned );
POST:   Deletes the line at the location specified. If there is no item at the 
        location, then an error message is printed.

bool replace( const std::string&, const std::string& );
POST:   Finds the first instance of the string to search for, then replaces that
        instance with the replacement string. If there is no match, an error
        message is printed.

void clear();
POST:   Clears the text buffer.

void view();
POST:   Prints the text buffer to cout.

unsigned lineCount();
POST:   Prints the number of lines to cout.

std::string getFileName();
POST:   Returns the filename as a string.

void setFileName( const std::string& );
POST:   Sets the filename to the new value.


*******************************************************************************/
class TextEditor {
public:
    typedef std::list<std::string> TextBuffer;

    TextEditor( const std::string& );

    bool read();
    bool write();
    bool insertLine( unsigned, const std::string& );
    bool deleteLine( unsigned );
    bool replace( const std::string&, const std::string& );
    void clear();
    void view();
    unsigned lineCount();

    std::string getFileName();
    void setFileName( const std::string& );
    
private:
    TextBuffer _textBuffer;
    std::string _filename;
};

#endif