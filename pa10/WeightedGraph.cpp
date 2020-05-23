/**
@file  WeightedGraph.cpp
@author  Christopher Eichstedt
@brief  An implementation of a Weighted Graph ADT
**/

#include "WeightedGraph.h"
#include "show12.cpp"

using namespace std;

/**
@param  int maxNumber
@return  none
@brief  "Constructor. Creates an empty graph. Allocates enough memory for a graph containing maxNumber vertices."
**/
WeightedGraph :: WeightedGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxNumber];
	adjMatrix = new int[maxNumber * maxNumber];
	pathMatrix = new int[maxNumber * maxNumber];
	
	for(int i = 0; i < maxSize; i++)
	{
		for(int j = 0; j < maxSize; j++)
		{
			setEdge(i, j, INFINITE_EDGE_WT);
		}
	}
}

/**
@param  const WeightedGraph& other
@return  none
@brief  "Copy Constructor. Initializes the weighted graph to be equivalent to the other weighted graph parameter."
**/
WeightedGraph :: WeightedGraph(const WeightedGraph& other)
{
	*this = other;
}

/**
@param  const WeightedGraph& other
@return  *this
@brief  "Overloaded assignment operator. Sets the weighted graph to be equivalent to the other weighted graph parameter and returns a reference to this other."
**/
WeightedGraph& WeightedGraph :: operator=(const WeightedGraph& other)
{
	if(this == &other)
	{
		return *this;
	}
	
	else
	{
		delete[] vertexList;
		delete[] adjMatrix;
		delete[] pathMatrix;
		
		size = other.size;
		maxSize = size;
		vertexList = new Vertex[maxSize];
		adjMatrix = new int[maxSize * maxSize];
		pathMatrix = new int[maxSize * maxSize];
		
		for(int i = 0; i < maxSize; i++)
		{
			vertexList[i] = other.vertexList[i];
			
			for(int j = 0; j < maxSize; j++)
			{
				adjMatrix[(i * maxSize) + j] = other.adjMatrix[(i * maxSize) + j];
				pathMatrix[(i * maxSize) + j] = other.pathMatrix[(i * maxSize) + j];
			}
		}
		
		return *this;
	}
}

/**
@param  none
@return  none
@brief  "Destructor. Deallocates (frees) the memory used to store a graph."
**/
WeightedGraph :: ~WeightedGraph()
{
	delete[] vertexList;
	delete[] adjMatrix;
	delete[] pathMatrix;
}

/**
@param  newVertex
@return  none
@brief  "Inserts newVertex into a graph. If the vertex already exists in the graph, then updates it."
**/
void WeightedGraph ::insertVertex(const Vertex& newVertex) throw(logic_error)
{
	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == newVertex.getLabel())
		{
			vertexList[i] = newVertex;
			
			for(int j = 0; j < size; j++)
			{
				setEdge(i, j, INFINITE_EDGE_WT);
			}
			
			return;
		}
	}
	
	if(isFull())
	{
		throw logic_error("The Graph is full");
	}
	
	vertexList[size] = newVertex;
	
	for(int i = 0; i < size; i++)
	{
		setEdge(size, i, INFINITE_EDGE_WT);
	}
	
	size = size + 1;
}

/**
@param  const string& v1, const string& v2, int wt
@return  none
@brief  "Inserts an undirected edge connecting vertices v1 and v2 into the graph. The weight of the edge is WT. If there is already an edge connecting these vertices, then updates the weight of the edge."
**/
void WeightedGraph :: insertEdge(const string& v1, const string& v2, int wt) throw(logic_error)
{
	int temp1 = getIndex(v1);
	int temp2 = getIndex(v2);
	
	if(temp1 == -1 || temp2 == -1)
	{
		throw logic_error("Vertex not found");
	}
	
	setEdge(temp1, temp2, wt);
}

/**
@param  const string& v, Vertex& vData
@return  true if found and false if not
@brief  "Searches a graph for vertex v. If this vertex is found, then places the value of the vertex's data in vData and returns true. Otherwise, returns false with vData undefined."
**/
bool WeightedGraph :: retrieveVertex(const string& v, Vertex& vData) const
{
	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == v)
		{
			vData = vertexList[i];
			return true;
		}
	}
	
	return false;
}

/**
@param  const string& v1, const string& v2, int& wt
@return
@brief  "Searches the graph for the edge connecting vertices v1 and v2. If this edge exists, then places the weight of the edge in wt and returns true. Otherwise, returns false with wt undefined."
**/
bool WeightedGraph :: getEdgeWeight(const string& v1, const string& v2, int& wt) const throw(logic_error)\
{
	int temp1 = getIndex(v1);
	int temp2 = getIndex(v2);
	
	if(temp1 == -1 || temp2 == -1)
	{
		throw logic_error("Edge not found");
	}
	
	if(getEdge(temp1, temp2) != INFINITE_EDGE_WT)
	{
		wt = getEdge(temp1, temp2);
		return true;
	}
	
	return false;
}

/**
@param  const string& v
@return  none
@brief  "Removes vertex v from the graph and any edges connected to v."
**/
void WeightedGraph :: removeVertex(const string& v) throw(logic_error)
{
	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == v)
		{
			for(int j = i; j < size; j++)
			{
				for(int k = 0; k < size; k++)
				{
					adjMatrix[k * maxSize + j] = adjMatrix[k * maxSize + (j + 1)]; 
				}
			}
			
			for(int j = 0; j < size; j++)
			{
				for(int k = i; k < size; k++)
				{
					adjMatrix[k * maxSize + j] = adjMatrix[(k + 1) * maxSize + j];
				}
			}
			
			for(int j = i; j < size; j++)
			{
				vertexList[j] = vertexList[j + 1];
			}
			
			size = size - 1;
			return;
		}
	}
	
	throw logic_error("Vertex not found");
}

