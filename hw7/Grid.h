#ifndef GRID_H
#define GRID_H

#include "Organism.h"

//			 x------>
//	y		[0,0][1,0][2,0][][]
//	|		[0,1][1,1][2,1][][]
//	|		[0,2][1,2][2,2][][]
//	\/		[][][][][]

class Grid
{
public:

	static const size_t GRID_HEIGHT = 20;
	static const size_t GRID_WIDTH = 20;

private:

	static const size_t INIT_NUM_ANTS = 100;
	static const size_t INIT_NUM_DOODLEBUGS = 5;

	Organism* arr[GRID_HEIGHT][GRID_WIDTH];	// Two-dimensional array of Organism pointers

	// Making the copy constructor and operator= private to prevent any outside entity from
	// calling them.
	Grid(const Grid&) {}
	void operator=(const Grid&) {}

public:

	Grid();
	~Grid();

	const Organism* get_cell(size_t x, size_t y) const;
	
	void spawn(size_t x, size_t y, Organism* new_org);
	
	bool move_organism(size_t from_x, size_t from_y, size_t to_x, size_t to_y);	// Returns true iff move performed

	void advance_time_step();

	void print() const;
};

#endif