/**
	ListLinked.cpp 
	Created by Christopher Eichstedt 
	
	This is the implementation file for a dynamically allocated, singly linked list.
	Below are all of the functions with brief descriptions.
**/

#include "ListLinked.h"

//------------------------------------------------------------------------
//Constructor & Destructor declarations
//------------------------------------------------------------------------

//default node constructor
template <typename DataType>
List<DataType> :: ListNode :: ListNode(const DataType& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

//default list constructor
template <typename DataType>
List<DataType> :: List (int ignored)
{
	head = cursor = NULL;
}

//copy constructor
template <typename DataType>
List<DataType> :: List(const List& other)
{
	if(other.isEmpty())
	{
		head = cursor = NULL;
	}
	
	else
	{
		ListNode* tempCopy = new ListNode(other.head->dataItem, NULL);
		ListNode* tempTravel = other.head->next;
		head = tempCopy;
		
		while(tempTravel != NULL)
		{
			if(tempTravel == other.cursor)
			{
				cursor = tempCopy;
			}
			
			ListNode* nextItem = new ListNode(tempTravel->dataItem, NULL);
			tempCopy->next = nextItem;
			tempTravel = tempTravel->next;
			tempCopy = tempCopy->next;
		}
		
		tempCopy = tempTravel = NULL;
	}
}

//overloaded assignment operator
template <typename DataType>
List<DataType>& List<DataType> :: operator=(const List<DataType>& other)
{
	if(other.isEmpty())
	{
		head = cursor = NULL;
	}
	
	else if(this == &other)
	{
		return *this;
	}
	
	else
	{
		ListNode* tempCopy = new ListNode(other.head->dataItem, NULL);
		ListNode* tempTravel = other.head->next;
		head = tempCopy;
		
		while(tempTravel != NULL)
		{
			if(tempTravel == other.cursor)
			{
				cursor = tempCopy;
			}
			
			ListNode* nextItem = new ListNode(tempTravel->dataItem, NULL);
			tempCopy->next = nextItem;
			tempTravel = tempTravel->next;
			tempCopy = tempCopy->next;
		}
		
		tempCopy = tempTravel = NULL;
	}
}

//destructor
template <typename DataType>
List<DataType> :: ~List()
{
	this->clear();
}

//------------------------------------------------------------------------
//Function declarations
//------------------------------------------------------------------------

//insert node into list
template <typename DataType>
void List<DataType> :: insert(const DataType& newDataItem) throw(logic_error)
{	
	if (isEmpty())
	{
		ListNode *temp = new ListNode(newDataItem, NULL);
		head = temp;
		cursor = head;
		temp = NULL;
	}
	
	else if (isFull())
	{
		throw logic_error("insert() full list");
	}
	
	else
	{
		ListNode *temp = new ListNode(newDataItem, NULL);
		temp->next = cursor->next;
		cursor->next = temp;
		cursor = temp;
		temp = NULL;
	}
}

//remove node from list
template <typename DataType>
void List<DataType> :: remove() throw(logic_error)
{
	if (isEmpty())
	{
		throw logic_error("remove() empty list");
	}

	else if (head == cursor)
	{
		cursor = cursor->next;
		delete head;
		head = cursor;
	}
	
	else if (head->next == cursor)
	{
		cursor = cursor->next;
		delete head->next;
		head->next = cursor;
		cursor = head;
	}
	
	else if (cursor->next == NULL)
	{
		ListNode* temp;
		temp = head;
		
		while(temp->next != cursor)
		{
			temp = temp->next;
		}
		
		temp->next = NULL;
		delete cursor;
		cursor = head;
		temp = NULL;
	}
	
	else
	{	
		ListNode* temp;
		temp = head;
		
		while(temp->next != cursor)
		{
			temp = temp->next;
		}
		
		temp->next = cursor->next;
		delete cursor;
		cursor = temp->next;
		temp = NULL;
	}	
}

//replaces the data at cursor node
template <typename DataType>
void List<DataType> :: replace(const DataType& newDataItem) throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("replace() empty list");
	}
	
	else
	{
		cursor->dataItem = newDataItem;
	}
}

