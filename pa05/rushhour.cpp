/**
@file  rushhour.cpp
@author  Christopher Eichstedt
@brief  A simulation of the puzzle game, Rush hour.
**/

#include "rushhour.h"

/**
@pre  none
@post  creates an empty rushhour
@param  none
@return  none
@brief  default constructor for rushhour data type
**/
rushhour :: rushhour()
{
	cap = 10;
	isSolved = false;
	numOfCars = 0;
	numOfMoves = cap + 1;
	
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			board[i][j] = 0;
		}
	}
}

/**
@pre  none
@post  initializes rushhour data type with user defined board
@param  none
@return  none
@brief  a setup function for a user defined rush hour board
**/
int rushhour :: buildBoard()
{
	cap = 10;
	numOfMoves = cap + 1;
	numOfCars = 0;
	isSolved = false;
	
	//setting up board to zero
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			board[i][j] = 0;
		}
	}
		
	//take in number of cars
	cin >> numOfCars;
	
	if(numOfCars == 0)
	{
		return 0;
	}
	
	for(int i = 0; i < numOfCars; i++)
	{
		cin >> lot[i].size;
		cin >> lot[i].orientation;
		cin >> lot[i].row;
		cin >> lot[i].column;
	}
	
	int row, column;
	for(int i = 0; i < numOfCars; i++)
	{
		row = lot[i].row;
		column = lot[i].column;
	
		board[row][column] = (i + 1);
		
		if(lot[i].orientation == 'H')
		{
			if(lot[i].size == 2)
			{
				board[row][column + 1] = (i + 1);
			}
		
			else if(lot[i].size == 3)
			{
				board[row][column + 1] = (i + 1);
				board[row][column + 2] = (i + 1);
			}
		}
		
		if(lot[i].orientation == 'V')
		{
			if(lot[i].size == 2)
			{
				board[row + 1][column] = (i + 1);
			}
				
			else if(lot[i].size == 3)
			{
				board[row + 1][column] = (i + 1);
				board[row + 2][column] = (i + 1);
			}
		}
	}
	
	return numOfCars;
}

/**
@pre  none
@post  returns true or false depending on condition
@param  none
@return  true or false
@brief  a boolean function that checks to see if vehicle zero meets win conditions
**/
bool rushhour :: didWeWin()
{
	//checks to see if its a car
	if(lot[0].column == 4 && lot[0].size == 2)
	{
		return true;
	}
	
	//checks to see if its a truck
	else if(lot[0].column == 3 && lot[0].size == 3)
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
@post  moves passed in vehicle number, one space forward, either vertical or horizontal
@param  int carNumber, used to specify which vehicle to move
@return  true or false
@brief  a boolean function that returns true if the vehicle can move forward, or false if it cannot
**/
bool rushhour :: moveForward(int carNumber)
{
	int row, column;
	row = lot[carNumber].row;
	column = lot[carNumber].column;
	
	//moveForward for a truck
	if(lot[carNumber].size == 3)
	{
		if(lot[carNumber].orientation == 'H')
		{
			//check bounds
			if(lot[carNumber].column == 3)
			{
				return false;
			}
			
			//check for other vehicle
			else if(board[row][column + 3] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column] = 0;
				board[row][column + 3] = carNumber + 1;
				lot[carNumber].column = column + 1;
				return true;
			}
		}
		
		if(lot[carNumber].orientation == 'V')
		{
			//check bounds
			if(lot[carNumber].row == 3)
			{
				return false;
			}
			
			//check for other vehicle
			else if(board[row + 3][column] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column] = 0;
				board[row + 3][column] = carNumber + 1;
				lot[carNumber].row = row + 1;
				return true;
			}
		}
	}
	
	//moveForward for a car
	if(lot[carNumber].size == 2)
	{
		if(lot[carNumber].orientation == 'H')
		{
			//check bounds
			if(lot[carNumber].column == 4)
			{
				return false;
			}
			
			//check for vehicle
			else if(board[row][column + 2] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column] = 0;
				board[row][column + 2] = carNumber + 1;
				lot[carNumber].column = column + 1;
				return true;
			}
		}
		
		if(lot[carNumber].orientation == 'V')
		{
			//check bounds
			if(lot[carNumber].row == 4)
			{
				return false;
			}
			
			//check for vehicle
			else if(board[row + 2][column] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column] = 0;
				board[row + 2][column] = carNumber + 1;
				lot[carNumber].row = row + 1;
				return true;
			}
		}
	}
}

