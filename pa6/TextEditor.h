#ifndef _TEXT_EDITOR_H
#define _TEXT_EDITOR_H

#include <list>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

class TextEditor {
public:
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
    std::list<std::string> _textBuffer;
    std::string _filename;
};

#endif