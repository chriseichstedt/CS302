/** @file RushHour.cpp
@authors Liliana Pacheco, Chantelle Marquez Suarez, Chris Eichstedt
@version Revision 1.1
@brief This program will simulate a rush hour game board and solve the board.
@details This program takes in input from the keyboard to make a rush hour game board and place a maximum of eighteen cars. this program then has the potential to solve said 6x6 board if there exist a solution with a maximum of ten move. futher more if you can manually manipulate the board and move individual cars if desired. 
@date Tuesday December 7, 2017
*/

/**
@mainpage
This program will simulate a rush hour game board and solve the board.
@details This program takes in input from the keyboard to make a rush hour game board and place a maximum of eighteen cars. this program then has the potential to solve said 6x6 board if there exist a solution with a maximum of ten move. futher more if you can manually manipulate the board and move individual cars if desired. 
the program includes the Board class with the following functions:
*/

/*
Author self-assessment statement:
This program is complete and working according to spcecifications,
according to the best of my knowledge.
*/

//
// Header Files ///////////////////////////////////////////////////
//
#include "RushHour.h"
#include <iostream>

using namespace std;

//Board public methods

//
// Supporting Function Implementations //////////////////////////////
//
/**
 * @brief This function will initialize a board class variable by setting all the grid values to zero, 
 * this is the default constructor of the class
 * 
 * @param none 
 * @return none
 * 
 * @pre none 
 * @post creates a board item  
 * 
 */
Board::Board()
{
	 for(int i = 0; i<MAX_GRID_SIZE; i++)
    {
        for(int j = 0; j<MAX_GRID_SIZE; j++)
        {
            boardGrid[i][j] = 0;
        }
    }

    numberOfCars = 0;
}

/**
 * @brief This function will set up the board values from keyboard inputs it also makes sure to clear the variables 
 *	of the board class to start with a clean board before it sets any values. Furthermore it will return a int
 * value if it is zero then there is no more inputs to be taken in other wise it is some other number of cars
 * 
 * @param noe
 * @return int value that functions as a bool to demonstrate that there is no more values to be read into the board
 * 
 * @pre the input values to the board must be as specified and cars must not be out of bound or overlapping 
 * @post allocates all inputed data in the proper place so that the board can be solved
 * 
 */
int Board::setupBoard()
{
	//start setup by clearing everything on the array to zero
	 for(int i = 0; i<MAX_GRID_SIZE; i++)
    {
        for(int j = 0; j<MAX_GRID_SIZE; j++)
        {
            boardGrid[i][j] = 0;
        }
    }	

    numberOfCars = 0;

	 int r, c;
    cin>>numberOfCars;
		
	 if(numberOfCars == 0)//check for end of input values
	 	return 0;

    for(int i = 0; i<numberOfCars; i++)
    {
        cin>>carsNtrucks[i].sizeType;
        cin>>carsNtrucks[i].orientation;
        cin>>carsNtrucks[i].row;
        cin>>carsNtrucks[i].col;
    }

    for(int i = 0; i<numberOfCars; i++) 
    {
		  r = carsNtrucks[i].row; 
		  c = carsNtrucks[i].col;

        boardGrid[r][c] = (i + 1);

        if( carsNtrucks[i].orientation == 'H' )
            boardGrid[r][ c + 1 ] = (i + 1);
        else if( carsNtrucks[i].orientation == 'V' )
            boardGrid[ r + 1 ] [c] = (i + 1);

        if( carsNtrucks[i].sizeType == 3 && carsNtrucks[i].orientation == 'H' )
            boardGrid[r][ c + 2 ] = (i + 1);
        else if ( carsNtrucks[i].sizeType == 3 && ( carsNtrucks[i].orientation == 'V' ) )
            boardGrid[ r + 2] [c] = (i + 1); 
    }
  
	return numberOfCars;
}

/**
 * @brief This Function prints the board's two dimensianol array values this function is mainly for debugging purposes
 * 
 * @param none 
 * @return none
 * 
 * @pre none 
 * @post prints message two dimensional array
 * 
 */
