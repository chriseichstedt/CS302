/**
@file  HashTable.cpp
@author  Christopher Eichstedt
@brief  An implementation file for a HashTable
**/

#include "HashTable.h"
#include "show10.cpp"

using namespace std;

/**
@pre  none	
@post  creates a HashTable
@param  int variable
@return  none
@brief  "Constructor. Creates the empty hash table."
**/
template <typename DataType, typename KeyType>
HashTable <DataType, KeyType> :: HashTable (int initTableSize)
{
	tableSize = initTableSize;
	dataTable = new BSTree<DataType, KeyType> [initTableSize];
}

/**
@pre  none
@post  copies a HashTable from other to the current HashTable
@param  HashTable variable
@return  none
@brief  "Copy Constructor. Initializes the hash table to be equivalent to the HashTable object parameter other."
**/
template <typename DataType, typename KeyType>
HashTable <DataType, KeyType> :: HashTable (const HashTable &other)
{
	*this = other;
}

/**
@pre  clear()
@post  sets the current HashTable equivalent to other
@param  HashTable variable
@return  returns the current HashTable
@brief  "Overloaded assignment operator. Sets the hash table to be equivalent to the other HashTable object parameter and returns a reference to this object."
**/
template<typename DataType, typename KeyType>
HashTable <DataType, KeyType>& HashTable<DataType, KeyType> :: operator= (const HashTable& other)
{
	if(*this == other)
	{
		return *this;
	}
	
	else
	{
		clear();
		copyTable(other);
		return *this;
	}
}

/**
@pre  clear()
@post  clears the current HashTable
@param  none
@return  none
@brief  "Destructor. Deallocates (frees) the memory used to store a hash table."
**/
template <typename DataType, typename KeyType>
HashTable <DataType, KeyType> :: ~HashTable ()
{
	clear();
}

/**
@pre  none
@post  inserts the data item, or updates the current data item in the binary search tree
@param  DataType variable
@return  none
@brief  "Inserts newDataItem into the appropriate binary search tree. If a data item with the same key as newDataItem already exists in the binary search tree, then updates the data item with newDataItem. Otherwise, it inserts it in the binary search tree."
**/
template <typename DataType, typename KeyType>
void HashTable <DataType, KeyType> :: insert (const DataType& newDataItem)
{
	int index = newDataItem.hash(newDataItem.getKey()) % tableSize;
	dataTable[index].insert(newDataItem);
}

/**
@pre  none
@post  removes the deleteKey from the binary search tree
@param  KeyType variable
@return  returns true or false, if the item was found
@brief  "Searches the hash table for the data item with the key deleteKey. If the data item is found, the removes the data item and returns true. Otherwise, returns false."
**/
template <typename DataType, typename KeyType>
bool HashTable <DataType, KeyType> :: remove (const KeyType& deleteKey)
{
	DataType temp;
	int index = temp.hash(deleteKey) % tableSize;
	return dataTable[index].remove(deleteKey);
}

/**
@pre  none
@post  returns true or false, depending on searchKey
@param  KeyType and DataType variables
@return  returns true if searchKey is found, else false
@brief  "Searches the hash table for the data item with key searchKey. If the data item is found. then copies the data item to returnItem and returns true. Otherwise, returns false with returnItem undefined."
**/
template <typename DataType, typename KeyType>
bool HashTable <DataType, KeyType> :: retrieve (const KeyType& searchKey, DataType& returnItem) const
{
	int index = returnItem.hash(searchKey) % tableSize;
	return dataTable[index].retrieve(searchKey, returnItem);
}

/**
@pre  none
@post  all data items are removed from HashTable
@param  none
@return  none
@brief  "Removes all data items in the hash table."
**/
template <typename DataType, typename KeyType>
void HashTable <DataType, KeyType> :: clear ()
{
	for (int i = 0; i < tableSize; i++)
	{
		dataTable[i].clear();
	}
}

/**
@pre  none
@post  returns true or false, depending if HashTable is empty
@param  none
@return  true if hashTable is empty, false if it isn't
@brief  "Returns true if the hash table is empty. Otherwise, returns false."
**/
template <typename DataType, typename KeyType>
bool HashTable <DataType, KeyType> :: isEmpty () const
{
	for (int i = 0; i < tableSize; i++)
	{
		if (dataTable[i].isEmpty() == false)
		{
			return false;
		}
	}
	
	return true;
}

/**
@pre  none
@post  copies the source HashTable to the current
@param  HashTable variable
@return  none
@brief  A function that makes a copy of the source HashTable, into the current.
**/
template <typename DataType, typename KeyType>
void HashTable <DataType, KeyType> :: copyTable (const HashTable& source)
{
	delete dataTable;
	dataTable = new BSTree <DataType, KeyType>[source.tableSize];
	
	for (int i = 0; i < tableSize; i++)
	{
		dataTable[i] = source.dataTable[i];
	}
}

/////////////////////////////////////////////////////////////////////
//programming exercise #3, not required
/////////////////////////////////////////////////////////////////////
template <typename DataType, typename KeyType>
double HashTable <DataType, KeyType> :: standardDeviation () const
{
}
