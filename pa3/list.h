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

/************************ PRE / POST CONDITIONS ********************************
fw_list();
PRE:    None.
POST:   Creates an empty list.

fw_list( const fw_list<T>& );
PRE:    None.
POST:   Copies a list, creating new elements in free store.

fw_list( iterator, iterator );
PRE:    None.
POST:   Copies a list from the first iterator to the second, or when the first
        iterator reaches the end of the list.

fw_list( T*, T* );
PRE:    T* points an array. The second argument is a within the arrays size.
POST:   Creates a list from an array of type T.

~fw_list();
PRE:    None.
POST:   Deletes any objects in the list.

// Constant members
unsigned size() const
PRE:    None.
POST:   Returns the size of the list.

bool empty() const
PRE:    None.
POST:   Returns true if the list is empty, else false.

const T& front() const;
PRE:    None.
POST:   Returns the first element of the list. Throws an exception if list
        is empty.

const iterator find( const T& ) const;
PRE:    None.
POST:   Returns an iterator for the first element that matches the parameter,
        or returns the end iterator.

// Modification members
void push_front( const T& );
PRE:    None.
POST:   Pushes a new element onto the front of the list, making it the head.

void pop_front();
PRE:    None.
POST:   Pops the first element off the list if one exists.

iterator find( const T& );
PRE:    None.
POST:   Returns an iterator for the first element that matches the parameter,
        or returns the end iterator.

void insert( const T&, unsigned );
PRE:    None.
POST:   Inserts an element into the list at a position, where offsets start
        at 0. Inserts at the end if the position provided is not accessible.

void insert_after( iterator, const T& );
PRE:    Iterator must be for the this list.
POST:   Inserts an element after the iterator provided.

bool erase_one( const T& );
PRE:    None.
POST:   Erases the first instance of an element found. Returns true if erased.

unsigned erase( const T& );
PRE:    None.
POST:   Erases all instances of an element. Returns the quantity erased.

void clear();
PRE:    None.
POST:   Deletes all elements of the list.

fw_list<T>& operator =  ( const fw_list<T>& );
PRE:    None.
POST:   Copies a list, creating new elements in free store, overwriting the 
        original list.

void operator += ( const fw_list<T>& );
PRE:    None.
POST:   Appends a list onto the end of this list in order.

template<T> friend std::ostream& 
                operator << ( std::ostream&, const fw_list<T>& );
PRE:    Data type T supports ostream operator <<
POST:   Prints a formatted list output to a stream.

iterator begin() const;
PRE:    None.
POST:   Returns an iterator for the first element in the list. If the list is
        empty it returns the end iterator.

iterator end() const;
PRE:    None.
POST:   Returns an end iterator.

node*   copy(node*);
PRE:    None.
POST:   Returns a node* to a node copy in free store.

******** NOTE - THE SAME PRE/POST APPLIES FOR THE SPECIALIZATION
******** EXCEPT FOR ONE ADDITION - IF THE POINTER CANNOT BE DEREFERENCED
******** TO A VALUE TYPE, THEN THERE WILL BE UNDEFINED BEHAVIOR

*******************************************************************************/

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
    fw_list( const fw_list<T>& );
    fw_list( iterator, iterator );
    fw_list( T*, T* );
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

// Specialization for pointers
template <typename T>
class fw_list<T*> {
public:
    typedef fw_node_iterator<T*> iterator;

    // Constructors
    fw_list();
    fw_list( const fw_list<T*>& );
    fw_list( iterator, iterator );
    fw_list( T**, T** );
    ~fw_list();

    // Constant members
    unsigned        size() const { return used; }
    bool            empty() const { return used==0; }
    T* const        front() const;
    const iterator  find( T* const ) const;

    // Modification members
    void            push_front( T* const );
    void            pop_front();
    iterator        find( T* const );
    void            insert( T* const, unsigned );
    void            insert_after( iterator, T* const );
    bool            erase_one( T* const );
    unsigned        erase( T* const );
    void            clear();

    // Operators
    fw_list<T*>&    operator =  ( const fw_list<T*>& );
    void            operator += ( const fw_list<T*>& );

    // Friends
    template<T*> friend std::ostream& 
                    operator << ( std::ostream&, const fw_list<T*>& );
    friend class    fw_node_iterator<T*>;

    // Forward iterator support
    iterator        begin() const;
    iterator        end() const;

private:
    // Nest our linked-fw_list node
    struct node
    {
        node(T* val=0, node* n=0):data(val),link(n) { }
        T*          data;
        node*       link;
    };
    node*           head;
    unsigned        used;
    node*           copy(node*);
};

#include "list.tem"


#endif