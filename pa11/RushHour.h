#ifndef RushHour_h
#define RushHour_h

#define MAX_GRID_SIZE 6
#define MAX_NUMBER_OF_VEHICLES 18

//
// Header Files ///////////////////////////////////////////////////
//
#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

//
// Struct /////////////////////////////////////////////////////////
//
struct Vehicle
{
    int row;	        /**< This is the row number of the vehicle (for ID) */
    int col;           /**< This is the column number of the vehicle (for ID) */
    int sizeType;      /**< Determines whether vehicle is a car or truck */
    char orientation;  /**< Determines whether vehicle is horizontal or vertical */
};

class Board
{
    public:
        Board();
  		  Board& operator=(const Board& other);
        
		  int setupBoard();
        void printBoard()const;
		  bool isWon()const;
		  int getNumCars()const;

        bool moveForward(int carNum)const;
        bool moveBackward(int carNum)const;
        void moveVehicleF(int carNum);
        void moveVehicleB(int carNum);

        string getKey()const;

    private:
        int boardGrid[MAX_GRID_SIZE][MAX_GRID_SIZE]; //physical representation of where behicles are placed
        Vehicle carsNtrucks[MAX_NUMBER_OF_VEHICLES]; //structure array of all the existing vehicle data
  
        int numberOfCars; //holds the number of cars in a particular board
};
	
class rushBoard
{
	public: 
		rushBoard();
		
		int setupBoard();
		void printResults(int scenarioNum)const;
		void printBoard()const;

		bool isWon()const;
		void solve();

	private:
		Board gameBoard;
		int  bestSolution;
		bool won;
};	

#endif // Board



