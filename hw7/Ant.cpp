#include <iostream>
#include "Ant.h"
#include "Grid.h"
using namespace std;

void Ant::move(Grid& grid)
{
	// Pick a random direction
	char dir = this->get_random_dir();
	size_t to_x = this->x, to_y = this->y;

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

	if (grid.get_cell(to_x, to_y) == nullptr && grid.move_organism(x, y, to_x, to_y))
	{
		x = to_x;
		y = to_y;
	}
}

void Ant::breed(Grid& grid)
{
	if (++time_since_last_breed > 3)
	{
		size_t adj_x = this->x, adj_y = this->y;
		
		if (this->get_adjacent_cell(adj_x, adj_y, grid))
		{
			grid.spawn(adj_x, adj_y, new Ant(adj_x, adj_y));
			time_since_last_breed = 0;
		}
	}
}

bool Ant::starve()
{
	return false;
}

void Ant::print() const
{
	cout << "o";
}

string Ant::get_type() const
{
	return "Ant";
}