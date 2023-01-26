#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "ulliststr.h"

//Use this file to test your ulliststr implementation before running the test suite

using namespace std;

int main(int argc, char* argv[])
{
   ULListStr dat;
	 dat.push_back("1");
	 dat.push_back("2");
	 dat.push_back("3");
	 dat.push_back("4");
	 dat.push_back("5");

	 cout <<dat.size();

	 cout << dat.get(5)	;
   
   

}
