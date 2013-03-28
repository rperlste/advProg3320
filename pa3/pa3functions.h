#ifndef _pa3functions_H
#define _pa3functions_H

#include "list.h"

/******** PRE / POST CONDITIONS ************************************************
void PrintGreeting();
PRE:    None
POST:   Prints a greeting and description via cout

void InstanceLists( fw_list<int>, fw_list<int> );
PRE:    Lists should not already be instanced, as there will be no deletion.
POST:   Creates a list that contains the squares of the first 10
        integers in order, starting with 1. 
        Creates another list with values 2 and 4 in order.

void ManipulateList( fw_list<int>, fw_list<int> );
PRE:    Lists have been instanced.
POST:   Prints lists sizes. Concats lists. Prints sizes again. 
        Averages list values. Prints the list with cout and <<.
*******************************************************************************/

namespace pa3functions {
    void PrintGreeting();
    void InstanceLists( fw_list<int>&, fw_list<int>& );
    void ManipulateList( fw_list<int>&, fw_list<int>& );
}

#endif