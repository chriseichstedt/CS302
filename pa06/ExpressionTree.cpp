/**
@file  ExpressionTree.cpp
@author  Christopher Eichstedt
@brief  An Implementation file for an Expression Tree
**/

#include "ExpressionTree.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
//function declarations
//////////////////////////////////////////////////////////////////////////

/**
@pre  none
@post  creates a node
@param  Char variable and two Node pointers
@return  none
@brief  default node constructor for ExprTree class
**/
template <typename DataType>
ExprTree<DataType> :: ExprTreeNode :: ExprTreeNode(char elem, ExprTreeNode *leftPtr, ExprTreeNode *rightPtr)
{
	dataItem = elem;
	left = leftPtr;
	right = rightPtr;
}

/**
@pre  none
@post  sets root equal to null
@param  none
@return  none
@brief  default constructor for ExprTree class
**/
template <typename DataType>
ExprTree<DataType> :: ExprTree()
{
	root = NULL;
}

/**
@pre  copyConstructor_Helper()
@post  sets current tree equal to parameterized tree
@param  predefined ExprTree
@return  *this, which is the current list whether its identical or needs to be rebuilt
@brief  default copy constructor for ExprTree class
**/
template <typename DataType>
ExprTree<DataType> :: ExprTree(const ExprTree& source)
{
	*this = source;
}

/**
@pre  copyConstructor_Helper()
@post  sets current tree equal to parameterized tree
@param  predefined ExprTree
@return  *this, which is the current list whether its identical or needs to be rebuilt
@brief  overloaded operator for ExprTree class
**/
template <typename DataType>
ExprTree<DataType>& ExprTree<DataType> :: operator=(const ExprTree<DataType>& source)
{
	if(this == &source)
	{
		return *this;
	}
	
	else
	{
		copyConstructor_Helper(root, source.root);
		return *this;
	}
}

/**
@pre  clear()
@post  destroys the current tree
@param  none
@return  none
@brief  default destructor for ExprTree class
**/
template <typename DataType>
ExprTree<DataType> :: ~ExprTree()
{
	clear();
}

/**
@pre  build_Helper()
@post  builds an Expression Tree
@param  none
@return  none
@brief  builds the tree with the use of build_Helper()
**/
template <typename DataType>
void ExprTree<DataType> :: build()
{
	build_Helper(root);
}

/**
@pre  expression_Helper()
@post  none
@param  none
@return  none
@brief  prints out the expressions in the tree with the use of expression_Helper()
**/
template <typename DataType>
void ExprTree<DataType> :: expression() const
{
	expression_Helper(root);
}

/**
@pre  evaluate_Helper()
@post  none
@param  none
@return  evaluate_Helper(), using root as the start location
@brief  prints out the total value of the equation stored in the tree with the use of evaluate_Helper()
**/
template <typename DataType>
DataType ExprTree<DataType> :: evaluate() const throw(logic_error)
{
	if(root == NULL)
	{
		throw logic_error("evaluate() empty tree");
	}
	
	else
	{
		return evaluate_Helper(root);
	}
}

/**
@pre  clear_Helper()
@post  destroys the current tree
@param  none
@return  none
@brief  deletes the entirety of the tree with the use of clear_Helper()
**/
template <typename DataType>
void ExprTree<DataType> :: clear()
{
	clear_Helper(root);
}

template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if (root == NULL)
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}
//////////////////////////////////////////////////////////////////////////
//function helper declarations
//////////////////////////////////////////////////////////////////////////
/**
@pre  none
@post  builds an Expression Tree from another one
@param  Two Nodes that point to where the copy is starting from and where it will end up
@return  none
@brief  recursively calls itself to build an Expression Tree
**/
template <typename DataType>
void ExprTree<DataType> :: copyConstructor_Helper(ExprTreeNode *&end, ExprTreeNode *start)
{	
	if(start == NULL)
	{
		return;
	}
	
	else
	{
		ExprTreeNode *left = NULL;
		ExprTreeNode *right = NULL;
		
		copyConstructor_Helper(left, start->left);
		copyConstructor_Helper(right, start->right);
		
		end = new ExprTreeNode(start->dataItem, left, right);
	}
}

