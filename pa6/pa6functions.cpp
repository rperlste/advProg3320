#include "pa6functions.h"


void pa6functions::GreetUser(){
    std::cout << "\nThis simple line editor allows for the reading of a text\n"
        << "file, and the manipulation of the text file's contents.\n\n"
        << "The file buffer is a STL list, where each element represents\n"
        << "line of the text. The program allows for reading, writing,\n"
        << "insertion, deletion, and replacement of the text data.\n\n";
}

void pa6functions::PrintTitle(){
     std::cout
              << "___________                __    ___________    .___.__   __"
              << "                 \n"
              << "\\__    ___/____  ___  ____/  |_  \\_   _____/  __| _/|__|_/"
              << "  |_  ____ _______  \n"
              << "  |    | _/ __ \\ \\  \\/  /\\   __\\  |    __)_  / __ | |  |"
              << "\\   __\\/  _ \\\\_  __ \\ \n"
              << "  |    | \\  ___/  >    <  |  |    |        \\/ /_/ | |  | | "
              << " | (  <_> )|  | \\/ \n"
              << "  |____|  \\___  >/__/\\_ \\ |__|   /_______  /\\____ | |__| "
              << "|__|  \\____/ |__|    \n"
              << "              \\/       \\/                \\/      \\/      "
              << "                     \n";

}

void pa6functions::RunTextEditor( const std::string& filename ){

    TestValidFilename( filename );
    TextEditor textEditor( filename );
    RunMenu( textEditor );

}

void pa6functions::TestValidFilename( const std::string& filename ){
    if( filename.size() == 0 ){
        throw pa6exception( "Invalid filename." );
    } else if( !isalnum(filename[0]) ){
        throw pa6exception( "Invalid filename." );
    }


}

void pa6functions::RunMenu( TextEditor& textEditor ){
    bool run = true;
    char choice = ' ';

    while( run ){
        PrintMenu();
        // Get menu choice and take approriate action
        GetInput( choice );
        run = ExecuteMenuChoice( textEditor, choice );
        if( run )
            PressEnterToContinue(2);
    }
}

bool pa6functions::ExecuteMenuChoice( TextEditor& textEditor, char choice ){
    switch( choice ){
        case 'R': case 'r': 
            Read( textEditor ); break;
        case 'W': case'w':
            Write( textEditor ); break;
        case 'I': case 'i':
            Insert( textEditor ); break;
        case 'D': case 'd':
            Delete( textEditor ); break;
        case 'F': case 'f':
            FindAndReplace( textEditor ); break;
        case 'L': case 'l':
            LineCount( textEditor ); break;
        case 'V': case 'v':
            View( textEditor ); break;
        case 'C': case 'c':
            Clear( textEditor ); break;
        case 'X' : case 'x': 
            return false;
    }
    return true;
}

void pa6functions::PrintMenu(){
    std::cout << "\n\n" << std::string(80,'-');
    PrintTitle();
    std::cout << std::string(80,'-')
            << "\n:: MAIN MENU ::\n"
            << "R - Read file.\n"
            << "W - Write file.\n"
            << "I - Insert line.\n"
            << "D - Delete line.\n"
            << "F - Find and replace line.\n"
            << "L - Line count.\n"
            << "C - Clear the text.\n"
            << "V - View file.\n"
            << "X - Exit.\n"
            << "\nPlease choose a menu option: ";
}

void pa6functions::Read( TextEditor& textEditor ){
    std::cout << ":: READ FILE ::"
        << "\nReading file: " << textEditor.getFileName();
    if( !textEditor.read() ){
        throw( pa6exception( "Invalid file. Unable to read." ) );
    }
}

void pa6functions::Write( TextEditor& textEditor ){
    std::cout << ":: WRITE FILE ::"
        << "\nWriting to file: " << textEditor.getFileName() ;
    if( !textEditor.write() ){
        throw( pa6exception( "There was an error writing to the file." ) );
    }
}

void pa6functions::Insert( TextEditor& textEditor ){
    std::cout << ":: INSERT LINE ::\n(The first line is 1)\n";
    int lineNum = 0;
    std::string lineIn = "";

    std::cout << "\nEnter a line number: ";
    GetInt( lineNum );
    std::cout << "\nEnter text to insert...\n>>";
    GetInput( lineIn );

    if( !textEditor.insertLine( lineNum, lineIn ) ){
        std::cerr << "\nThere was an exception inserting the text.\n";
    }
}

void pa6functions::Delete( TextEditor& textEditor ){
    std::cout << ":: DELETE LINE ::\n(The first line is 1)\n";
    int lineNum = 0;
    std::cout << "\nEnter a line number to delete: ";
    GetInt( lineNum );
    if( !textEditor.deleteLine( lineNum ) ){
        std::cerr << "\nCould not delete line " << lineNum << ".\n"; 
    }
}

void pa6functions::FindAndReplace( TextEditor& textEditor ){
    std::cout << ":: FIND & REPLACE STRING ::";
    std::string lineIn = "";
    std::string lineOut = "";

    std::cout << "\nEnter a string to find: ";
    GetInput( lineIn );
    std::cout << "\nEnter a replacement string: ";
    GetInput( lineOut );
    if( !textEditor.replace( lineIn, lineOut ) ){
        std::cerr << "\nString not found. Could not replace.\n"; 
    }
}

void pa6functions::LineCount( TextEditor& textEditor ){
    std::cout << ":: LINE COUNT ::\n" 
        << "The document has " << textEditor.lineCount() << " lines.";
}

void pa6functions::View( TextEditor& textEditor ){
    std::cout << ":: VIEW TEXT CONTENTS ::";
    textEditor.view();
}

void pa6functions::Clear( TextEditor& textEditor ){
    std::cout << ":: CLEAR TEXT CONTENTS ::";
    textEditor.clear();
}

void pa6functions::GetInt( int& newInt ){
    std::string sIn;
    std::stringstream ssIn;
    while( true ){
        GetInput( sIn );
        if ( !StrIsDigit(sIn) ){
            std::cerr << "Please enter an integer value: ";
            continue;
        } else {
            break;
        }
    }
    ssIn << sIn;
    ssIn >> newInt;
}

void pa6functions::RefreshCin(){
    std::cin.clear();
    std::cin.ignore(INT_MAX,'\n'); 
}

void pa6functions::GetInput( char& input ){
    std::cin >> input;
    std::cout << std::endl;
    RefreshCin();
}

void pa6functions::GetInput( std::string& input ){
    std::getline( std::cin, input );
    std::cout << std::endl;
}

bool pa6functions::StrIsDigit( const std::string& str ){
    for( int i = 0; i < str.size(); ++i ){
        if( !isdigit(str[i]) )
            return false;
    }
    return true;
}

void pa6functions::GetFilename( std::string& filename ){
        std::cout << "Please provide a filename: ";
        GetInput(filename);
}

void pa6functions::PressEnterToContinue( unsigned newlineCount ){
    std::cout << std::string( newlineCount, '\n' );
    std::cout << "Press ENTER to continue... ";
    std::cin.ignore( INT_MAX, '\n' );
}