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
#include <string>

void get_int();
void get_double();

int main(int argc, char **argv)
{
	std::cout<<"Enter a valid integer"<<std::endl;
	get_int();
	std::cout<<"Now enter a valid double"<<std::endl;
	get_double();
	return 0;
}

void get_int()
{
	int len;
	std::string line{""};
	bool check_int;

	while((std::cin >> line))
	{
		len=line.length();
		check_int=true;

		if(line[0]!='-' && !isdigit(line[0]))
		{
			check_int=false;
			goto exit_for_int;
		}

		for(int i=1;i<len;++i)
		{
			if(!isdigit(line[i]))
			{
				check_int=false;
				break;
			}
		}

		exit_for_int:
		if(check_int)
		{
			std::cout<<"You have entered a valid integer"<<"   "<<line<<std::endl;
			break;
		}
		else
		{
			std::cout<<"Please enter a valid integer"<<std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

void get_double()
{
	int len;
	std::string line{""};
	bool check_double,check_int;

	while((std::cin >> line))
	{
		len=line.length();
		check_int=true;
		check_double=true;

		if(line[0]!='-' && !isdigit(line[0]))
		{
			check_int=false;
			check_double=false;
			goto exit_for_double;
		}

		for(int i=1;i<len;++i)
		{
			if(!isdigit(line[i]) && line[i]!='.')
			{
				check_int=false;
				check_double=false;
				break;
			}
			else if(line[i]=='.' && check_int)
			{
				check_int=false;
			}
			else if(line[i]=='.' && !check_int)
			{
				check_double=false;
				break;
			}
		}

		exit_for_double:
		if(check_double && !check_int)
		{
			std::cout<<"You have entered a valid double"<<"   "<<line<<std::endl;
			break;
		}
		else if(check_int)
		{
			std::cout<<"An integer is not a valid double...use decimal points"<<std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			std::cout<<"Please enter a valid double"<<std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}