void Board::printBoard()const
{
    for(int i = 0; i<MAX_GRID_SIZE; i++)
    {
        for(int j = 0; j<MAX_GRID_SIZE; j++)
        {
            cout<<boardGrid[i][j]<<" ";
        }
        cout<<endl;
    }
	cout<<endl;
}

/**
 * @brief This function checks if the specified vehicle can be moved forward within the board's two dimensional array
 *	
 * 
 * @param int value that specifies which scenerio is being printed 
 * @return none
 * 
 * @pre none 
 * @post prints message to terminal 
 * 
 */
bool Board::moveForward(int carNum)const //forward refers to moving the car to the right or to the bottom
{
	int r = carsNtrucks[carNum].row;  
	int c = carsNtrucks[carNum].col;
	char o = carsNtrucks[carNum].orientation;
	int s = carsNtrucks[carNum].sizeType;
		
	if(s >3 || s<2)
  {
		cout<<"size is invalid s: "<<s<<endl;
    return false; 
  }

	if(s == 3) //this is in case the vehicle is a truck
	{
		if( c == 3 && o == 'H') //is the truck already as far right as it can be?
			return false;
		else if ( r == 3 && o == 'V') //is the truck already as far down as it can be?
			return false;
		else if ( o == 'H' && boardGrid[r][c + 3] != 0)// is the desired area open or is there an existing object already there? in horizontal case
			return false;
		else if ( o == 'V' && boardGrid[r + 3][c] != 0) // is desired are open in vertical case
			return false;
		else 
			return true;
	}
	else if (s == 2)
	{	
		if( c == 4 && o == 'H')
			return false;
		else if ( r == 4 && o == 'V')
			return false;
		else if ( o == 'H' && boardGrid[r][c + 2] != 0)
			return false;
		else if ( o == 'V' && boardGrid[r + 2][c] != 0)
			return false;
		else 
			return true;
	}
	return false; 
}

/**
 * @brief This function checks if the specified vehicle can be moved forward within the board's two dimensional array
 *	
 * 
 * @param int value that specifies which scenerio is being printed 
 * @return none
 * 
 * @pre none 
 * @post prints message to terminal 
 * 
 */
bool Board::moveBackward(int carNum)const //backward refers to moving the cars to the left or up
{
	int r = carsNtrucks[carNum].row;        
	int c = carsNtrucks[carNum].col;
	char o = carsNtrucks[carNum].orientation;

	if( c == 0 && o == 'H') //is the car already as far left as it can be?
		return false;
	else if ( r == 0 && o == 'V') //is the car as far up as it can be?
		return false;
	else if ( o == 'H' && boardGrid[r][c - 1] != 0)
		return false;
	else if ( o == 'V' && boardGrid[r - 1][c] != 0) 
		return false;
	else 
		return true;
}

/**
 * @brief This function checks if the specified vehicle can be moved forward within the board's two dimensional array
 *	
 * 
 * @param int value that specifies which scenerio is being printed 
 * @return none
 * 
 * @pre none 
 * @post prints message to terminal 
 * 
 */
void Board::moveVehicleF(int carNum)//moving a vehicle forward refers to moving to the right or down depending on orientation
{
	int r = carsNtrucks[carNum].row;        
	int c = carsNtrucks[carNum].col;
	char o = carsNtrucks[carNum].orientation;
	int s = carsNtrucks[carNum].sizeType;

	if(!moveForward(carNum))
	{
		printBoard();
		cout<<"shouldn't move car forward: "<<endl;
		return;		
	}

	boardGrid[r][c] = 0;

	if(s == 3)
	{
		if(o == 'H')
		{
			boardGrid[r][c + 3] = carNum + 1;
			carsNtrucks[carNum].col = c + 1;
		}
		else if ( o == 'V')
		{
			boardGrid[r + 3][c] = carNum + 1;
			carsNtrucks[carNum].row = r + 1;
		}		
	}
	else if ( s == 2)
	{
		if(o == 'H')
		{
			boardGrid[r][c + 2] = carNum + 1;
			carsNtrucks[carNum].col = c + 1;
		}
		else if ( o == 'V')
		{
			boardGrid[r + 2][c] = carNum + 1;
			carsNtrucks[carNum].row = r + 1;
		}	
	}
}

