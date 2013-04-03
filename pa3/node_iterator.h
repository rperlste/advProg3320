/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Node Iterator
 *    
 *    Forward iterator for fw_list. Complies with C++ STL
 */

/************************ PRE / POST CONDITIONS ********************************
fw_node_iterator();
PRE:    None.
POST:   Creates an end iterator.

fw_node_iterator( node* nPtr );
PRE:    nPtr must reference an node in memory.
POST:   Creates an iterator starting at the nPtr.

fw_node_iterator( const fw_node_iterator& );
PRE:    None.
POST:   Copies the node iterator, uses it's cursor for a starting point.

~fw_node_iterator()
PRE:    None.
POST:   Destructs the iterator. Deletes nothing.

bool operator == ( const fw_node_iterator<T>& it ) const;
PRE:    None.
POST:   Returns true if the cursor addresses are equal, else false.

bool operator != ( const fw_node_iterator<T>& it ) const;
PRE:    None.
POST:   Returns true if the cursor addresses are not equal, else false.

T& operator * ()  const;
PRE:    The cursor references a node in memory.
POST:   Returns the data value of the cursor.

node* operator -> () const;
PRE:    The cursor references a node in memory.
POST:   Returns a pointer to the cursor.

void operator ++ ();
PRE:    None.
POST:   Sets the cursor to the current cursors link. If the link is 0, or there
        is no link, sets the iterator to end.

void operator ++ ( int );
PRE:    None.
POST:   Sets the cursor to the current cursors link. If the link is 0, or there
        is no link, sets the iterator to end.

void operator =  ( const fw_node_iterator<T>& it );
PRE:    None.
POST:   Assigns this's cursor to point at it's cursor.
*******************************************************************************/

#ifndef _FLLNodeIterator_H
#define _FLLNodeIterator_H

#include <iterator>

template <typename T>
class fw_node_iterator : public std::iterator 
    <std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {

public:
    typedef typename		fw_list<T>::node node;

    fw_node_iterator();
    fw_node_iterator( node* nPtr );
    fw_node_iterator( const fw_node_iterator& );
    ~fw_node_iterator() {}

    // Equality operations
    bool                    operator == ( const fw_node_iterator<T>& it ) const;
    bool                    operator != ( const fw_node_iterator<T>& it ) const;

    // Dereference operations
    T&                      operator * ()  const;
    node*                   operator -> () const;

    // Assign/Change iterator's cursor
    void                    operator ++ ();
    void                    operator ++ ( int );
    void                    operator =  ( const fw_node_iterator<T>& it );

    friend class fw_list<T>;

private:
    node*                   cursor;
};

#include "node_iterator.tem"

#endif