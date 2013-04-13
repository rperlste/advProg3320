/*******************************************************************************
 *  Robbie Perlstein
 *  Hash Table, Forward Iterator for Hash Table, Pair
 ******************************************************************************/

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

/******************************************************************************/
// Bucket class for HashTable.
// It is the responsibilty of the hash table to delete any linked buckets
template< typename key_type, typename mapped_type >
class Bucket {
public:
    Bucket( key_type key, mapped_type value, Bucket* next = 0 )
        :key(key),value(value),_next(next) {}
    key_type key;
    mapped_type value;
    friend class HashTable<key_type,mapped_type>;
    friend class HashTableIterator<key_type,mapped_type>;
private:
    Bucket* _next;
};

/******************************************************************************/
// Forward iterator class for HashTable.
template< typename key_type, typename mapped_type >
class HashTableIterator {

public:
    typedef typename Bucket< key_type, mapped_type > bucket_type;
    typedef typename HashTable< key_type, mapped_type > hash_table;
    typedef typename hash_table::size_type size_type;

    HashTableIterator();
    HashTableIterator( bucket_type* cursor, hash_table* ht);
    HashTableIterator( const HashTableIterator<key_type,mapped_type>& );
    ~HashTableIterator() {}

    // Comparison
    bool operator == ( const HashTableIterator<key_type,mapped_type>& it ) const;
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

/******************************************************************************/
// Hash Table. Any non built in types must provide a hashing function.
template< typename key_type, typename mapped_type >
class HashTable {
    // Constant members
    enum _DEFAULTS { SIZE = 10007,
                     HASH_MOD = 15486719,
                     HASH_MULT = 11,
                     HASH_ADD = 8111 };
public:

    typedef unsigned size_type;
    typedef typename Bucket< key_type, mapped_type > bucket_type;
    typedef HashTableIterator< key_type, mapped_type > iterator;
    typedef unsigned (HashTable<key_type,mapped_type>::*hashing_funct_ptr)
        ( const key_type& );

    // Construction
    HashTable( const HashTable< key_type, mapped_type >& );
    HashTable( size_type indexSize = _DEFAULTS::SIZE );
    HashTable( hashing_funct_ptr hashPtr, 
               size_type indexSize = _DEFAULTS::SIZE  );
    HashTable( bucket_type, 
               size_type indexSize = _DEFAULTS::SIZE );
    HashTable( bucket_type, 
               hashing_funct_ptr hashPtr, 
               size_type indexSize = _DEFAULTS::SIZE );
    HashTable( key_type, 
               mapped_type, 
               size_type indexSize = _DEFAULTS::SIZE );
    HashTable( key_type, 
               mapped_type, 
               hashing_funct_ptr hashPtr, 
               size_type indexSize = _DEFAULTS::SIZE );
    virtual ~HashTable();

