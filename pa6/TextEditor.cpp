#include "TextEditor.h"

TextEditor::TextEditor( const std::string& fileName ){ 
    _filename = fileName;
}

bool TextEditor::read(){ 
    std::ifstream fin( _filename );
    _textBuffer.clear();
    if( fin ){
        std::string line;
        while( !fin.eof() ){
            std::getline( fin, line );
            _textBuffer.push_back( line );
        }
        fin.close();
        // Test for empty file.
        if( line == "" ){
            _textBuffer.pop_back();
        }
        return true;
    } else {
        fin.close();
        return false;
    }
}

bool TextEditor::write(){ 
    std::ofstream fin( _filename );
    for( std::list<std::string>::iterator it = _textBuffer.begin();
        it != _textBuffer.end();
        ++ it ){
            fin << *it << "\n";
    }
    fin.close();
    return true;
}

bool TextEditor::insertLine( unsigned pos, const std::string& line ){ 
    std::list<std::string>::iterator it = _textBuffer.begin();
    unsigned currentPos = 1;
    while( it != _textBuffer.end() && currentPos < pos ){
        ++ it;
        ++ currentPos;
    }
    try{
        _textBuffer.insert( it, line );
        return true;
    } catch ( std::bad_alloc e ){
        return false;
    }
}

bool TextEditor::deleteLine( unsigned pos ){ 
    std::list<std::string>::iterator it = _textBuffer.begin();
    unsigned currentPos = 1;
    while( it != _textBuffer.end() && currentPos < pos ){
        ++ it;
        ++ currentPos;
    }
    if( currentPos == pos && it != _textBuffer.end() ){
        _textBuffer.erase( it );
        return true;
    } else {
        return false;
    }
}

bool TextEditor::replace( const std::string& find, const std::string& replace ){
    for( std::list<std::string>::iterator it = _textBuffer.begin();
        it != _textBuffer.end();
        ++ it ){
            unsigned pos = (*it).find( find );
            if( pos != std::string::npos ){
                (*it).replace( pos, find.size(), replace );
                return true;
            }
        }
    return false;
}

void TextEditor::view(){ 
    std::cout << "\n" << std::string(80, '_');
    for( std::list<std::string>::iterator it = _textBuffer.begin();
        it != _textBuffer.end();
        ++ it ){
            std::cout << (*it) << std::endl;
        }
    std::cout << std::string(80, '_') << "\n";
    return;
}

void TextEditor::clear(){
    _textBuffer.clear();
}

unsigned TextEditor::lineCount(){
    return _textBuffer.size();
}

std::string TextEditor::getFileName(){
    return _filename;
}

void TextEditor::setFileName( const std::string& fileName ){
    _filename = fileName;
}