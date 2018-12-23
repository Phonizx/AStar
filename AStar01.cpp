// AStar01.cpp : Defines the entry point for the console application.
//

#include "Cell.h"
#include "AStar.h"

#include <iostream>

using namespace std; 

int main()
{
	AStar a;
	Cell start(0, 0);
	Cell target(5, 5);
	
	cout << a;
	cout << "Searching valid path ..." << endl;
	a.path_finding(start, target);


	cout << a;
	a.print();
	getchar();
	return 0;
}

