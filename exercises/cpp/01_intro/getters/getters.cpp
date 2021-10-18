/*
 * =====================================================================================
 *
 *       Filename:  getters.cpp
 *
 *    Description:  Read from stdin till valid integer or double is given
 *
 *        Version:  1.0
 *        Created:  18/10/21 01:41:53 AM CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Debarshi Banerjee
 *   Organization:  ICTP, SISSA
 *
 * =====================================================================================
 */

#include <iostream>
#include <iomanip>
#include <limits>

int get_int();
double get_double();

int main(int argc, char **argv)
{
	std::cout<<"Enter a valid integer"<<std::endl;
	int n{get_int()};
	std::cout<<"You have entered a valid number (integer)"<<"   "<<n<<std::endl;
	std::cout<<"Now enter a valid double"<<std::endl;
	double d{get_double()};
	std::cout<<"You have entered a valid number (double)"<<"   "<<d<<std::endl;
	return 0;
}

int get_int()
{
	int n;

	while(!(std::cin >> n))
	{
		std::cout<<"Please enter a valid integer"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return n;
}

double get_double()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	double d;

	while(!(std::cin >> d))
	{
		std::cout<<"Please enter a valid double"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return d;
}