//clears the list
template <typename DataType>
void List<DataType> :: clear()
{
	if(isEmpty())
	{
		return;
	}
	
	else
	{
		ListNode *temp = head->next;
	
		while(head->next != NULL)
		{
			delete head;
			head = temp;
			temp = temp->next;	
		}
	
		delete head;
		
		head = cursor = temp = NULL;
	}
}

//checks to see if the list is empty
template <typename DataType>
bool List<DataType> :: isEmpty() const
{
	if(head == NULL)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

//checks to see if the list is full
template <typename DataType>
bool List<DataType> :: isFull() const
{
	return false;
}

//moves cursor to the beginning of list
template <typename DataType>
void List<DataType> :: gotoBeginning() throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("gotoBeginning() empty list");
	}
	
	else if (cursor == head)
	{
		return;
	}
	
	else
	{
		cursor = head;
	}
}

//moves cursor to the end of list
template <typename DataType>
void List<DataType> :: gotoEnd() throw (logic_error)
{
	if(isEmpty())
	{
		throw logic_error("gotoEnd() empty list");
	}
	
	else if(cursor->next == NULL)
	{
		return;
	}
	
	else
	{
		ListNode* temp = new ListNode(head->dataItem, head->next);
		
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		
		cursor = temp;
		temp = NULL;
	}
}

//moves cursor to the next node
template <typename DataType>
bool List<DataType> :: gotoNext() throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("gotoNext() empty list");
	}
	
	else if(cursor->next == NULL)
	{
		return false;
	}
	
	else
	{
		cursor = cursor->next;
		return true;
	}
}

//moves cursor to prior node
template <typename DataType>
bool List<DataType> :: gotoPrior() throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("gotoPrior() empty list");
	}
	
	else if(cursor == head)
	{
		return false;
	}
	
	else
	{
		ListNode* temp;
		temp = head;
		
		while(temp->next != cursor)
		{
			temp = temp->next;
		}
		
		cursor = temp;
		temp = NULL;
		return true;
	}
}
//returns the data value at the cursor
template <typename DataType>
DataType  List<DataType> :: getCursor () const throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("getCursor() empty list");
	}
	
	else
	{
		return cursor->dataItem;
	}
}

//////////////////////////////////////////////////////////////////////////
//Programming Exercise #2
//////////////////////////////////////////////////////////////////////////

//moves cursor data item to head
template <typename DataType>
void List<DataType> :: moveToBeginning() throw(logic_error)
{
	if(isEmpty())
	{
		throw logic_error("moveToBeginning() empty list");
	}
	
	else
	{
		DataType cursVal = cursor->dataItem;
  		DataType headVal = head->dataItem;
    
   		head->dataItem = cursVal;
   		cursor->dataItem = headVal;
   		
   		cursor = head;
 	}
}

//////////////////////////////////////////////////////////////////////////
//Programming Exercise #3
//////////////////////////////////////////////////////////////////////////

//insert data before the cursor, moves cursor to the new data node
template <typename DataType>
void List<DataType> :: insertBefore(const DataType& newDataItem) throw(logic_error)
{
	if(isEmpty())
  	{
		ListNode *temp = new ListNode(newDataItem, NULL);
		head = temp;
		cursor = head;
		temp = NULL;
 	}
  
  	else if (cursor == head)
  	{
  		ListNode *temp = new ListNode(newDataItem, head);
		head = temp;
		cursor = head;
		temp = NULL;
  	}
  
  	else
  	{
		ListNode* temp = new ListNode(head->dataItem, head->next);
		
		while(temp->next != cursor)
		{
			temp = temp->next;
		}
  	
    		ListNode* tempNewData = new ListNode(newDataItem, cursor);
    		cursor = temp;
    		cursor->next = tempNewData;
    		cursor = tempNewData;
    		temp = tempNewData = NULL;
  }
}

//taken from show5.cpp in student starter kit, lab 05 folder
template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}
