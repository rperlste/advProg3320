/******************************************************************************
 * Author:  Robbie Perlstein
 * Date:    Apr 15, 2013
 * SSID:    101130094
 * Purpose: Assignment 4 - Hash Table and Club Dues
            In this program, two input files are read, parsed, loaded into
            hash tables, and then extracted for outputs via cout and output
            to a file.
  
 ******************************************************************************
 *  Hash Table, Forward Iterator for Hash Table, Bucket for Hash Table
 
 *  The following provides a generic Hash Table implementation that uses
    chaining to resolve conflicts.
 
 *  Any key that is not a built-in type must provide it's own hashing function.
 
 *  A bucket class is utilized as the container for the table, it consists of
    a key and value pair, and a link to another bucket.
 
 *  A forward iterator class exists for traversing the entire table and for
    searching elements within the table. It bahaves like STL forward iterator.
 *****************************************************************************/


#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <iostream>
#include <iterator>
#include <string>

// Forward declarations
template< typename key_type, typename mapped_type > class Bucket;
template< typename key_type, typename mapped_type > class HashTableIterator;
template< typename key_type, typename mapped_type > class HashTable;
template< typename key_type, typename mapped_type > std::ostream& operator <<
    ( std::ostream&, const HashTable<key_type, mapped_type>& );


/***** Bucket class for HashTable *********************************************
 *  This class is a specialized container similar to std::pair, but is
    specific for the HashTable<K,V> class.
  
****** PRE / POST CONDITIONS **************************************************

Bucket( key_type key, mapped_type value, Bucket* next = 0 )
PRE:    None
POST:   Constructs a bucket. _next pointer is defaulted to 0 assuming there is
        no link

******************************************************************************/
template< typename key_type, typename mapped_type >
class Bucket {
public:
    Bucket( key_type key, mapped_type value, Bucket* next = 0 )
        :key(key),value(value),_next(next) {}
    key_type key;
    mapped_type value;
    friend class HashTable<key_type,mapped_type>;
    friend class HashTableIterator<key_type,mapped_type>;
    friend std::ostream& operator << ( std::ostream&,
                                    const HashTable< key_type, mapped_type >& );
private:
    Bucket* _next;
};

/***** Forward iterator class for HashTable ***********************************
 *  Specialized iterator class for the HashTable<K,V> class
 *  Comes with the standard bells and whistles.
  
****** PRE / POST CONDITIONS **************************************************

HashTableIterator();
PRE:    None
POST:   Creates an end iterator;

HashTableIterator( bucket_type* cursor, hash_table* ht);
PRE:    None
POST:   Creates iterator starting at cursor's bucket. Uses ht's hashing algo
        to iterate past any chained buckets. If cursor == 0, then creates an
        end iterator. If the ht == 0, then the iterator won't traverse the 
        table.

HashTableIterator( const HashTableIterator<key_type,mapped_type>& );
PRE:    None
POST:   Copies the iterator

bool operator == ( const HashTableIterator<key_type,mapped_type>& it ) const;
PRE:    None
POST:   Compares addresses of cursors, return true if same.

bool operator != ( const HashTableIterator<key_type,mapped_type>& it ) const;
PRE:    None
POST:   Compares addresses of cursors, return false if same.


bucket_type& operator * ()  const;
PRE:    _cursor points at a bucket
POST:   "Dereferences" the iterator, allowing element access.

bucket_type* operator -> () const;
PRE:    _cursor points at a bucket
POST:   Accesses the bucket elements.

void operator ++ ();
PRE:    None
POST:   Iterates forward until there are no more elements, then sets to end.

void operator ++ ( int );
PRE:    None
POST:   Iterates forward until there are no more elements, then sets to end.

void operator =  ( const HashTableIterator<key_type,mapped_type>& it );
PRE:    None
POST:   Copies the iterator.


******************************************************************************/
template< typename key_type, typename mapped_type >
class HashTableIterator {

public:
    typedef Bucket< key_type, mapped_type > bucket_type;
    typedef HashTable< key_type, mapped_type > hash_table;
    typedef typename hash_table::size_type size_type;

    HashTableIterator();
    HashTableIterator( bucket_type* cursor, hash_table* ht);
    HashTableIterator( const HashTableIterator<key_type,mapped_type>& );
    ~HashTableIterator() {}

    // Comparison
    bool operator == ( const HashTableIterator<key_type,mapped_type>& it )const;
    bool operator != ( const HashTableIterator<key_type,mapped_type>& it ) const;

    // Element access
    bucket_type&                   operator * ()  const;
    bucket_type*                   operator -> () const;

    // Modifiers
    void operator ++ ();
    void operator ++ ( int );
    void operator =  ( const HashTableIterator<key_type,mapped_type>& it );

    // Friends
    friend class HashTable< key_type, mapped_type >;

private:
    bucket_type*                    _cursor;
    hash_table*                     _hash_table;
    size_type                       _index;
};

