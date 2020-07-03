#include <iostream>
#include <cstdlib>
#include "Grid.h"
#include "Ant.h"
#include "Doodlebug.h"
using namespace std;

Grid::Grid()
{
	for (size_t j = 0; j < GRID_HEIGHT; ++j)
		for (size_t i = 0; i < GRID_WIDTH; ++i)
			arr[i][j] = nullptr;

	size_t x, y;

	for (size_t i = 0; i < INIT_NUM_ANTS; ++i)
	{
		do
		{
			x = rand() % GRID_WIDTH;
			y = rand() % GRID_HEIGHT;

		} while (arr[x][y] != nullptr);

		arr[x][y] = new Ant(x, y);
	}

	for (size_t i = 0; i < INIT_NUM_DOODLEBUGS; ++i)
	{
		do
		{
			x = rand() % GRID_WIDTH;
			y = rand() % GRID_HEIGHT;

		} while (arr[x][y] != nullptr);

		arr[x][y] = new Doodlebug(x, y);
	}
}

Grid::~Grid()
{
	for (size_t j = 0; j < GRID_HEIGHT; ++j)
	{
		for (size_t i = 0; i < GRID_WIDTH; ++i)
		{
			delete arr[i][j];
			arr[i][j] = nullptr;
		}
	}
}

const Organism* Grid::get_cell(size_t x, size_t y) const
{
	if (x < GRID_WIDTH && y < GRID_HEIGHT)
		return arr[x][y];

	return nullptr;
}

void Grid::spawn(size_t x, size_t y, Organism* new_org)
{
	arr[x][y] = new_org;
}

bool Grid::move_organism(size_t from_x, size_t from_y, size_t to_x, size_t to_y)
{
	// Do not perform move if either of the locations is out of bounds
	// or if the from and to locations are identical
	if (from_x >= GRID_WIDTH || from_y >= GRID_HEIGHT ||
		to_x >= GRID_WIDTH || to_y >= GRID_HEIGHT ||
		from_x == to_x && from_y == to_y)
		return false;

	// If the to cell is already occupied, then destroy the occupant before
	// replacing it with the from occupant.
	if (arr[to_x][to_y] != nullptr)
		delete arr[to_x][to_y];

	// Perform the move
	arr[to_x][to_y] = arr[from_x][from_y];
	arr[from_x][from_y] = nullptr;

	return true;
}

void Grid::advance_time_step()
{
	for (size_t j = 0; j < GRID_HEIGHT; ++j)
		for (size_t i = 0; i < GRID_WIDTH; ++i)
			if (arr[i][j] != nullptr)
				arr[i][j]->perpare_for_update();

	for (size_t j = 0; j < GRID_HEIGHT; ++j)
	{
		for (size_t i = 0; i < GRID_WIDTH; ++i)
		{
			if (arr[i][j] != nullptr)
			{
				size_t new_x, new_y;

				if (arr[i][j]->update(*this, new_x, new_y) == true)
				{
					delete arr[new_x][new_y];
					arr[new_x][new_y] = nullptr;
				}
			}
		}
	}
}

void Grid::print() const
{
	for (size_t j = 0; j < GRID_HEIGHT; ++j)
	{
		for (size_t i = 0; i < GRID_WIDTH; ++i)
		{
			if (arr[i][j] == nullptr)
				cout << "-";
			else
				arr[i][j]->print();
		}
		cout << endl;
	}
}