/**
@pre  none
@post  builds an Expression Tree
@param  Node that points to where to build an Expression Tree
@return  none
@brief  builds an Expression Tree
**/
template <typename DataType>
void ExprTree<DataType> :: build_Helper(ExprTreeNode *&tempNode)
{	
	char tempVal;
	cin >> tempVal;
	tempNode = new ExprTreeNode(tempVal, NULL, NULL);
	
	switch(tempVal)
	{
		case '+':
		{
			build_Helper(tempNode->left);
			build_Helper(tempNode->right);
			break;
		}
		
		case '-':
		{
			build_Helper(tempNode->left);
			build_Helper(tempNode->right);
			break;
		}
		
		case '*':
		{
			build_Helper(tempNode->left);
			build_Helper(tempNode->right);
			break;
		}
		
		case '/':
		{
			build_Helper(tempNode->left);
			build_Helper(tempNode->right);
			break;
		}
		
		default:
		{
		}
	}
}

/**
@pre  none
@post  none
@param  Node used to traverse Expression Tree
@return  none
@brief  prints out the expressions using parenthesis 
**/
template <typename DataType>
void ExprTree<DataType> :: expression_Helper(ExprTreeNode *ptr) const
{
	char tempChar = ptr->dataItem;
	int tempInt = tempChar - '0';
	
	if(tempInt >= 0 && tempInt <= 9)
	{
		cout << tempInt;
		return;
	}
	
	else
	{
		cout << "(";
		expression_Helper(ptr->left);
		cout << ptr->dataItem;
		expression_Helper(ptr->right);
		cout << ")";
	}
}

/**
@pre  none
@post  none
@param  Node used to traverse Expression Tree
@return  returns the value of the left and right nodes, based upon their arithmetic operator
@brief  performs the expression and returns its value
**/
template <typename DataType>
DataType ExprTree<DataType> :: evaluate_Helper(ExprTreeNode *ptr) const
{
	switch(ptr->dataItem)
	{
		case '+':
		{
			return (evaluate_Helper(ptr->left) + evaluate_Helper(ptr->right));
			break;
		}
		
		case '-':
		{
			return (evaluate_Helper(ptr->left) - evaluate_Helper(ptr->right));
			break;
		}
		
		case '*':
		{
			return (evaluate_Helper(ptr->left) * evaluate_Helper(ptr->right));
			break;
		}
		
		case '/':
		{
			return (evaluate_Helper(ptr->left) / evaluate_Helper(ptr->right));
			break;
		}
		
		default:
			char tempChar = ptr->dataItem;
			int tempInt = tempChar - '0';
			return tempInt;
			break;
	}
}

/**
@pre  none
@post  destroys the current tree
@param  Node used to traverse Expression Tree
@return  none
@brief  deletes the entirety of the Expression Tree
**/
template <typename DataType>
void ExprTree<DataType> :: clear_Helper(ExprTreeNode *&ptr)
{
	if(ptr == NULL)
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

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}
//////////////////////////////////////////////////////////////////////////
//programming exercise #2
//////////////////////////////////////////////////////////////////////////
/**
@pre  commmute_Helper()
@post  applies the commutative property to the current expressions stored in the tree
@param  none
@return  none
@brief  applies the commutative property with the use of the commute_Helper()
**/
template <typename DataType>
void ExprTree<DataType> :: commute()
{
	commute_Helper(root);
}

/**
@pre  none
@post  applies the commutative property to the current expressions stored in the tree
@param  Node used to traverse Expression Tree
@return  none
@brief  applies the commutative property by swapping the left and right nodes of expressions
**/
template <typename DataType> 
void ExprTree<DataType> :: commute_Helper(ExprTreeNode *&ptr)
{
	if(ptr == NULL)
	{
		return;
	}
	
	switch(ptr->dataItem)
	{
		case '+':
		{
			ExprTreeNode *temp;
			temp = ptr->left;
			ptr->left = ptr->right;
			ptr->right = temp;
			break;
		}
		
		case '-':
		{
			ExprTreeNode *temp;
			temp = ptr->left;
			ptr->left = ptr->right;
			ptr->right = temp;
			break;
		}
		
		case '*':
		{
			ExprTreeNode *temp;
			temp = ptr->left;
			ptr->left = ptr->right;
			ptr->right = temp;
			break;
		}
		
		case '/':
		{
			ExprTreeNode *temp;
			temp = ptr->left;
			ptr->left = ptr->right;
			ptr->right = temp;
			break;
		}
		
		default:
		{
			break;
		}
	}
	
	commute_Helper(ptr->left);
	commute_Helper(ptr->right);
}

//////////////////////////////////////////////////////////////////////////
//programming exercise #3 (extra credit)
//////////////////////////////////////////////////////////////////////////
template <typename DataType>
bool ExprTree<DataType> :: isEquivalent(const ExprTree& source) const
{
}
