/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    pa3 - Linked List
 *    
 *    Instance and manipulate forward linked lists.
 *    Forward linked lists are data structures that
 *	  allow for dynamically growing and shrinking
 *	  lists of data. They are memory efficient.
 *	  This program demonstrates an implementation of
 *	  a forward linked list, and its iterator.
 *	  Two lists will be created and have their elements
 *	  manipulated. The lists will be printed after the manipulations.
 */

#include "pa3functions.h"

int main() {
    fw_list<int> list1;
    fw_list<int> list2;

    pa3functions::PrintGreeting();
    pa3functions::InstanceLists( list1, list2 );
    pa3functions::ManipulateList( list1, list2 );
}