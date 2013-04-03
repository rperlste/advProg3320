#include "pa3functions.h"

void pa3functions::PrintGreeting(){
    std::cout << "Greetings user! This is a simple program that demonstrates"
        << "\nan implementation of a forward linked list. A forward linked list"
        << "\nis a data structure that acts as a dynamically expanding array."
        << "\nIt consists of containers, called nodes, that store an individual"
        << "\nunit of data, and a pointer to another node. There pointers are"
        << "\nused to chain, or link, the data together into a list."
        << "\n\nLinked lists are memory efficient, especially when large,"
        << "\nand can quickly append data to the head of the list."
        << "\n\nThis program will create two lists, remove data from the lists,"
        << "\ninsert new data into the lists, concat the lists, compute the"
        << "\nsize of the lists, and print the elements of the lists.\n\n";
}

void pa3functions::InstanceLists( fw_list<int>& list1, fw_list<int>& list2 ){

    // Load list1 with the squares in range (1,10)
    for( int i = 10; i > 0; -- i ){
        list1.push_front( i*i );
    }

    list2.push_front(4);
    list2.push_front(2);
}

void pa3functions::ManipulateList( fw_list<int>& list1, fw_list<int>& list2 ){

    std::cout << "\nThe number of elements in list 1 is: " << list1.size()
        << "\nThe number of elements in list 2 is: " << list2.size()
        << "\n\nManipulations on the lists:"
        << "\nlist1 += list2         // append list2 to list1"
        << "\nlist1.erase( 49 );     // erase element == 49"
        << "\nlist1.pop_front();     // pop the first element of the list"
        << "\nlist1.push_front( 6 ); // push 6 onto the front of the list";

    // Manipulations
    list1 += list2;
    list1.erase( 49 );
    list1.pop_front();
    list1.push_front( 6 );

    // Size
    std::cout << "\n\nThe new number of elements in the list1 is: " 
        << list1.size();

    // Compute sum
    unsigned sum = 0;
    for( fw_list<int>::iterator it = list1.begin();
        it != list1.end();
        ++ it ){
        sum += (*it);
    }
    std::cout << "\nThe sum of the elements in the list is: " << sum;

    // Compute average
    std::cout << "\nThe average of the elements in the list is: " 
        << (sum/list1.size());

    // Print contents with iterator
    std::cout << "\nContents using iterator are {";
    fw_list<int>::iterator it = list1.begin();
    if( it != list1.end() ){
        std::cout << " " << it->data;
        ++ it;
    }
    while( it != list1.end() ){
        std::cout << ", " << it->data;
        ++ it;
    }
    std::cout << " }";


    // Print contents with operator <<
    std::cout << "\nContents using operator << are " << list1 << "\n\n";
}