/**
@pre  none
@post  moves passed in vehicle number, one space backward, either vertical or horizontal
@param  int carNumber, used to specify which vehicle to move
@return  true or false
@brief  a boolean function that returns true if the vehicle can move backward, or false if it cannot
**/
bool rushhour :: moveBackward(int carNumber)
{
	int row, column;
	row = lot[carNumber].row;
	column = lot[carNumber].column;
	
	//moveBackward for a truck
	if(lot[carNumber].size == 3)
	{
		if(lot[carNumber].orientation == 'H')
		{
			//check bounds
			if(lot[carNumber].column == 0)
			{
				return false;
			}
			
			//check for other vehicle
			else if(board[row][column - 1] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column + 2] = 0;
				board[row][column - 1] = carNumber + 1;
				lot[carNumber].column = column - 1;
				return true;
			}
		}
		
		if(lot[carNumber].orientation == 'V')
		{
			//check bounds
			if(lot[carNumber].row == 0)
			{
				return false;
			}
			
			//check for other vehicle
			else if(board[row - 1][column] != 0)
			{
				return false;
			}
			
			else
			{
				board[row + 2][column] = 0;
				board[row - 1][column] = carNumber + 1;
				lot[carNumber].row = row - 1;
				return true;
			}
		}
	}
	
	//moveBackward for a car
	if(lot[carNumber].size == 2)
	{
		if(lot[carNumber].orientation == 'H')
		{
			//check bounds
			if(lot[carNumber].column == 0)
			{
				return false;
			}
			
			//check for vehicle
			else if(board[row][column - 1] != 0)
			{
				return false;
			}
			
			else
			{
				board[row][column + 1] = 0;
				board[row][column - 1] = carNumber + 1;
				lot[carNumber].column = column - 1;
				return true;
			}
		}
		
		if(lot[carNumber].orientation == 'V')
		{
			//check bounds
			if(lot[carNumber].row == 0)
			{
				return false;
			}
			
			//check for vehicle
			else if(board[row - 1][column] != 0)
			{
				return false;
			}
			
			else
			{
				board[row + 1][column] = 0;
				board[row - 1][column] = carNumber + 1;
				lot[carNumber].row = row - 1;
				return true;
			}
		}
	}
}

/**
@pre  didWeWin(), moveForward(), moveBackward()
@post  updates the amount of moves necessary to solve the board, as well as the cap after a solution is found
@param  int numVal, used to specify the amount of moves to solve the board
@return  none
@brief  a void function that uses recursion to solve the amount of moves necessary to solve the board
**/
void rushhour :: solveIt(int numVal)
{
	if(didWeWin())
	{
		if(numVal <= cap)
		{
			numOfMoves = numVal;
			cap = numVal;
			isSolved = true;
			return;
		}
	}
	
	if(numVal > cap)
	{
		return;
	}
		
	for(int i = 0; i < numOfCars; i++)
	{
		if(moveForward(i))
		{
			solveIt(numVal + 1);
			moveBackward(i);
		}
			
		if(moveBackward(i))
		{
			solveIt(numVal + 1);
			moveForward(i);
		}
	}
}

/**
@pre  none
@post  none
@param  int numVal, used to print out the amount of moves necessary to complete the board
@return  none
@brief  a void function that prints out the solution if isSolved is true, and an error if it is false
**/
void rushhour :: printResults(int numVal)
{
	if(isSolved)
	{
		cout << "Scenario " << numVal + 1 << " requires " << numOfMoves << " moves" << endl;
	}
	
	else
	{
		cout << "No solution under 10 moves." << endl;
	}
}

/**
@pre  none
@post  none
@param  none
@return  none
@brief  a void function that prints the board; used only for testing
**/
void rushhour :: printBoard()
{
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			cout << board[i][j]; 
		}
		
		cout << endl;
	}	
	cout<<endl;
}

/**
@pre  rushhour(), solveIt(), buildBoard(), printResults()
@post  builds and solves the board for the alloted input, continues until 0 is given for numOfCars
@param  none
@return  returns 0 to end main driver
@brief  the main driver that builds and runs the rushhour game
**/
int main()
{
	rushhour game;
	
	for(int i = 0; game.buildBoard() != 0; i++)
	{
		game.solveIt(0);
		//game.printBoard();
		game.printResults(i);
	}
	return 0;	
}
