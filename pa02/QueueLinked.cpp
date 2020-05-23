/**
@file  QueueLinked.cpp
@author  Christopher Eichstedt
@brief  An implementation file for a dynamically allocated node Queue 
**/

#include "QueueLinked.h"

//////////////////////////////////////////////////////////////////////////
//constructors and destructor
//////////////////////////////////////////////////////////////////////////

/**
@pre  none
@post  creates a node
@return  none
@param  DataType variable and a node pointer
@brief  default node constructor for the Queue class
**/
template <typename DataType>
QueueLinked<DataType> :: QueueNode :: QueueNode(const DataType& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

/**
@pre  none
@post  creates an empty node queue
@return  none
@param  none for the QueueLinked version
@brief  default constructor for the node queue
**/
template <typename DataType>
QueueLinked<DataType> :: QueueLinked(int maxNumber)
{
	front = back = NULL;
}

/**
@pre  requires enqueue() and clear()
@post  intializes a new node queue to be identical as the one passed through parameter
@return  none
@param  predefined node queue, QueueLinked
@brief  default copy constructor for a node queue
**/
template <typename DataType>
QueueLinked<DataType> :: QueueLinked(const QueueLinked& other)
{
	if(other.isEmpty())
	{
		front = back = NULL;
	}
	
	else
	{
		clear(); //just added, remove if error occurs
		QueueNode* temp;
		temp = other->front;
		
		while(temp != NULL)
		{
			enqueue(temp->dataItem);
			temp = temp->next;
		}
		
		temp = NULL;
	}
}

/**
@pre  requires enqueue() and clear()
@post  sets a node queue equal to another
@return  returns the current node queue
@param  a DataType defined node queue
@brief  assignment operator overload for a node queue
**/
template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType> :: operator=(const QueueLinked<DataType>& other)
{
	if(other.isEmpty())
	{
		front = back = NULL;
		return *this;
	}
	
	else if(this == &other)
	{
		return *this;
	}
	
	else
	{
		clear(); //just added, remove if error occurs
		QueueNode* temp;
		temp = other->front;
	
		while(temp != NULL)
		{
			enqueue(temp->dataItem);
			temp = temp->next;
		}
		
		temp = NULL;
		return *this;
	}
}

/**
@pre  requires clear()
@post  removes and deletes all node data from queue
@return  none
@param  none
@brief  default destructor for a node queue
**/
template <typename DataType>
QueueLinked<DataType> :: ~QueueLinked()
{
	this->clear();
}

//////////////////////////////////////////////////////////////////////////
//node queue functions
//////////////////////////////////////////////////////////////////////////

/**
@pre  requires isEmpty() and isFull()
@post  adds a new node to the Queue using FIFO logic
@return  none
@param  DataType to be passed into node
@brief  enqueue function for a dynamically allocated node queue
**/
template <typename DataType>
void QueueLinked<DataType> :: enqueue(const DataType& newDataItem) throw(logic_error)
{
	if(isEmpty())
	{
		QueueNode* temp = new QueueNode(newDataItem, NULL);
		front = back = temp;
		temp = NULL;
	}
	
	else if(isFull())
	{
		throw logic_error("enqueue() full list");
	}
	
	else
	{
		QueueNode* temp = new QueueNode(newDataItem, NULL);
		back->next = temp;
		back = temp;
		temp = NULL;
	} 
}

/**
@pre  requires isEmpty() and isFull()
@post  deletes a node from the queue using FIFO logic
@return  returns DataType variable
@param  none
@brief  dequeue function for a dynamically allocated node queue
**/
template <typename DataType>
DataType QueueLinked<DataType> :: dequeue() throw(logic_error)
{	
	if(isEmpty())
	{
		throw logic_error("dequeue() empty list");
	}
	
	DataType val = front->dataItem;
	QueueNode* temp;
	temp = front->next;
	delete front;
	front = temp;
	temp = NULL;
	return val;
}

/**
@pre  requires isEmpty()
@post  removes and deletes all node data from queue
@return  none
@param  none
@brief  clear function for a dynamically allocated node queue
**/
template <typename DataType>
void QueueLinked<DataType> :: clear()
{
	if(isEmpty())
	{
		return;
	}

	QueueNode* temp;
	temp = front->next;
	
	while(temp != NULL)
	{
		delete front;
		front = temp;
		temp = temp->next;
	}
	
	delete back;
	front = back = temp = NULL;
}

/**
@pre  none
@post  returns true or false if node queue is empty
@return  return a true or false statement based on condition
@param  none
@brief  isEmpty function for a dynamically allocated node queue
**/
template <typename DataType>
bool QueueLinked<DataType> :: isEmpty() const
{
	if(front == NULL)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

/**
@pre  none
@post  returns false because a node queue cannot be full
@return  returns false
@param  none
@brief  isFull function for a dynamically allocated node queue
**/
template <typename DataType>
bool QueueLinked<DataType> :: isFull() const
{
	return false;
}

//taken from show7-revised.cpp in the student starter kit, lab 07 folder
template <typename DataType>
void QueueLinked<DataType>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    // Iterates through the queue
	QueueNode* p;

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != NULL ; p = p->next )
	{
	    if( p == front )
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}

//////////////////////////////////////////////////////////////////////////
//programming exercise #2
//////////////////////////////////////////////////////////////////////////

/**
@pre  requires isEmpty() and isFull()
@post  moves a new node to the front of the queue
@return  none
@param  DataType variable to be passed into node
@brief  putFront function for a dynamically allocated node queue
**/
template <typename DataType>
void QueueLinked<DataType> :: putFront(const DataType& newDataItem) throw(logic_error)
{
	if(isEmpty())
	{
		enqueue(newDataItem);
	}
	
	else if(isFull())
	{
		throw logic_error("putFront() full list");
	}
	
	else
	{
		QueueNode* tempOldFront;
		tempOldFront = front;
		QueueNode* tempNewFront = new QueueNode(newDataItem, NULL);
	
		front = tempNewFront;
		front->next = tempOldFront;
		
		tempOldFront = tempNewFront = NULL;
	}
}

/**
@pre  none
@post  returns dataItem from back of node queue
@return  returns dataItem
@param  none
@brief  getRear function for a dynamically allocated node queue
**/
template <typename DataType>
DataType QueueLinked<DataType> :: getRear() throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("getRear() empty list");
	}
	
	else
	{
		return back->dataItem;
	}
}

//////////////////////////////////////////////////////////////////////////
//programming exercise #3
//////////////////////////////////////////////////////////////////////////

/**
@pre  none
@post  returns length of node queue
@return  returns int count
@param  none
@brief  getLength function for a dynamically allocated node queue
**/
template <typename DataType>
int QueueLinked<DataType> :: getLength() const
{
	QueueNode* temp;
	temp = front;
	int count = 0;
	
	while(temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	
	return count;
}
