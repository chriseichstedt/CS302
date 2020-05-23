/**
@file  BSTree.cpp
@author  Christopher Eichstedt
@brief  An implementation file for a Binary Search Tree
**/

#include "BSTree.h"

//////////////////////////////////////////////////////////////////////////
//function declarations
//////////////////////////////////////////////////////////////////////////

/**
@pre  none
@post  creates a BSTreeNode
@param  DataType variable and two BSTreeNodes
@return  none
@brief  default BSTreeNode constructor
**/
template <typename DataType, class KeyType>
BSTree <DataType, KeyType> :: BSTreeNode :: BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

/**
@pre  none
@post  creates a BSTree
@param  none
@return  none
@brief  default BSTree constructor
**/
template <typename DataType, class KeyType>
BSTree <DataType, KeyType> :: BSTree()
{
	root = NULL;	
}

/**
@pre  none
@post  creates a parameterized BSTree
@param  BSTree variable
@return  none
@brief  copy BSTree constructor
**/
template <typename DataType, class KeyType>
BSTree <DataType, KeyType> :: BSTree(const BSTree<DataType, KeyType> &other)
{
	*this = other;
}

/**
@pre  copyConstructor_Helper()
@post  sets the current BSTree equal to another
@param  BSTree variable
@return  returns the current BSTree
@brief  overloaded assignment operator
**/
template <typename DataType, class KeyType>
BSTree <DataType, KeyType>& BSTree <DataType, KeyType> :: operator=(const BSTree<DataType, KeyType>& source)
{
	if (*this == source)
	{
		return *this;
	}
	
	else
	{
		copyConstructor_helper(root, source.root);
		return *this;
	}
}

/**
@pre  clear()
@post  none
@param  none
@return  none
@brief  default BSTree destructor
**/
template <typename DataType, class KeyType>
BSTree <DataType, KeyType> :: ~BSTree()
{
	clear();
}

/**
@pre  insert_Helper()
@post  none
@param  Datatype variable
@return  none
@brief  insert() function that calls insert_Helper()
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: insert(const DataType& newDataItem)
{
	insert_Helper(newDataItem, root);
}

/**
@pre  retrieve_Helper()
@post  none
@param  KeyType and Datatype variables
@return  none
@brief  retrieve() function that calls retrieve_Helper()
**/
template <typename DataType, class KeyType>
bool BSTree <DataType, KeyType> :: retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	retrieve_Helper(searchKey, searchDataItem, root);
}

/**
@pre  remove_Helper()
@post  none
@param  KeyType variable
@return  none
@brief  remove() function that calls remove_Helper()
**/
template <typename DataType, class KeyType>
bool BSTree <DataType, KeyType> :: remove(const KeyType& deleteKey)
{
	remove_Helper(deleteKey, root);
}

