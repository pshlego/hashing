#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
using namespace std;


int hash_own( const char * key);
int hash_own( const string & key );
int hash_own( int key );

int nextPrime( int n );

// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 )
      : currentSize( 0 )
      { theLists.resize( 101 ); }

    bool contains( const HashedObj & x ) const
    {
        const list<HashedObj> & whichList = theLists[ myhash( x ) ];
        return find( whichList.begin( ), whichList.end( ), x ) != whichList.end( );
    }

    void makeEmpty( )
    {
        for( int i = 0; i < theLists.size( ); i++ )
            theLists[ i ].clear( );
    }

    bool insert( const HashedObj & x )
    {
	    // FILL THIS
        typename list<HashedObj> & position = theLists[myhash(x)];
        //이미 존재하는 것이면 false return
        if (position.end()!=find(position.begin(),position.end(),x)) return false;
        //chain 앞에 추가하기
        position.push_front(x);
        //currentsize가 tablesize보다 크면 rehash
        if(++currentSize>theLists.size()) rehash();
        return true;
    }

    bool remove( const HashedObj & x )
    {
	    // FILL THIS
        list<HashedObj> & position = theLists[myhash(x)];
        //이미 존재하는 것이면 false return
        if(position.end()!=find(position.begin(),position.end(),x)) return false;       
        //x의 위치로 iterator 초기화
        list<HashedObj>::iterator itr = find(position.begin(),position.end(),x);
        //삭제
        position.erase(itr);
        --currentSize;
        return true;
    }

  private:
    vector<list<HashedObj> > theLists;   // The array of Lists
    int  currentSize; //global variable

    void rehash( )
    {
        vector<list<HashedObj> > oldLists = theLists;

            // Create new double-sized, empty table
        theLists.resize( nextPrime( 2 * theLists.size( ) ) );
        for( int j = 0; j < theLists.size( ); j++ )
            theLists[ j ].clear( );

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldLists.size( ); i++ )
        {
            typename list<HashedObj>::iterator itr = oldLists[ i ].begin( );
            while( itr != oldLists[ i ].end( ) )
                insert( *itr++ );
        }
    }

    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash_own( x );

        hashVal %= theLists.size( );
        if( hashVal < 0 )
            hashVal += theLists.size( );

        return hashVal;
    }

    
};


#endif
