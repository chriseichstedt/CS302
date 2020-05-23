//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cpp
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 38;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------

int main ()
{
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum = 0;                      // Record number
    string temp1, temp2, temp3;		  // Temp strings

    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
	while(!acctFile.eof())
	{
		acctFile >> entry.acctID;
		acctFile >> temp1 >> temp2 >> temp3;
		entry.recNum = recNum;
		recNum++;
		index.insert(entry);
	}

    // Output the account IDs in ascending order.
	cout << endl << "Account IDs :" << endl;
	index.writeKeys();
	cout << endl;

    // Clear the status flags for the database file.
	acctFile.clear();
	acctFile.seekg(0, ios:: beg);

    // Read an account ID from the keyboard and output the
    // corresponding record.
    	cout << "Enter account ID : ";
    	int temp = 0;
	
	while(cin >> searchID)
	{	
		if(index.retrieve(searchID, entry))
		{
			while(temp < entry.recNum)
			{
				acctFile >> acctRec.acctID;
				acctFile >> acctRec.firstName >> acctRec.lastName;
				acctFile >> acctRec.balance;
				temp++;
			}
			
			recNum = entry.recNum;
	
			cout << recNum - 1
			<< " : " << acctRec.acctID
			<< " " << acctRec.firstName
			<< " " << acctRec.lastName
			<< " " << acctRec.balance;
		}
		
		else
		{
			cout << "No record with that account ID";
		}
		
		acctFile.clear();
		acctFile.seekg(0, ios:: beg);
		cout << endl << "Enter account ID (EOF to quit): ";	
	}
	
	return 0;
}