/**
@pre  writeKeys_Helper()
@post  none
@param  none
@return  none
@brief  writeKeys() function that calls writeKeys_Helper()
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: writeKeys() const
{
	writeKeys_Helper(root);
	cout << endl;
}

/**
@pre  clear_Helper()
@post  none
@param  none
@return  none
@brief  clear() function that calls clear_Helper()
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: clear()
{
	clear_Helper(root);
}

/**
@pre  none
@post  none
@param  none
@return  true is BSTree = NULL, false if not
@brief  isEmpty() function that checks if root is equal to NULL
**/
template <typename DataType, class KeyType>
bool BSTree <DataType, KeyType> :: isEmpty () const
{
	if (root == NULL)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

/**
@pre  getHeight_Helper()
@post  none
@param  none
@return  getHeight_Helper(root, 0)
@brief  getHeight() function that calls getHeight_Helper()
**/
template <typename DataType, class KeyType>
int BSTree <DataType, KeyType> :: getHeight() const
{
	return getHeight_Helper(root, 0);
}

/**
@pre  getCount_Helper()
@post  none
@param  none
@return  getCount_Helper(root)
@brief  getCount() function that calls getCount_Helper()
**/
template <typename DataType, class KeyType>
int BSTree <DataType, KeyType> :: getCount() const
{
	return getCount_Helper(root);
}

//////////////////////////////////////////////////////////////////////////
//function helper declarations
//////////////////////////////////////////////////////////////////////////

/**
@pre  none
@post  sets the current BSTree equal to another
@param  (2) BSTreeNodes
@return  none
@brief  Copy constructor helper that sets current BSTree equal to another
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: copyConstructor_Helper(BSTreeNode *&end, BSTreeNode *start)
{	
	if (start == NULL)
	{
		return;
	}
	
	else
	{
		BSTreeNode *left = NULL;
		BSTreeNode *right = NULL;
		
		copyConstructor_Helper(left, start->left);
		copyConstructor_Helper(right, start->right);
		
		end = new BSTreeNode(start->dataItem, left, right);
	}
}

/**
@pre  none
@post  Inserts a new node containing newDataItem
@param  DataType variable and a BSTreeNode
@return  none
@brief  Inserts a new node containing newDataItem. If it exists, then it updates the data item with newDataItem
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: insert_Helper(const DataType& newDataItem, BSTreeNode* &ptr)
{
	if (ptr == NULL)
	{
		ptr = new BSTreeNode(newDataItem, NULL, NULL);
	}
	
	else
	{
		if ((ptr->dataItem).getKey() == newDataItem.getKey())
		{
			ptr->dataItem = newDataItem;
		}
		
		if ((ptr->dataItem).getKey() > newDataItem.getKey())
		{
			insert_Helper(newDataItem, ptr->left);
		}
		
		if ((ptr->dataItem).getKey() < newDataItem.getKey())
		{
			insert_Helper(newDataItem, ptr->right);
		}
	}
}

/**
@pre  none
@post  Searches BSTree using searchKey
@param  KeyType, DataType variables & BSTreeNode
@return  false if ptr is equal to NULL, true if searchDataItem is equal to data item, else recursively searches itself
@brief  Searches BSTree for data item with the same key as searchKey; if found, replaces data item with searchDataItem and returns true
**/
template <typename DataType, class KeyType>
bool BSTree <DataType, KeyType> :: retrieve_Helper(const KeyType& searchKey, DataType& searchDataItem, BSTreeNode* ptr) const
{
	if (ptr == NULL)
	{
		return false;
	}
	
	else
	{
		if (searchKey == (ptr->dataItem).getKey())
		{
			searchDataItem = ptr->dataItem;
			return true;
		}
		
		if (searchKey < (ptr->dataItem).getKey())
		{
			return retrieve_Helper(searchKey, searchDataItem, ptr->left);
		}
		
		if (searchKey > (ptr->dataItem).getKey())
		{
			return retrieve_Helper(searchKey, searchDataItem, ptr->right);
		}
	}
}

/**
@pre  none
@post  Deletes the data item from BSTree
@param  KeyType variable and BSTreeNode
@return  false if ptr is equal to NULL, true if it completes any of the 4 cases below, else it recursively searches itself
@brief  Delete data item with key deleteKey from the BSTree. If data is found, returns true. Else, it returns false.
**/
template <typename DataType, class KeyType>
bool BSTree <DataType, KeyType> :: remove_Helper(const KeyType& deleteKey, BSTreeNode* &ptr)
{
	if (ptr == NULL)
	{
		return false;
	}
	
	if ((ptr->dataItem).getKey() < deleteKey)
	{
		return remove_Helper(deleteKey, ptr->right);
	}
	
	if ((ptr->dataItem).getKey() > deleteKey)
	{
		return remove_Helper(deleteKey, ptr->left);
	}
	
	//case #1, no children
	if ((ptr->left == NULL) && (ptr->right == NULL))
	{
		delete ptr;
		ptr = NULL;
		return true;
	}
	
	//case #2a, one child on the left
	if ((ptr->left != NULL) && (ptr->right == NULL))
	{
		BSTreeNode* temp = ptr;
		ptr = ptr->left;
		delete temp;
		return true;
	}
	
	//case #2b, one child on the right
	if ((ptr->left == NULL) && (ptr->right != NULL))
	{
		BSTreeNode* temp = ptr;
		ptr = ptr->right;
		delete temp;
		return true;
	}
	
	//case #3, two children
	if ((ptr->left != NULL) && (ptr->right != NULL))
	{
		BSTreeNode* temp = ptr->left;
		
		while (temp->right != NULL)
		{
			temp = temp->right;
		}
		
		ptr->dataItem = temp->dataItem;
		remove_Helper((temp->dataItem).getKey(), ptr->left);
		return true;
	}
}

/**
@pre  none
@post  Outputs keys of data items in BSTree
@param  BSTreeNode
@return  none
@brief  Outputs the keys of the data items in the BSTree. They are output in ascending order.
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: writeKeys_Helper(BSTreeNode* ptr) const
{
	if (ptr != NULL)
	{
		//using in-order traversal to print out the binary tree
		writeKeys_Helper(ptr->left);
		cout << (ptr->dataItem).getKey() << " ";
		writeKeys_Helper(ptr->right);
	}
}

/**
@pre  none
@post  Removes all data from BSTree
@param  BSTreeNode
@return  none
@brief  Removes all data from BSTree
**/
template <typename DataType, class KeyType>
void BSTree <DataType, KeyType> :: clear_Helper(BSTreeNode *&ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	
	else
	{
		clear_Helper(ptr->left);
		clear_Helper(ptr->right);
		
		delete ptr;
		ptr = NULL;	
	}
}

/**
@pre  none
@post  Returns the count of the number of data items in BSTree
@param  BSTreeNode and Int
@return  maxHeight
@brief  Counts the number of data items in the BSTree and returns its value
**/
template <typename DataType, class KeyType>
int BSTree <DataType, KeyType> :: getHeight_Helper(BSTreeNode *ptr, int currentHeight) const
{
	//int needs to be static so that its lifetime is the entire run of the program, otherwise it will reset
	static int maxHeight;
	
	if (ptr == NULL)
	{
		if (currentHeight > maxHeight)
		{
			maxHeight = currentHeight;
		}
	}
	
	else
	{
		getHeight_Helper(ptr->left, currentHeight + 1);
		getHeight_Helper(ptr->right, currentHeight + 1);
	}
	
	return maxHeight;
}

/**
@pre  none
@post  Returns the height of the BSTree
@param  BSTreeNode
@return  it will return 0 if empty, otherwise it will recursively traverse itself and add the total plus 1
@brief  Counts the height of the BSTree while recursively traversing itself
**/
template <typename DataType, class KeyType>
int BSTree <DataType, KeyType> :: getCount_Helper(BSTreeNode *ptr) const
{
	if (ptr == NULL)
	{
		return 0;
	}
	
	else
	{
		return getCount_Helper(ptr->left) + getCount_Helper(ptr->right) + 1;
	}
}

//////////////////////////////////////////////////////////////////////////
//showStructure function and helper (provided for this lab)
//////////////////////////////////////////////////////////////////////////

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}