    // Capacity
    inline bool             empty()    { return _size == 0; }
    inline size_type        size()     { return _size; }
    inline size_type        indexSize() { return _MAX_INDEX_SIZE; }

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
    template< typename key_type, typename mapped_type > friend
        std::ostream& operator << ( std::ostream&, 
                                    const HashTable< key_type, mapped_type > );
    friend class bucket_type;
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


/******************************************************************************/
// Forward Table Iterator defitinion

template< typename key_type, typename mapped_type > 
HashTableIterator<key_type,mapped_type>::HashTableIterator(){
    _cursor = 0;
    _hash_table = 0;
    _index = 0;
}

template< typename key_type, typename mapped_type > 
HashTableIterator<key_type,mapped_type>::HashTableIterator( bucket_type* cursor, 
                                                            hash_table* ht ){
    _cursor = cursor;
    _hash_table = ht;
    _index = (ht != 0) ? _hash_table->_bucketIndex(_cursor->key) : 0;
}

template< typename key_type, typename mapped_type > 
HashTableIterator<key_type,mapped_type>::HashTableIterator( 
    const HashTableIterator<key_type,mapped_type>& it ){
    this->_cursor = it._cursor;
    this->_hash_table = it._hash_table;
    this->_index = it._index;
}

template< typename key_type, typename mapped_type > 
void HashTableIterator<key_type,mapped_type>::operator = ( 
    const HashTableIterator<key_type,mapped_type>& it ){
    this->_cursor = it._cursor;
    this->_hash_table = it._hash_table;
    this->_index = it._index;

}

template< typename key_type, typename mapped_type > 
bool HashTableIterator<key_type,mapped_type>::operator == ( 
    const HashTableIterator<key_type,mapped_type>& it ) const {
    return ( this->_cursor == it._cursor );
}

template< typename key_type, typename mapped_type > 
bool HashTableIterator<key_type,mapped_type>::operator != ( 
    const HashTableIterator<key_type,mapped_type>& it ) const {
    return ( this->_cursor != it._cursor );
}

template< typename key_type, typename mapped_type > 
typename HashTableIterator<key_type,mapped_type>::bucket_type& 
HashTableIterator<key_type,mapped_type>::operator * () const {
    return *_cursor;
}

template< typename key_type, typename mapped_type > 
typename HashTableIterator<key_type,mapped_type>::bucket_type* 
HashTableIterator<key_type,mapped_type>::operator -> () const {
    return _cursor;
}

template< typename key_type, typename mapped_type > 
void HashTableIterator<key_type,mapped_type>::operator ++ () {
    if ( _cursor != 0 ){
        _cursor = _cursor->_next;
        if ( _cursor == 0 && _hash_table != 0 ){
            while( _cursor == 0 && _index < _hash_table->indexSize()-1 ){
                ++ _index;
                _cursor = _hash_table->_table[_index];
            }
        }
    }
}

template< typename key_type, typename mapped_type > 
void HashTableIterator<key_type,mapped_type>::operator ++ ( int ) {
    if ( _cursor != 0 ){
        _cursor = _cursor->_next;
        if ( _cursor == 0 && _hash_table != 0 ){
            while( _cursor == 0 && _index < _hash_table->_MAX_INDEX_SIZE-1 ){
                ++ _index;
                _cursor = _hash_table->_table[_index];
            }
        }
    }
}

/*****************************************************************************/
/******* HashTable<key_type,mapped_type> definition *************************/


template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( const HashTable< key_type, mapped_type >& copy ){
    _size = copy._size;
    _MAX_INDEX_SIZE = copy._MAX_INDEX_SIZE;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        bucket_type* copyBucket = copy._table[i];
        if( copyBucket == 0 ){
            _table[i] = 0;
        } else {
            _table[i] = new bucket_type( copyBucket->key, copyBucket->value );
            bucket_type* currBucket = _table[i];
            copyBucket = copyBucket->_next;
            while( copyBucket != 0 ){
                currBucket->_next = new bucket_type( copyBucket->key, 
                                                     copyBucket->value );
                currBucket = currBucket->_next;
                copyBucket = copyBucket->_next;
            }
        }
    } 
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( size_type indexSize ){
    _size = 0;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( hashing_funct_ptr hashPtr, 
           size_type indexSize  ){
    _size = 0;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( bucket_type bckt, unsigned indexSize ){
    _size = 1;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(bckt.key)] = new bucket_type(bckt.key, bckt.value);
}


template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
    HashTable( bucket_type bckt, hashing_funct_ptr hashPtr, size_type indexSize ){
    _size = 1;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(bckt.key)] = new bucket_type(bckt.key, bckt.value);
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( key_type key, mapped_type value, size_type indexSize ){
    _size = 1;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(key)] = new bucket_type(key,value);
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( key_type key, 
            mapped_type value, 
            hashing_funct_ptr hashPtr, 
            size_type indexSize ){
    _size = 1;
    _MAX_INDEX_SIZE = indexSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(key)] = new bucket_type(key,value);
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
~HashTable(){
    bucket_type* bucketPtr;
    bucket_type* toDel;
    for( int i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        bucketPtr = _table[i];
        toDel = bucketPtr;
        while( bucketPtr != 0 ){
            bucketPtr = bucketPtr->_next;
            delete toDel;
            toDel = bucketPtr;
        }
    }
}
/*

// Iterator
//    iterator                begin ();
//    iterator                end   ();
*/
// Element access
template< typename key_type, typename mapped_type > 
typename mapped_type& 
HashTable<key_type,mapped_type>::operator [] ( const key_type& key ){
    bucket_type* bucket = _table[_bucketIndex(key)];
    while( bucket != 0 && bucket->_next != 0 && bucket->key != key ){
        bucket = bucket->_next;
    }
    if( bucket == 0 ){
        _table[_bucketIndex(key)] = new bucket_type(key,mapped_type());
        bucket =  _table[_bucketIndex(key)];
        ++ _size;
    } 
    else if ( bucket->key != key ){
        bucket->_next = new bucket_type(key,mapped_type());
        bucket = bucket->_next;
        ++ _size;
    }
    return bucket->value;
}

template< typename key_type, typename mapped_type > 
typename HashTable<key_type,mapped_type>::bucket_type& 
HashTable<key_type,mapped_type>::at ( const key_type& key ){
    bucket_type* bucket = _table[_bucketIndex(key)];
    while( bucket->_next != 0 && bucket->key != key ){
        bucket = bucket->_next;
    }
    if( bucket->key != key ){
        bucket->_next = new bucket_type(key,mapped_type());
        bucket = bucket->_next;
    }
    return *bucket;
}
/*
// Element lookup
//    iterator                find  ( const key_type& );
*/
template< typename key_type, typename mapped_type > 
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::count ( const key_type& key ){
    bucket_type* bucket = _table[_bucketIndex(key)];
    size_type count = 0;
    while( bucket != 0 ){
        if( bucket->key == key ) 
            ++ count;
        bucket = bucket->_next;
    }
    
    return count;
}


// Modifiers
template< typename key_type, typename mapped_type > 
void HashTable<key_type,mapped_type>::insert ( bucket_type bucket ){
    insert( bucket.key, bucket.value );
}

template< typename key_type, typename mapped_type > 
void HashTable<key_type,mapped_type>::insert ( const key_type& key, 
                                               const mapped_type& value ){
    if( _table[_bucketIndex(key)] == 0 ){
        _table[_bucketIndex(key)] = new bucket_type( key, value );
    } else {
        bucket_type* currBucket = _table[_bucketIndex(key)];
        while( currBucket->_next != 0 ){
            currBucket = currBucket->_next;
        }
        currBucket->_next = new bucket_type( key, value );
    }
    ++ _size;
}

template< typename key_type, typename mapped_type > 
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::erase ( const key_type& ){
    bucket_type* currBucket = _table[_bucketIndex(key)];
    bucket_type* toDel = currBucket;
    size_type count = 0;
    while( currBucket != 0 ){
        if( currBucket->key == key ) {
            ++ count;
            currBucket = currBucket->next;
            delete toDel;
        } else {
            currBucket = currBucket->next;
        }
        toDel = currBucket;
    }
    
    return count;
}

template< typename key_type, typename mapped_type > 
void HashTable<key_type,mapped_type>::clear(){
    bucket_type* bucketPtr;
    bucket_type* toDel;
    for( int i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        bucketPtr = _table[i];
        toDel = bucketPtr;
        while( bucketPtr != 0 ){
            bucketPtr = bucketPtr->_next;
            delete toDel;
            toDel = bucketPtr;
        }
    }
    _size = 0;
    _bucketCount = 0;
}

// Hash policy
template< typename key_type, typename mapped_type > 
float HashTable<key_type,mapped_type>::loadFactor (){
    return ( float(_size) / float(_MAX_INDEX_SIZE) );
}
/*
// Friends
template< typename key_type, typename mapped_type >
std::ostream& HashTable<key_type,mapped_type>::
operator << ( std::ostream&, const HashTable< key_type, mapped_type > ){

}
*/

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hashKey( int key ){
    return (size_type)key;
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hashKey( float key ){
    return (size_type)key;
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hashKey( char key ){
    return (size_type)key;
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hashKey( const char* key ){
    size_type keyValue = 0;
    for( int i = 0; key[i] != 0; ++i ){
        keyValue += (size_type)key[i];
    }
    return keyValue;
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hashKey( std::string key ){
    size_type keyValue = 0;
    for( int i = 0; i < key.size(); ++i ){
        keyValue += (size_type)key[i];
    }
    return keyValue;
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_hash( const key_type& key ){
    size_type hashValue = _hashKey( key );
    return (( _DEFAULTS::HASH_MULT * hashValue + _DEFAULTS::HASH_ADD) 
                 % _DEFAULTS::HASH_MOD ); 
}

template< typename key_type, typename mapped_type >
typename HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::_bucketIndex( const key_type& key ){
    if( _hashPtr == 0 ){
        return _hash( key ) % _MAX_INDEX_SIZE;
    } 
    //else {
    //    return this->*_hashPtr(key) % _MAX_INDEX_SIZE;
    //}
}

#endif