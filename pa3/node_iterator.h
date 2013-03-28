/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Node Iterator
 *    
 *    Forward iterator for fw_list. Complies with C++ STL
 */

#ifndef _FLLNodeIterator_H
#define _FLLNodeIterator_H

#include <iterator>

template <typename T>
class fw_node_iterator : public std::iterator 
    <std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {

public:
    typedef typename		fw_list<T>::node node;

    fw_node_iterator();
    fw_node_iterator(       node* nPtr );
    fw_node_iterator(       const fw_node_iterator& );
    ~fw_node_iterator() {}

    bool                    operator == ( const fw_node_iterator<T>& it ) const;
    bool                    operator != ( const fw_node_iterator<T>& it ) const;

    T&                      operator * ()  const;
    node*                   operator -> () const;

    void                    operator ++ ();
    void                    operator ++ ( int );
    void                    operator =  ( const fw_node_iterator<T>& it );

    friend class fw_list<T>;

private:
    node*                   cursor;
};

#include "node_iterator.tem"

#endif