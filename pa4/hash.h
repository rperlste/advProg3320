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
template< typename key_type, typename mapped_type > class FwIterator;
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
private:
    Bucket* _next;
};

/******************************************************************************/
// Forward iterator class for HashTable.
template< typename key_type, typename mapped_type >
class FwIterator {

public:
    typedef typename Bucket< key_type, mapped_type > bucket_type;

    FwIterator();
    FwIterator( bucket_type* nPtr );
    FwIterator( const FwIterator<key_type,mapped_type>& );
    ~FwIterator() {}

    // Comparison
    bool operator == ( const FwIterator<key_type,mapped_type>& it ) const;
    bool operator != ( const FwIterator<key_type,mapped_type>& it ) const;

    // Element access
    bucket_type&                   operator * ()  const;
    bucket_type*                   operator -> () const;

    // Modifiers
    void operator ++ ();
    void operator ++ ( int );
    void operator =  ( const FwIterator<key_type,mapped_type>& it );

    // Friends
    friend class HashTable< key_type, mapped_type >;

private:
    bucket_type*                   cursor;
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
    typedef FwIterator< key_type, mapped_type > iterator;
    typedef unsigned (HashTable<key_type,mapped_type>::*hashing_funct_ptr)
        ( const key_type& );

    // Construction
    HashTable( const HashTable< key_type, mapped_type >& );
    HashTable( size_type maxSize = _DEFAULTS::SIZE );
    HashTable( hashing_funct_ptr hashPtr, 
                size_type maxSize = _DEFAULTS::SIZE  );
    HashTable( bucket_type, 
                size_type maxSize = _DEFAULTS::SIZE );
    HashTable( bucket_type, 
                hashing_funct_ptr hashPtr, 
                size_type maxSize = _DEFAULTS::SIZE );
    HashTable( key_type, 
                mapped_type, 
                size_type maxSize = _DEFAULTS::SIZE );
    HashTable( key_type, 
                mapped_type, 
                hashing_funct_ptr hashPtr, 
                size_type maxSize = _DEFAULTS::SIZE );
    virtual ~HashTable();

    // Capacity
    inline bool             empty()    { return _size == 0; }
    inline size_type        size()     { return _size; }
    inline size_type        max_size() { return _MAX_INDEX_SIZE; }

    // Iterator
    iterator                begin ();
    iterator                end   ();

    // Element access
    mapped_type&            operator [] ( const key_type& );
    mapped_type&            at          ( const key_type& );

    // Element lookup
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
    friend class FwIterator< key_type, mapped_type >;

private:
    // Members
    size_type               _size;
    size_type               _MAX_INDEX_SIZE;
    bucket_type**                _table;


    // Hash function
    hashing_funct_ptr       _hashPtr;
    size_type               _hashKey( int );
    size_type               _hashKey( float );
    size_type               _hashKey( char );
    size_type               _hashKey( const char* );
    size_type               _hashKey( std::string );
    size_type               _hash( const key_type& );
    size_type               _bucketIndex( size_type );
};

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
HashTable( size_type maxSize ){
    _size = 0;
    _MAX_INDEX_SIZE = maxSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( hashing_funct_ptr hashPtr, 
           size_type maxSize  ){
    _size = 0;
    _MAX_INDEX_SIZE = maxSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( bucket_type bckt, unsigned maxSize ){
    _size = 1;
    _MAX_INDEX_SIZE = maxSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(bckt.key)] = new bucket_type(bckt.key, bckt.value);
}


template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
    HashTable( bucket_type bckt, hashing_funct_ptr hashPtr, size_type maxSize ){
    _size = 1;
    _MAX_INDEX_SIZE = maxSize;
    _table = new bucket_type*[_MAX_INDEX_SIZE];
    _hashPtr = 0;
    for( unsigned i = 0; i < _MAX_INDEX_SIZE; ++ i ){
        _table[i] = 0;
    }
    _table[_bucketIndex(bckt.key)] = new bucket_type(bckt.key, bckt.value);
}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::
HashTable( key_type key, mapped_type value, size_type maxSize ){
    _size = 1;
    _MAX_INDEX_SIZE = maxSize;
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
            size_type maxSize ){
    _size = 1;
    _MAX_INDEX_SIZE = maxSize;
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

// Element access
template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::mapped_type& 
HashTable<key_type,mapped_type>::operator [] ( const key_type& key ){

}

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::mapped_type& 
HashTable<key_type,mapped_type>::at ( const key_type& ){

}

// Element lookup
//    iterator                find  ( const key_type& );

template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::count ( const key_type& ){
}
*/

// Modifiers
template< typename key_type, typename mapped_type > 
void HashTable<key_type,mapped_type>::insert ( bucket_type bucket ){
    insert( bucket.key, bucket.value );
}

template< typename key_type, typename mapped_type > 
void HashTable<key_type,mapped_type>::insert ( const key_type& key, 
                                                const mapped_type& value ){
    unsigned hashIndex;
    if( _hashPtr == 0 ){
        hashIndex = _hashKey( key );
    }
    // else {
    //     hashIndex = this->*_hashPtr(key);
    //}
    if( _table[_bucketIndex(hashIndex)] == 0 ){
        _table[_bucketIndex(hashIndex)] = 
            new bucket_type( key, value );
    } else {
        bucket_type* currBucket = _table[_bucketIndex(hashIndex)];
        while( currBucket->_next != 0 ){
            currBucket = currBucket->_next;
        }
        currBucket->_next = new bucket_type( key, value );
    }
}
/*
template< typename key_type, typename mapped_type > 
HashTable<key_type,mapped_type>::size_type 
HashTable<key_type,mapped_type>::erase ( const key_type& ){

}
*/
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
/*
// Hash policy
template< typename key_type, typename mapped_type > 
float HashTable<key_type,mapped_type>::loadFactor (){

}

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
HashTable<key_type,mapped_type>::_bucketIndex( size_type index ){
    return index % _MAX_INDEX_SIZE;
}

#endif