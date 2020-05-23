/**
@file  Timer.cpp
@author  Christopher Eichstedt
@brief  this is an implementation file for a timer using timeofday()
*/

#include "Timer.h"

using namespace std;

/**
@pre  none
@post  sets the timer flag to false
@return  none
@param  none
@brief  this functions sets the timer flag to false at initialization
*/
Timer :: Timer()
{
	timerWasStarted = false;
}

/**
@pre  none
@post  changes the timer flag to true and records the begin time
@return  none
@param  none
@brief  this function checks to see if the timer flag is true, else it sets it to true and then records the begin time
*/
void Timer :: start() throw (runtime_error)
{
	if(timerWasStarted == true)
	{
		throw runtime_error("start(): runtime_error");
	}
	
	timerWasStarted = true;
	gettimeofday(&beginTime, NULL);
}

/**
@pre  none
@post  changes the timer flag to false and records the duration
@return  none
@param  none
@brief  this function checks to see if the timer flag is false, else it sets it to false and then records the duration
*/
void Timer :: stop() throw (logic_error)
{
	if(timerWasStarted == false)
	{
		throw logic_error("stop(): logic_error");
	}
	
	timerWasStarted = false;
	gettimeofday(&duration, NULL);
}

/**
@pre  none
@post  returns the difference between the start and finish time that has been put into a double variable called, total
@return  returns the double variable, total
@param  none
@brief  this function checks to see if the timer flag is true, else it finds the difference of start and finish time, then puts them into a variable called total, and then returns it; the logic is borrowed from the example "toddiff" function, that was given to us for this assignment
*/
double Timer :: getElapsedTime() const throw (logic_error)
{
	if(timerWasStarted == true)
	{
		throw logic_error("getElapsedTime(): logic_error");
	}
	
	double startTime, finishTime, total;
	startTime = beginTime.tv_sec * 1000000 + beginTime.tv_usec;
	finishTime = duration.tv_sec * 1000000 + duration.tv_usec;
	total = (finishTime - startTime)/1000000;
		
	return total;
}
