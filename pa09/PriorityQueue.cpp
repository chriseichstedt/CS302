/**
@file  PriorityQueue.cpp
@author  Christopher Eichstedt
@brief  An implementation file for a Priorty Queue
**/

#include "PriorityQueue.h"

using namespace std;

/**
@param  int maxNumber
@return  none
@brief  The default constructor for the PriorityQueue
**/
template<typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator> :: PriorityQueue(int maxNumber)
{
	//Heap<DataType, KeyType, Comparator> :: Heap(maxNumber);
}

/**
@param  const DataType& newDataItem
@return  none
@brief  enqueue function for the PriortyQueue, it calls the insert function within the Heap ADT
**/
template<typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator> :: enqueue(const DataType& newDataItem)
{
	Heap<DataType, KeyType, Comparator> :: insert(newDataItem);
}

/**
@param  none
@return  none
@brief  dequeue function for the PriortyQueue, it calls the remove function within the Heap ADT
**/
template<typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator> :: dequeue()
{
	return Heap<DataType, KeyType, Comparator> :: remove();
}
