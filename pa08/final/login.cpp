/**
@file login.cpp
@author Christopher Eichstedt
@brief Programming Exercise #1 for a Hash Table
**/

#include <iostream>
#include <fstream>
#include "HashTable.cpp"

/////////////////////////////////////////////////////////////////////
//class header for user information
/////////////////////////////////////////////////////////////////////
class userLogin
{
	public:
	
		void setKey(const string& userName);
		void setPassword(const string& userPassword);
		string getKey() const;
		string getPassword() const;
		static unsigned int hash(const string& other);
		
	private:
		string key;
		string password;
};

/////////////////////////////////////////////////////////////////////
//class implementation for user information
/////////////////////////////////////////////////////////////////////
/**
@pre  none
@post  sets key equal to userName
@param  string variable
@return  none
@brief  assigns userName to key
**/
 void userLogin :: setKey (const string& userName)
 {
 	key = userName;
 }
 
 /**
@pre  none
@post  sets password equal to userPassword
@param  string variable
@return  none
@brief  assigns userPassword to password
**/
void userLogin :: setPassword (const string& userPassword)
{
	password = userPassword;
}

/**
@pre  none
@post  none
@param  none
@return  returns key
@brief  a function that returns the string value stored in key
**/
string userLogin :: getKey() const
{
	return key;
}

/**
@pre  none
@post  none
@param  none
@return  returns password
@brief  a function that returns the string value stored in password
**/
string userLogin :: getPassword() const
{
	return password;
}

/**
@pre  none
@post  none
@param  string variable
@return  returns the int value stored in temp
@brief  builds a hash value for the string
**/
unsigned int userLogin :: hash (const string& other)
{
	unsigned int temp = 0;
	
	for(int i = 0; i < other.length(); i++)
	{
		temp += other[i];
	}
	
	return temp;
}

/////////////////////////////////////////////////////////////////////
//main driver for Login.cpp
/////////////////////////////////////////////////////////////////////
int main()
{
	string userName;
	string userPassword;
	
	ifstream loginInfo("password.dat");
	HashTable<userLogin, string> userTable(8);
	userLogin temp;
	
	loginInfo >> userName;
	
	while(!loginInfo.eof())
	{
		loginInfo >> userPassword;
		
		temp.setKey(userName);
		temp.setPassword(userPassword);
		userTable.insert(temp);
		
		loginInfo >> userName;
	}
	
	userTable.showStructure();
	
	cout << "Login: ";
	
	while(cin >> userName)
	{
		cout << "Password: ";
		cin >> userPassword;
		
		if(userTable.retrieve(userName, temp))
		{
			if(temp.getPassword() == userPassword)
			{
				cout << "Authentication successful" << endl;
			}
			
			else
			{
				cout << "Authentication failure" << endl;
			}
		}
		
		else
		{
			cout << "Authentication failure" << endl;
		}
		
		cout << "Login: ";
	}
	
	return 0;
}