/***** Hash Table *************************************************************
 *  Hash Table for all built in types and std::string.                        
 *  Any non built in types must provide a hashing function.    

******* PRE / POST CONDITIONS *************************************************

HashTable( const HashTable< key_type, mapped_type >& );
PRE:    None
POST:   Copies the existing table.

HashTable( size_type indexSize = SIZE );
PRE:    None
POST:   Creates an empty table with index size deaulted to SIZE;

HashTable( hashing_funct_ptr hashPtr,
            size_type indexSize = SIZE  );
PRE:    None
POST:   Creates an empty table with a hashPtr for the hashing algorithm
        and size defaulted to SIZE

HashTable( bucket_type,
            size_type indexSize = SIZE );
PRE:    None
POST:   Creates a table with a bucket inserted and size defaulted to SIZE

HashTable( bucket_type,
            hashing_funct_ptr hashPtr,
            size_type indexSize = SIZE );
PRE:    None
POST:   Creates a table with a bucket inserted, uses hashPtr for hashing if it
        is not 0, and size defaults to SIZE

HashTable( key_type,
            mapped_type,
            size_type indexSize = SIZE );
PRE:    None
POST:   Creates a bucket from the pair and inserts it into the table with
        size defaulted to SIZE

HashTable( key_type,
            mapped_type,
            hashing_funct_ptr hashPtr,
            size_type indexSize = SIZE );
PRE:    None
POST:   Creates a bucket from the pair and inserts it into the table with
        size defaulted to SIZE, hashPtr is used for hashing if it is not 0

virtual ~HashTable();
PRE:    None   
POST:   Deletes all buckets associated with the table.

inline bool empty() const
PRE:    None
POST:   Return true if there are no buckets in the table.

inline size_type size() const
PRE:    None
POST:   Returns number of buckets

inline size_type indexSize() const
PRE:    None
POST:   Returns size of the internal table array

iterator begin ();
PRE:    None
POST:   Return an iterator to the first element of the table, not the first
        or sorted insertion. Returns end iterator if table is empty.

iterator end   ();
PRE:    None
POST:   Returns an iterator that points to 0

mapped_type& operator [] ( const key_type& );
PRE:    If the key references no value, then the value will call its
        default constructor. Thus a key must have a constructor that
        takes no arguments.
POST:   Returns a reference to the value associated with the key, or creates
        a new value. Can be assigned to.

bucket_type& at ( const key_type& );
PRE:    None
POST:   Returns a pointer to the first bucket that contains the key, or 0 if
        no key match is found.

iterator find  ( const key_type& );
PRE:    None
POST:   Returns iterator to the first reference of the key, or end if no
        match is found.

size_type count ( const key_type& );
PRE:    None
POST:   Returns the number of key matches found in the entire table.

void insert ( bucket_type );
PRE:    None
POST:   Inserts a bucket into the table.

void insert ( const key_type&, const mapped_type& );
PRE:    None
POST:   Creates a bucket from the key/value pair and inserts into the table.

size_type erase  ( const key_type& );
PRE:    None
POST:   Deletes any entries in the table that match the key, and returns the 
        quantity of deletions that occurred.

void clear  ();
PRE:    None
POST:   Deletes all buckets, resets the size to 0.

float loadFactor ();
PRE:    None
POST:   Returns the ratio of buckets to the number of available table slots.



******************************************************************************/

template< typename key_type, typename mapped_type >
class HashTable {
    // Constant members
    enum _DEFAULTS { SIZE = 10007,
                     HASH_MOD = 15486719,
                     HASH_MULT = 11,
                     HASH_ADD = 8111 };
public:

    typedef unsigned size_type;
    typedef Bucket< key_type, mapped_type > bucket_type;
    typedef HashTableIterator< key_type, mapped_type > iterator;
    typedef unsigned (*hashing_funct_ptr)( const key_type& );

    // Construction
    HashTable( const HashTable< key_type, mapped_type >& );
    HashTable( size_type indexSize = SIZE );
    HashTable( hashing_funct_ptr hashPtr,
               size_type indexSize = SIZE  );
    HashTable( bucket_type,
               size_type indexSize = SIZE );
    HashTable( bucket_type,
               hashing_funct_ptr hashPtr,
               size_type indexSize = SIZE );
    HashTable( key_type,
               mapped_type,
               size_type indexSize = SIZE );
    HashTable( key_type,
               mapped_type,
               hashing_funct_ptr hashPtr,
               size_type indexSize = SIZE );
    virtual ~HashTable();

    // Capacity
    inline bool             empty() const     { return _size == 0; }
    inline size_type        size() const      { return _size; }
    inline size_type        indexSize() const { return _MAX_INDEX_SIZE; }

    // Iterator
    iterator                begin ();
    iterator                end   ();

    // Element access
    // If element does not exist, calls default value constructor.
    // If value cannot call a default constructor, bad things will happen.
    mapped_type&            operator [] ( const key_type& );
    bucket_type&            at          ( const key_type& );

    // Element lookup.
    iterator                find  ( const key_type& );
    size_type               count ( const key_type& );

    // Modifiers
    void                    insert ( bucket_type );
    void                    insert ( const key_type&, const mapped_type& );
    size_type               erase  ( const key_type& );
    void                    clear  ();

    // Hash policy
    float                   loadFactor ();

    // Friends
    friend std::ostream& operator << ( std::ostream&,
                                    const HashTable< key_type, mapped_type >& );
    friend class Bucket< key_type, mapped_type >;
    friend class HashTableIterator< key_type, mapped_type >;

private:
    // Members
    size_type               _size;
    size_type               _MAX_INDEX_SIZE;
    bucket_type**           _table;

    // Hash function
    hashing_funct_ptr       _hashPtr;
    size_type               _hashKey( int );
    size_type               _hashKey( float );
    size_type               _hashKey( char );
    size_type               _hashKey( const char* );
    size_type               _hashKey( std::string );
    size_type               _hash( const key_type& );
    size_type               _bucketIndex( const key_type& );
};


#include "hash.tem"

#endif
