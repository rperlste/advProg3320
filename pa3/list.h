/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Forward Linked List
 *    
 *    Class declaration for a single-ended, singly-linked list with iterator
 *    support. Compatible with C++ STL
 */

#ifndef _FwLinkedList_H
#define _FwLinkedList_H

#include <iostream>
#include <exception>

// Forward declarations for overloading operator <<
template <typename T> class fw_list;
template <typename T> std::ostream& 
                    operator << ( std::ostream&, const fw_list<T>& );

#include "node_iterator.h"


// Class definition
template <typename T>
class fw_list {
public:
    typedef fw_node_iterator<T> iterator;

    // Constructors
    fw_list();
    fw_list(        const fw_list<T>& );
    fw_list(        iterator, iterator );
    fw_list(        T*, T* );

    ~fw_list();

    // Constant members
    unsigned        size() const { return used; }
    bool            empty() const { return used==0; }
    const T&        front() const;
    const iterator  find( const T& ) const;

    // Modification members
    void            push_front( const T& );
    void            pop_front();
    iterator        find( const T& );
    void            insert( const T&, unsigned );
    void            insert_after( iterator, const T& );
    bool            erase_one( const T& );
    unsigned        erase( const T& );
    void            clear();

    // Operators
    fw_list<T>&     operator =  ( const fw_list<T>& );
    void            operator += ( const fw_list<T>& );

    // Friends
    template<T> friend std::ostream& 
                    operator << ( std::ostream&, const fw_list<T>& );
    friend class    fw_node_iterator<T>;

    // Forward iterator support
    iterator        begin() const;
    iterator        end() const;

private:
    // Nest our linked-fw_list node
    struct node
    {
        node(const T& val=T(), node* n=0):data(val),link(n) { }
        T           data;
        node*       link;
    };
    node*           head;
    unsigned        used;
    node*           copy(node*);
};

#include "list.tem"

#endif