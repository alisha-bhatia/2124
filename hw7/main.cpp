#include <iostream>
#include "Grid.h"
using namespace std;

int main()
{
	Grid the_grid;

	while (true)
	{
		the_grid.print();
		the_grid.advance_time_step();

		cout << endl << endl;
		cin.get();
	}

	return 0;
}