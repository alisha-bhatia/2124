#include <cstdlib>
#include "Organism.h"
#include "Grid.h"
using namespace std;

char Organism::get_random_dir()
{
	int dir = rand() % 4;

	switch (dir)
	{
	case 0: return 'N';
	case 1: return 'S';
	case 2: return 'E';
	}
	return 'W';
}

bool Organism::get_adjacent_cell(size_t& adj_x, size_t& adj_y, const Grid& grid) const
{
	if (adj_y > 0 && grid.get_cell(adj_x, adj_y - 1) == nullptr)
	{
		--adj_y;
		return true;
	}
	if (adj_x > 0 && grid.get_cell(adj_x - 1, adj_y) == nullptr)
	{
		--adj_x;
		return true;
	}
	if (adj_y < Grid::GRID_HEIGHT - 1 && grid.get_cell(adj_x, adj_y + 1) == nullptr)
	{
		++adj_y;
		return true;
	}
	if (adj_x < Grid::GRID_WIDTH - 1 && grid.get_cell(adj_x + 1, adj_y) == nullptr)
	{
		++adj_x;
		return true;
	}
	return false;
}

bool Organism::update(Grid& grid, size_t& new_x, size_t& new_y)
{
	if (finished_updating)
		return false;

	move(grid);
	breed(grid);
	finished_updating = true;
	new_x = x;
	new_y = y;
	return starve();
}