#include "stdafx.h"
#include "CppUnitTest.h"
#include "hash.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pa4_test
{		
    // Test constants
    const char char1 = 'a';
    const char char2 = 'b';
    const int int1 = 1;
    const int int2 = 2;

    TEST_CLASS(TestBucket)
    {
    public:
        TEST_METHOD(BucketCtors)
        {
            Bucket<int,int> b1(int1,int1);
            Bucket<int,int> b2(int2,int2,&b1);
            Bucket<int,int> b3(b2);
        }
        TEST_METHOD(BucketElements)
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

    TEST_CLASS(TestHashTable)
    {
    public:
        
        TEST_METHOD(HT_Ctor)
        {
            HashTable<char,int> ht;
        }

        TEST_METHOD(HT_BucketCtor)
        {
            Bucket<char,int> b('a',1);
            HashTable<char,int> ht(b);
        }

        TEST_METHOD(HT_CopyCtor)
        {
            HashTable<char,int> ht1;
            HashTable<char,int> ht2(ht1);

            HashTable<int,int> ht3( 1, 1 );
            HashTable<int,int> ht4(ht3);
        }

    };
}