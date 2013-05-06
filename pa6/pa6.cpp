#include "pa6functions.h"

int main( int argc, const char* argv[] ){
    
    pa6functions::GreetUser();

    std::string filename;
    if( argc < 2 ){
        pa6functions::GetFilename( filename );
    } else {
        filename = argv[1];
    }

    try{
        pa6functions::RunTextEditor( filename );
    } catch (pa6functions::pa6exception e ){
        std::cerr << "\n\n" << e.what() << "\n\n";
    }

    return 0;
} 