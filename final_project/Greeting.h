#ifndef _GREETING_
#define _GREETING_

#include <iostream>

void PrintFinalGreeting(){
    std::cout << "This is the final project for UC Denver's CSCI 3320,"
        << "\nAdvanced Programming for the Spring 2013 semester. This program"
        << "\nis a simple game that simulates a terrifying dungeon crawl and"
        << "\nfighting against abominations that lurk the castle's"
        << "\ncursed halls. The purpose is to demonstrate our command of"
        << "\nC++ concepts and tools that were taught over the semester."
        << "\n\nI took a notable turn in programming style, opting to"
        << "\nwrite self-documenting code such that I have many granular"
        << "\nfunctions that perform just one or two lines of code."
        << "\nMy outside research in places like The Pragmatic Programmer,"
        << "\nClean Code, and Stack Overflow, put a large emphasis on code"
        << "\nreadability. I have found the attempt to break down every"
        << "\nfunction into smaller, self-contained, and self-descriptive"
        << "\nunits to be very profound, and will likely result in a shift"
        << "\nin my style to more often decompose and write descriptive"
        << "\nfunction names, thus making the code self-documenting.\n";
}

#endif