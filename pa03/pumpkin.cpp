// @file  pumpkin.cpp
// @author  Christopher Eichstedt
// @brief  A user defined garden that then finds & prints out the size/amount of Pumpkin Patches

#include <iostream>

using namespace std;

const int maxRows = 40;
const int maxColumns = 40;

void findPatch(int, int, char [][maxColumns]);
int checkPatch(int, int, int, int, char[][maxColumns]);

// @pre  requires findPatch()
// @post  prints out the amount of patches and size for each user garden
// @param  none
// @return  returns 0 as to end the function
// @brief  the main function that prompts the user for their garden and its size
int main()
{
	int numOfRows = 1;
	int numOfColumns = 1;
	int gardenCount = 0;
	char userInput;
	
	while(numOfColumns > 0 || numOfRows > 0)
	{
		gardenCount++;
		cin >> numOfRows;
		cin >> numOfColumns;
		
		if(numOfRows == 0 || numOfColumns == 0)
		{
			return 0;
			
		}
	
		
		if(numOfRows > 40 || numOfColumns > 40)
		{
			return 0;
		}
	
		char userGarden[maxRows][maxColumns];
	
		for(int i = 0; i < numOfRows; i++)
		{
			for(int j = 0; j < numOfColumns; j++)
			{
				cin >> userInput;
			
				switch(userInput)
				{
					case 'z':
					{
						userGarden[i][j] = userInput;
						break;
					}
				
					case 'p':
					{
						userGarden[i][j] = userInput;
						break;
					}
				
					case 'y':
					{
						userGarden[i][j] = userInput;
						break;
					}
				
					case 's':
					{
						userGarden[i][j] = userInput;
						break;
					}
				
					default:
					{
						userGarden[i][j] = '_';
						break;
					}
				}
			}
		}

		cout << "Garden # " << gardenCount << ": ";
		findPatch(numOfRows, numOfColumns, userGarden);
	}
	return 0;
}

// @pre  requires checkPatch()
// @post  prints out the sorted patches and their sizes
// @param  two integers from garden row and column size, as well as the user defined garden char array
// @return  none
// @brief  traverses the user garden, finds pumpkin patches and their sizes, puts them into a temp array and sorts them to print
void findPatch(int userNum1, int userNum2, char userArray[][maxColumns])
{
	int patches = 0;
	int count[(40*40)/2];
 	int k = 0;

	//search for pumpkins
	for(int i = 0; i < userNum1; i++)
	{
		for(int j = 0; j < userNum2; j++)
		{
			if(userArray[i][j] == 'p' || userArray[i][j] == 'P')
			{
      				patches++;
       				count[k] = checkPatch(userNum1, userNum2, i, j, userArray);
       				k++;
			}
		}
	}
	
	//swap arrays
	int tempCount[patches];
	
	for(int i = 0; i < patches; i++)
	{
		tempCount[i] = count[i];
	}
	
	//bubble sort
	int swapTemp;
	int start = 0;
	int end = patches-1;

	for(int i = 0; i < end; i++)
	{
		for(int j = end; j > start; j--)
		{
			if(tempCount[j] < tempCount[j-1])
			{
				swapTemp = tempCount[j];
				tempCount[j] = tempCount[j-1];
				tempCount[j-1] = swapTemp;
			}
		}
	} 

	//print out sorted array
	cout << patches << " patches, sizes:";
	for(int i = 0 ; i < patches ; i++)
	{
  		cout << " " << tempCount[i];
  	}
	
	cout << endl;
}

// @pre  none
// @post  returns the size of a pumpkin patch
// @param  two integers that act as the user defined row and column size, two integers that denote where to locate found pumpkin, and the user defined garden char array
// @return  returns the total count of pumpkins in a patch
// @brief a function who recursively calls itself until it crosses out all pumpkins in a patch, then returns the total count
int checkPatch(int userNum1, int userNum2, int userNum3, int userNum4, char userArray[][maxColumns])
{
	int count = 0;
	if(userArray[userNum3][userNum4] == 'p' || userArray[userNum3][userNum4] == 'P')
	{
		count++;
		userArray[userNum3][userNum4] = 'x';
	
		if(userNum3 != 0)
		{
			count += checkPatch(userNum1, userNum2, userNum3 - 1, userNum4, userArray);
		}
	
		if(userNum4 != 0)
		{
			count += checkPatch(userNum1, userNum2, userNum3, userNum4 - 1, userArray);
		}
	
		if(userNum3 != userNum1)
		{
			count += checkPatch(userNum1, userNum2, userNum3 + 1, userNum4, userArray);
		}
	
		if(userNum4 != userNum2)
		{
			count += checkPatch(userNum1, userNum2, userNum3, userNum4 + 1, userArray);
		}
	}
	
	return count;
}

