/*
 * =====================================================================================
 *
 *       Filename:  uniq.cpp
 *
 *    Description:  Cheap imitation of 'uniq' program in Unix
 *
 *        Version:  1.0
 *        Created:  15/10/21 05:51:19 PM CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Debarshi Banerjee
 *   Organization:  ICTP, SISSA
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>

// ONLY CONSECUTIVE LINES NEED TO HAVE REPETITIONS

int main(int argc, char **argv)
{
	int counter{0};		// counter set as 0 to differentiate between first ever run of the loop and later runs
	std::string last{""};	// last will store the last line of the input, it is initialised as an empty string for convenience

	// std::string line;
	// while(std::getline(std::cin,line))
	// for loop is probably better since 'line' has limited scope

	for(std::string line; std::getline(std::cin,line);)
	{
		if(last==line & line!="")
		// whenever 2 lines match, increase counter by 1, but not if first user-input line is also empty
		{
			counter+=1;
		}

		else if(last=="" && counter!=0)
		// whenever the last input line is empty, and it is not the very first run of the loop, don't change the counter
		{
			counter=counter;
		}

		else if(last=="" && counter==0)
		// whenever the last input line is empty, and counter=0, it means it is the very first run of the loop, so initialise counter as 1
		{
			counter=1;
		}

		else
		// for all other conditions when last line and current line don't match, print the no. of repetitions, and reset counter to 1 for next run
		{
			std::cout<<counter<<"   "<<last<<std::endl;
			counter=1;
		}

		// store current line as last line at the end
		last=line;

	}
	return 0;
}

