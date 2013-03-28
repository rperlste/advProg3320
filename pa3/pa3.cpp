/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    pa3 - Linked List
 *    
 *    Instance and manipulate forward linked lists.
 */

#include "pa3functions.h"

int main() {
    fw_list<int> list1;
    fw_list<int> list2;

    pa3functions::PrintGreeting();
    pa3functions::InstanceLists( list1, list2 );
    pa3functions::ManipulateList( list1, list2 );
}