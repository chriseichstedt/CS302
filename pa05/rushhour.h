/**
@file  rushhour.h
@author  Christopher Eichstedt
@brief  A simulation of the puzzle game, Rush hour.
**/
#include <iostream>

using namespace std;

struct vehicles
{
	int size;
	int row;
	int column;
	char orientation;	
};

class rushhour
{
	public:
		rushhour();
		int buildBoard();
		bool didWeWin();
		bool moveForward(int);
		bool moveBackward(int);
		void solveIt(int);
		void printResults(int);
		void printBoard();
		
		
	private:
		vehicles lot[10];
		int board[6][6];
		bool isSolved;
		int numOfCars;
		int numOfMoves;
		int cap;
		
};
