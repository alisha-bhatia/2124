#include <iostream>
#include "Doodlebug.h"
#include "Grid.h"
using namespace std;

void Doodlebug::move(Grid& grid)
{
	size_t to_x = this->x, to_y = this->y;

	// If there is an adjacent Ant, that's where we want to move
	if (x > 0 && grid.get_cell(x - 1, y) != nullptr && grid.get_cell(x - 1, y)->get_type() == "Ant")
		--to_x;
	else if (y > 0 && grid.get_cell(x, y - 1) != nullptr && grid.get_cell(x, y - 1)->get_type() == "Ant")
		--to_y;
	else if (grid.get_cell(x + 1, y) != nullptr && grid.get_cell(x + 1, y)->get_type() == "Ant")
		++to_x;
	else if (grid.get_cell(x, y + 1) != nullptr && grid.get_cell(x, y + 1)->get_type() == "Ant")
		++to_y;

	if (x == to_x && y == to_y)
	{
		// Pick a random direction
		char dir = this->get_random_dir();

		if (dir == 'N')
		{
			if (to_y > 0)
				--to_y;
		}
		else if (dir == 'W')
		{
			if (to_x > 0)
				--to_x;
		}
		else if (dir == 'S')
			++to_y;
		else if (dir == 'E')
			++to_x;
	}
	else
		time_since_last_meal = 0;

	if (grid.move_organism(x, y, to_x, to_y))
	{
		x = to_x;
		y = to_y;
	}
}

void Doodlebug::breed(Grid& grid)
{
	if (++time_since_last_breed > 8)
	{
		size_t adj_x = this->x, adj_y = this->y;

		if (this->get_adjacent_cell(adj_x, adj_y, grid))
		{
			grid.spawn(adj_x, adj_y, new Doodlebug(adj_x, adj_y));
			time_since_last_breed = 0;
		}
	}
}

bool Doodlebug::starve()
{
	return ++time_since_last_meal > 3;
}

void Doodlebug::print() const
{
	cout << "X";
}

string Doodlebug::get_type() const
{
	return "Doodlebug";
}