/**
 * @brief This function checks if the specified vehicle can be moved forward within the board's two dimensional array
 *	
 * 
 * @param int value that specifies which scenerio is being printed 
 * @return none
 * 
 * @pre none 
 * @post prints message to terminal 
 * 
 */
void Board::moveVehicleB(int carNum)//moving a vehicle back refers to moving to the left or up depending on orientation
{
	int r = carsNtrucks[carNum].row;        
	int c = carsNtrucks[carNum].col;
	char o = carsNtrucks[carNum].orientation;
	int s = carsNtrucks[carNum].sizeType;

	if(!moveBackward(carNum))
	{
		printBoard();
		cout<<"shouldn't move car in back: "<<endl;
		return;		
	}

	if(s == 3)
	{
		if(o == 'H')
		{
			boardGrid[r][c + 2] = 0;
			boardGrid[r][c - 1] = carNum + 1;
			carsNtrucks[carNum].col = c - 1;
		}
		else if ( o == 'V')
		{
			boardGrid[r + 2][c] = 0;
			boardGrid[r -1][c] = carNum + 1;
			carsNtrucks[carNum].row = r - 1;
		}		
	}
	else 
	{
		if(o == 'H')
		{
			boardGrid[r][c + 1] = 0;
			boardGrid[r][c - 1] = carNum + 1;
			carsNtrucks[carNum].col = c - 1;
		}
		else if ( o == 'V')
		{
			boardGrid[r + 1][c] = 0;
			boardGrid[r - 1][c] = carNum + 1;
			carsNtrucks[carNum].row = r - 1;
		}	
	}
}

/**
 * @brief  function that returns the number of cars
 *	
 * 
 * @param  none
 * @return  int numberOfCars
 * 
 * @pre  none
 * @post  none
 * 
 */
int Board :: getNumCars()const
{
	return numberOfCars;
}

/**
 * @brief  default assignment operator that copies one board into another
 *	
 * 
 * @param  const Board& other
 * @return  *this
 * 
 * @pre  none
 * @post  updates the current board with one assigned to it
 * 
 */
Board& Board::operator=(const Board& other)
{
   for(int i = 0; i<MAX_GRID_SIZE; i++)
   {
       for(int j = 0; j<MAX_GRID_SIZE; j++)
       {
           boardGrid[i][j] = other.boardGrid[i][j];
       }
   }	
  
	numberOfCars = other.numberOfCars;

   for(int i = 0; i < MAX_NUMBER_OF_VEHICLES; i++ )
   {
   	carsNtrucks[i].row = other.carsNtrucks[i].row;
      carsNtrucks[i].col = other.carsNtrucks[i].col;
      carsNtrucks[i].sizeType = other.carsNtrucks[i].sizeType;
      carsNtrucks[i].orientation = other.carsNtrucks[i].orientation;
   }

	return *this;
  /******  note for this operator = does not copy over map or the queue *****/
}
 
/**
 * @brief  bool function that checks the current state of the board, whether it is won or not
 *	
 * 
 * @param   none
 * @return  bool true if win condition is met, bool false if not
 * 
 * @pre  none
 * @post  none
 * 
 */
bool Board :: isWon()const
{
	if( carsNtrucks[0].col  == MAX_GRID_SIZE-2 && carsNtrucks[0].sizeType == 2 ) //incase vehicle 0 is a car
		return true;
	else if (carsNtrucks[0].col == MAX_GRID_SIZE-3 && carsNtrucks[0].sizeType == 3)//incase vehicle 0 is a truck	
		return true;
	else 
		return false;
}

