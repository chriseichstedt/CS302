/**
@file  Heap.cpp
@author  Christopher Eichstedt
@brief  An implementation file for a Heap
**/

#include "Heap.h"
#include "show11.cpp"

using namespace std;

/**
@param  int maxNumber
@return  none
@brief  "Constructor. Creates an empty heap. Allocates enoughy memory for a heap containing maxNumber data items."
**/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator> :: Heap(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	dataItems = new DataType[maxSize];
}

/**
@param  const Heap& other
@return  none
@brief  "Copy constructor. Initializes the object to be an equivalent copy of other."
**/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator> :: Heap(const Heap<DataType, KeyType, Comparator>& other)
{
	*this = other;
}

/**
@param  const Heap& other
@return  *this
@brief  "Overloaded assignment operator. Sets the heap to be equivalent to the other Heap and returns a reference to this object."
**/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator> :: operator=(const Heap<DataType, KeyType, Comparator>& other)
{
	if(*this == &other)
	{
		return *this;
	}
	
	clear();
	
	size = other.size;
	maxSize = other.maxSize;
	
	for(int i = 0; i < size; i++)
	{
		dataItems[i] = other.dataItems[i];
	}
	
	return *this;
}

/**
@param  none
@return  none
@brief  "Destructor. Deallocates (free) the memory used to store the heap."
**/
template<typename DataType, typename KeyType, typename Comparator>
Heap<DataType, KeyType, Comparator> :: ~Heap()
{
	clear();
	delete dataItems;
}

/**
@param  const DataType& newDataItem
@return  none
@brief  "Inserts newDataItem into the heap. Inserts this data item as the bottom rightmost data item in the heap and moves it upward until the properties that define a heap are restored."
**/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator> :: insert(const DataType& newDataItem) throw(logic_error)
{
	if(!isFull())
	{
		size++;
		dataItems[size - 1] = newDataItem;
		sortUp(size - 1);
	}
	
	else
	{
		throw logic_error("Full List");
	}
}

/**
@param  const int nodeIndex
@return  none
@brief  The sortUp function that recursively sorts for insert()
**/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator> :: sortUp(const int nodeIndex)
{
		int parent;
		DataType temp;
		Comparator check;
	
		if(nodeIndex != 0)
		{
			parent = getParent(nodeIndex);
			if(check(dataItems[nodeIndex].getPriority(), dataItems[parent].getPriority()))
			{
				temp = dataItems[parent];
				dataItems[parent] = dataItems[nodeIndex];
				dataItems[nodeIndex] = temp;
				sortUp(parent);
			}
		}
}

/**
@param  none
@return  Datatype temp
@brief  "Removes the data item with the highest priority (the root) from the heap and returns it. Replaces the root data item with the bottom rightmost data item and moves this data item downward until the properties that define a heap are restored."
**/
template<typename DataType, typename KeyType, typename Comparator>
DataType Heap<DataType, KeyType, Comparator> :: remove() throw(logic_error)
{
	if(!isEmpty())
	{
		DataType temp = dataItems[0];
		dataItems[0] = dataItems[size - 1];
		size--;
		
		if(size > 0)
		{
			sortDown(0);
		}
		
		return temp;
	}
	
	else
	{
		throw logic_error("Empty List");
	}
}

/**
@param  const int nodeIndex
@return  none
@brief  The sortDown function that recursively sorts for remove()
**/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator> :: sortDown(const int nodeIndex)
{
	DataType temp;
	int largest;
	int left = getLeftChild(nodeIndex);
	int right = getRightChild(nodeIndex);
	Comparator check;
	
	if(right >= size)
	{
		if(left >= size)
		{
			return;
		}
		
		else
		{
			largest = left;
		}
	}
	
	else
	{
		if(check(dataItems[left].getPriority(), dataItems[right].getPriority()))
		{
			largest = left;
		}
		
		else
		{
			largest = right;
		}
	}
	
	/**
	if(check(dataItems[right].getPriority(), dataItems[left].getPriority()))
	{
		largest = right;
	}
	**/
	
	if(check(dataItems[largest].getPriority(), dataItems[nodeIndex].getPriority()))
	{
		temp = dataItems[nodeIndex];
		dataItems[nodeIndex] = dataItems[largest];
		dataItems[largest] = temp;
		sortDown(largest);
	}
}

/**
@param  none
@return  none
@brief  "Removes all the data items in the heap."
**/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator> :: clear()
{
	size = 0;
}

/**
@param  none
@return  true or false
@brief  "Returns true if the heap is empty. Otherwise, returns false."
**/
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator> :: isEmpty() const
{
	if(size == 0)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

/**
@param  none
@return  true or false
@brief  "Returns true if the heap is full. Otherwise, returns false."
**/
template<typename DataType, typename KeyType, typename Comparator>
bool Heap<DataType, KeyType, Comparator> :: isFull() const
{
	if(size == maxSize)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

/**
@param  const int nodeIndex
@return  (2 * nodeIndex + 1)
@brief  returns the left child
**/
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator> :: getLeftChild(const int nodeIndex) const
{
	return((2 * nodeIndex) + 1);
}

/**
@param  const int nodeIndex
@return  (2 * nodeIndex + 2)
@brief  returns the right child
**/
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator> :: getRightChild(const int nodeIndex) const
{
	return((2 * nodeIndex) + 2);
}

/**
@param  const int nodeIndex
@return  (nodeIndex / 2) - 1 or (nodeIndex / 2)
@brief  returns the parent
**/
template<typename DataType, typename KeyType, typename Comparator>
int Heap<DataType, KeyType, Comparator> :: getParent(const int nodeIndex) const
{
	return ((nodeIndex - 1) / 2);
}
/////////////////////////////////////////////////////////////////////
//programming exercise #3
/////////////////////////////////////////////////////////////////////
/**
@param  none
@return  none
@brief  "Outputs the data items in a heap in level order, one level per line. Only outputs each data item's priority. If the heap is empty, then outputs 'Empty heap'."
**/
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator> :: writeLevels() const
{
	int levelNum = 1;
	int printNum = 0;
	
	for(int i = 0; i < size; i++, printNum++)
	{
		if(printNum == levelNum)
		{
			cout << endl;
			printNum = 0;
			levelNum *= 2;
		}
		cout << dataItems[i].getPriority() << " ";
	}
	
	cout << endl;
}
