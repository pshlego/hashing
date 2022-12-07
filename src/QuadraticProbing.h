#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <string>
using namespace std;

int nextPrime( int n );

int hash_own( const char * key);
int hash_own( const string & key );
int hash_own( int key );


// QuadraticProbing Hash table class
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
    explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        return isActive( findPos( x ) );
    }

    void makeEmpty( )
    {
        currentSize = 0;
        for( int i = 0; i < array.size( ); i++ )
            array[ i ].info = EMPTY;
    }

    bool insert( const HashedObj & x )
    {
	// FILL THIS 
	//
    int position_of_x = findPos(x);
    //이미 존재하면 false
    if(isActive(position_of_x)) return false;
    array[position_of_x].info = ACTIVE;
    array[position_of_x].element = x;
    if(++currentSize>array.size()) rehash();
    return true;
    }
    bool remove( const HashedObj & x )
    {
	// FILL THIS 
	//
    int position_of_x = findPos(x);
    //존재하지 않는다면
    if(!isActive(position_of_x)) return false;
    //삭제되었음을 알려주기 위해서 flag를 만듬
    array[position_of_x] = DELETED;
    return true;
    }
    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
	    // FILL THIS
        int i = 1;
        int position_of_x = findPos(x);
        while(array[position_of_x].info != EMPTY && array[position_of_x].element !=x){
            //1,3,5,9,16
            position_of_x+=i;
            i+=2;
            if(position_of_x>=array.size()) position_of_x-=array.size();

        }
        return position_of_x;
    }

    void rehash( )
    {
        vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
        array.resize( nextPrime( 2 * oldArray.size( ) ) );
        for( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

            // Copy table over
        currentSize = 0;
        for( int i = 0; i < oldArray.size( ); i++ )
            if( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );
    }
    int myhash( const HashedObj & x ) const
    {
        int hashVal = hash_own( x );

        hashVal %= array.size( );
        if( hashVal < 0 )
            hashVal += array.size( );

        return hashVal;
    }
};

#endif