/**
 * @brief returns the keyVal for the current board
 *	
 * 
 * @param  none
 * @return  string keyVal
 * 
 * @pre  none
 * @post  none
 * 
 */
string Board::getKey()const
{
	string keyVal = "0";	

	for(int i = 0; i < MAX_GRID_SIZE; i++)
	{
		for(int k = 0; k < MAX_GRID_SIZE; k++)
		{
			keyVal = keyVal + (char)( boardGrid[i][k] + '0') ;
		}
	}
	return keyVal;
}

/**
 * @brief default constructor for rushBoard
 *	
 * 
 * @param  none
 * @return  none
 * 
 * @pre  none
 * @post  sets bool won to false
 * 
 */
rushBoard :: rushBoard()
{
	won = false;
}

/**
 * @brief function that sets up the default game board
 *	
 * 
 * @param  none
 * @return  gameBoard.setUpBoard()
 * 
 * @pre  setupBoard()
 * @post  sets bool won to false
 * 
 */
int rushBoard :: setupBoard()
{
	won = false;
	return gameBoard.setupBoard();
}

/**
 * @brief Get Key Function
 *	
 * 
 * @param int for the scenerio number
 * @return none
 * 
 * @pre  none
 * @post prints out results of board, if the board has been solved
 * 
 */
void rushBoard :: printResults(int scenarioNum)const
{
	if( won )
		cout<<"Scenario "<<scenarioNum<<" requires "<<bestSolution<<" moves"<<endl;
	else
		cout<<"This board has no solution"<<endl;
}

/**
 * @brief Get Key Function
 *	
 * 
 * @param none
 * @return none
 * 
 * @pre  none
 * @post output to terminal the contents of the board
 * 
 */
void rushBoard :: printBoard()const
{
	gameBoard.printBoard();
}

/**
 * @brief Get Key Function
 *	
 * 
 * @param none
 * @return bool true if board has been solved
 * 
 * @pre  none
 * @post none
 * 
 */
bool rushBoard :: isWon()const
{
	return gameBoard.isWon();
}

/**
 * @brief Get Key Function
 *	
 * 
 * @param none
 * @return none
 * 
 * @pre  board must be set prior to being solved
 * @post solves for the number of moves required to solve a preset board
 * 
 */
void rushBoard :: solve()
{
	int numMoves = 0;

	queue<Board> boardList;
	map<string, int> previousStates;
	
	boardList.push(gameBoard);
	previousStates.insert( pair<string, int>( gameBoard.getKey(), numMoves ) );

	while( boardList.size() > 0 && won == false )
	{
		gameBoard = boardList.front();
		boardList.pop();
		
		numMoves = previousStates.find( gameBoard.getKey() ) -> second;
	
		if( isWon() )
		{
			bestSolution = numMoves;
			won = true;
			return;
		}

		for(int i = 0; i < gameBoard.getNumCars(); i++)
		{
			if( gameBoard.moveForward(i) )
			{
				gameBoard.moveVehicleF(i);
			
				if( previousStates.find( gameBoard.getKey() ) == previousStates.end() )
				{
					boardList.push( gameBoard );
					previousStates.insert( pair<string, int>( gameBoard.getKey(), numMoves + 1));
				}
		
				gameBoard.moveVehicleB(i);
			}

			if( gameBoard.moveBackward(i) )
			{
				gameBoard.moveVehicleB(i);
			
				if( previousStates.find( gameBoard.getKey() ) == previousStates.end() )
				{
					boardList.push( gameBoard );
					previousStates.insert( pair<string, int>( gameBoard.getKey(), numMoves + 1));
				}
		
				gameBoard.moveVehicleF(i);
			}
		}
	}
}

//
// Main Function Implementation ///////////////////////////////////
//
int main()
{
  	 rushBoard game;
  
	 for(int i = 1; game.setupBoard() != 0; i++)
	 {
		 game.solve();
		 game.printResults(i);
	 }
 
return 0;
}