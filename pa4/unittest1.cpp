#include "stdafx.h"
#include "CppUnitTest.h"
#include "hash.h"

#include <cassert>
#include <sstream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pa4_test
{		
    // Test constants
    const char char1 = 'a';
    const char char2 = 'b';
    const int int1 = 1;
    const int int2 = 2;
    const int int3 = 3;
    const float float1 = 1.1;
    const float float2 = 2.2;

    TEST_CLASS(TestBucket)
    {
    public:
        TEST_METHOD(Bucket_Ctors)
        {
            Bucket<int,int> b1(int1,int1);
            Bucket<int,int> b2(int2,int2,&b1);
            Bucket<int,int> b3(b2);
        }
        TEST_METHOD(Bucket_Elements)
        {
            Bucket<char,char> b1(char1,char2);
            Assert::AreEqual( char1, b1.key );
            Assert::AreEqual( char2, b1.value );
            Bucket<char,char> b2(char1,char2,&b1);
            Assert::AreEqual( char1, b2.key );
            Assert::AreEqual( char2, b2.value );
            Bucket<char,char> b3(b2);
            Assert::AreEqual( char1, b3.key );
            Assert::AreEqual( char2, b3.value );
        }
    };

    TEST_CLASS(TestIterator)
    {
    public:
        TEST_METHOD(It_Ctors)
        {
            HashTableIterator<int,int> it1;

            Bucket<char,int> b(char1,int1);
            HashTable<char,int> ht(b);
            HashTableIterator<char,int> it2(&ht.at(char1), &ht);

            HashTableIterator<char,int> it3(it2);
        }
        TEST_METHOD(It_operatorNotEqual)
        {
            Bucket<char,int> b1(char1,int1);
            Bucket<char,int> b2(char2,int2);
            HashTable<char,int> ht(b1);
            ht.insert(b2);

            HashTableIterator<char,int> it1;
            HashTableIterator<char,int> it2(&ht.at(char1), &ht);
            assert( it1 != it2 );

            HashTableIterator<char,int> it3(&ht.at(char2), &ht);
            HashTableIterator<char,int> it4(&ht.at(char1), &ht);
            assert( it3 != it4 );

        }
        TEST_METHOD(It_operatorStar)
        {
            Bucket<char,int> b1(char1,int1);
            HashTable<char,int> ht(b1);
            HashTableIterator<char,int> it(&ht.at(char1), &ht);
            Bucket<char,int> b2(*it);
            Assert::AreEqual( b1.key, b2.key );
            Assert::AreEqual( b1.value, b2.value );
        }
        TEST_METHOD(It_operatorPlusPlus)
        {
            Bucket<char,int> b1(char1,int1);
            Bucket<char,int> b2(char1,int2);
            Bucket<char,int> b3(char1,int3);
            HashTable<char,int> ht(b1);
            ht.insert(b2);
            ht.insert(b3);
            HashTableIterator<char,int> it(&ht.at(char1), &ht);
            Assert::AreEqual( char1, it->key );
            Assert::AreEqual( int1, it->value );
            ++ it;
            Assert::AreEqual( char1, it->key );
            Assert::AreEqual( int2, it->value );
            it ++;
            Assert::AreEqual( char1, it->key );
            Assert::AreEqual( int3, it->value );
        }

        TEST_METHOD(It_operatorAssignment)
        {
            Bucket<char,int> b1(char1,int1);
            Bucket<char,int> b2(char2,int2);
            HashTable<char,int> ht(b1);
            ht.insert(b2);

            HashTableIterator<char,int> it1;
            HashTableIterator<char,int> it2(&ht.at(char1), &ht);

            it1 = it2;
            assert( it1 == it2 );

        }

        TEST_METHOD(It_operatorEquals)
        {
            Bucket<char,int> b1(char1,int1);
            Bucket<char,int> b2(char2,int2);
            HashTable<char,int> ht(b1);
            ht.insert(b2);

            HashTableIterator<char,int> it1(&ht.at(char1), &ht);
            HashTableIterator<char,int> it2(&ht.at(char1), &ht);
            assert( it1 == it2 );
        }

        TEST_METHOD(It_operatorArror)
        {
            Bucket<char,int> b1(char1,int1);
            Bucket<char,int> b2(char2,int2);
            HashTable<char,int> ht(b1);
            ht.insert(b2);

            HashTableIterator<char,int> it1(&ht.at(char1), &ht);
            Assert::AreEqual(char1, it1->key);
            Assert::AreEqual(int1, it1->value);
        }
    };


    TEST_CLASS(TestHashTable)
    {
    public:

        unsigned foo( const char& ){ return 1; }
        
        TEST_METHOD(HT_Ctor)
        {
            HashTable<char,int> ht;
        }

        TEST_METHOD(HT_CtorBucket)
        {
            Bucket<char,int> b(char1,int1);
            HashTable<char,int> ht1(b);
        }

        TEST_METHOD(HT_CtorKeyVal)
        {
            HashTable<float,float> ht( float1, float2 );
        }

        TEST_METHOD(HT_CopyCtor)
        {
            HashTable<char,int> ht1;
            HashTable<char,int> ht2(ht1);

            HashTable<int,int> ht3( 1, 1 );
            HashTable<int,int> ht4(ht3);

            Bucket<char,int> b('a',int1);
            HashTable<char,int> ht5(b);
            HashTable<char,int> ht6(ht5);
        }

        TEST_METHOD(HT_at)
        {
            Bucket<char,int> b(char1,int1);
            HashTable<char,int> ht(b);
            Bucket<char,int> c(ht.at(char1));
            Assert::AreEqual( char1, c.key );
            Assert::AreEqual( int1, c.value );
        }

        TEST_METHOD(HT_begin)
        {
            HashTable<int,int> ht(10);
            HashTableIterator<int,int> it = ht.begin();
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            
            ht.insert(b1);
            ht.insert(b2);

            it = ht.begin();
            ++ it;
            ++ it;
        }

        TEST_METHOD(HT_clear)
        {
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            HashTable<int,int> ht;
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b2);
            ht.insert(b2);

            Assert::AreEqual( unsigned(5), ht.size() );
            ht.clear();
            Assert::AreEqual( unsigned(0), ht.size() );
            assert( ht.begin() == ht.end() );
        }

        TEST_METHOD(HT_count)
        {
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int1,int1);
            HashTable<int,int> ht;
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b2);
            ht.insert(b2);
            Assert::AreEqual( unsigned(5), ht.count( int1 ) );
        }

        TEST_METHOD(HT_empty)
        {
            HashTable<int,int> ht;
            Assert::IsTrue( ht.empty() );
            ht.insert(int1,int1);
            Assert::IsFalse( ht.empty() );
        }

        TEST_METHOD(HT_end)
        {
            HashTable<int,int> ht(10);
            HashTableIterator<int,int> it = ht.begin();
            assert( it == ht.end() );
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            
            ht.insert(b1);
            ht.insert(b2);

            it = ht.begin();
            assert( it != ht.end() );
        }

        TEST_METHOD(HT_erase)
        {
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            HashTable<int,int> ht;
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b2);
            ht.insert(b2);
            Assert::AreEqual( unsigned(3), ht.count( int1 ) );
        }

        TEST_METHOD(HT_find)
        {
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            HashTable<int,int> ht;
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b2);
            ht.insert(b2);
            
            HashTableIterator<int,int> it = ht.find( int1 );
            Assert::AreEqual( int1, it->key );
            Assert::AreEqual( int2, it->value );
            ++ it;
            Assert::AreEqual( int1, it->key );
            Assert::AreEqual( int2, it->value );
            ++ it;
            Assert::AreEqual( int1, it->key );
            Assert::AreEqual( int2, it->value );
        }

        TEST_METHOD(HT_insert)
        {
            Bucket<int,int> b(int1,int2);
            HashTable<int,int> ht;
            ht.insert(b);
            Assert::AreEqual( int2, ht[int1] );
        }

        TEST_METHOD(HT_loadFactor)
        {
            Bucket<int,int> b(int1,int2);
            HashTable<int,int> ht(b,2);
            Assert::AreEqual( float(0.5), ht.loadFactor() );
        }

        TEST_METHOD(HT_indexSize)
        {
            HashTable<int,int> ht(int2);
            Assert::AreEqual( unsigned(int2), ht.indexSize() );
        }

        TEST_METHOD(HT_size)
        {
            HashTable<int,int> ht;
            Assert::AreEqual( unsigned(0), ht.size() );
            ht.insert(int1,int1);
            Assert::AreEqual( unsigned(1), ht.size() );
            ht.insert(int2,int2);
            Assert::AreEqual( unsigned(2), ht.size() );
        }

        TEST_METHOD(HT_OperatorBracker)
        {
            HashTable<int,int> ht(int1,int2,2);
            Assert::AreEqual( int2, ht[int1] );
            ht[int2] = int1;
            Assert::AreEqual( int1, ht[int2] );
        }

        TEST_METHOD(HT_OperatorOstream)
        {
            Bucket<int,int> b1(int1,int2);
            Bucket<int,int> b2(int2,int1);
            HashTable<int,int> ht;
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b1);
            ht.insert(b2);
            ht.insert(b2);

            std::stringstream ss;
            ss << ht;
            Logger::WriteMessage( ss.str().c_str() );
        }
    };
}