/**
@param  const string& v1, const string& v2
@return  none
@brief  "Removes the edge connecting vertices v1 and v2 from the graph."
**/
void WeightedGraph :: removeEdge(const string& v1, const string& v2) throw(logic_error)
{
	int temp1 = getIndex(v1);
	int temp2 = getIndex(v2);
	
	if(temp1 != -1 && temp2 != -1)
	{
		setEdge(temp1, temp2, INFINITE_EDGE_WT);
	}
	
	else
	{
		throw logic_error("Edge not found");
	}
}

/**
@param  none
@return  none
@brief  "Removes all the vertices and edges in the graph."
**/
void WeightedGraph :: clear()
{
	size = 0;
	delete[] vertexList;
	delete[] adjMatrix;
	delete[] pathMatrix;
	vertexList = new Vertex[maxSize];
	adjMatrix = new int[maxSize * maxSize];
	pathMatrix = new int[maxSize * maxSize];
}

/**
@param  none
@return  true if empty, false if not
@brief  "Returns true if the graph is empty (no vertices). Otherwise, returns false."
**/
bool WeightedGraph :: isEmpty()  const
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
@return  true if full, false if not
@brief  "Returns true if the graph is full (cannot add any more vertices). Otherwise, returns false."
**/
bool WeightedGraph :: isFull()  const
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
@param  const string& v
@return  i if found, -1 if not
@brief  checks WeightedGraph for index, returns result
**/
int WeightedGraph :: getIndex(const string& v) const
{
	for(int i = 0; i < size; i++)
	{
		if(vertexList[i].getLabel() == v)
		{
			return i;
		}
	}
	
	return -1;
}

/**
@param  int row, int col
@return  temp
@brief  Gives the edge weight for the adjMatrix
**/
int WeightedGraph :: getEdge(int row, int col) const
{
	int temp = row * maxSize;
	temp = temp + col;
	return adjMatrix[temp];
}

/**
@param  int row, int col
@return  temp
@brief  Gives the path weight for the pathMatrix
**/
int WeightedGraph :: getPath(int row, int col) const
{
	int temp = row * maxSize;
	temp = temp + col;
	return pathMatrix[temp];
}

/**
@param  int row, int col, int wt
@return  none
@brief  Determines the edge weight for the adjMatrix
**/
void WeightedGraph :: setEdge(int row, int col, int wt)
{
	int temp1 = row * maxSize;
	int temp2 = col * maxSize;
	temp1 = temp1 + col;
	temp2 = temp2 + row;
	
	adjMatrix[temp1] = wt;
	adjMatrix[temp2] = wt;
}

/**
@param  int row, int col, int wt
@return  none
@brief  Determines the edge weight for the pathMatrix
**/
void WeightedGraph :: setPath(int row, int col, int wt)
{
	int temp1 = row * maxSize;
	int temp2 = col * maxSize;
	temp1 = temp1 + col;
	temp2 = temp2 + row;
	
	pathMatrix[temp1] = wt;
	pathMatrix[temp2] = wt;
}
/////////////////////////////////////////////////////////////////////
//programming exercise #1
/////////////////////////////////////////////////////////////////////
/**
@param  none
@return  none
@brief  "Computes and displays the graph's path matrix."
**/
void WeightedGraph :: showShortestPaths()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			setPath(i, j, getEdge(i, j));
		}
		
		setPath(i, i, 0);
	}
	
	for(int i  = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			for(int k = 0; k < size; k++)
			{
				if(getPath(i, j) != INFINITE_EDGE_WT && getPath(i, k) != INFINITE_EDGE_WT)
				{
					if(getPath(i, j) + getPath(i, k) < getPath(j, k) || getPath(j, k) == INFINITE_EDGE_WT)
					{
						setPath(j, k, (getPath(j, i) + getPath(i, k)));
					}
				}
			}
		}
	}
	
	cout << endl << "Path matrix : " << endl << '\t';
	
	for(int i = 0; i < size; i++)
	{
		cout << i << '\t';
	}
	
	cout << endl;
	
	for(int i = 0; i < size; i++)
	{
		cout << i << '\t';
		
		for(int j = 0; j < size; j++)
		{
			int temp = getPath(i, j);
			
			if(temp == INFINITE_EDGE_WT)
			{
				cout << "- \t";
			}
			
			else
			{
				cout << temp << '\t';
			}
		}
		
		cout << endl;
	}
}

/////////////////////////////////////////////////////////////////////
//programming exercise #2
/////////////////////////////////////////////////////////////////////
/**
@param  none
@return  true or false
@brief  "Returns true if no vertex in the graph has the same color as an adjacent vertex. Otherwise, returns false."
**/
bool WeightedGraph :: hasProperColoring() const
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(getEdge(i, j) != INFINITE_EDGE_WT && vertexList[i].getColor() == vertexList[j].getColor() && i != j)
			{
				return false;				
			}
		}
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////
//prgramming exercise #3
/////////////////////////////////////////////////////////////////////
/**
@param  none
@return  true or false
@brief  "Returns true if every vertex in a graph is of even degree. Otherwise, returns false."
**/
bool WeightedGraph :: areAllEven() const
{
	int count = 0;
	
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(getEdge(i, j) != INFINITE_EDGE_WT)
			{
				count++;
			}
		}
		
		if(count % 2)
		{
			return false;
		}
		
		count = 0;
	}
	
	return true;
}
