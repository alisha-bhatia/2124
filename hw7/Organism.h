#ifndef ORGRANISM_H
#define ORGRANISM_H

#include <string>

class Grid;

class Organism
{
protected:

	size_t x, y;
	int time_since_last_breed;
	bool finished_updating;

	static char get_random_dir();	// Returns either 'N', 'S', 'E', 'W' randomly

	// Searches the grid for an empty cell that is adjacent to (adj_x,adj_y), and if
	// found, updates adj_x or adj_y with the location of the empty cell, and returns
	// true. Otherwise, returns false;
	bool get_adjacent_cell(size_t& adj_x, size_t& adj_y, const Grid&) const;
	
public:

	Organism(size_t x, size_t y) : x(x), y(y), time_since_last_breed(0) {}

	virtual ~Organism() {}	// Very important to provide a virtual destructor since
							// this class is to be used as a base class

	void perpare_for_update() { finished_updating = false; }

	virtual void move(Grid &) = 0;	// Making the move function virtual so that when it is
								// called on a Organism pointer, the derived class overload
								// is called instead. The = 0 furthermore makes this a
								// pure virtual function, which means this class does not
								// implement the move function. The derived classes must
								// implement the move function.
	virtual void breed(Grid&) = 0;
	virtual bool starve() = 0;	// Returns true if and only if Organism has starved to death

	bool update(Grid&, size_t& new_x, size_t& new_y);
	// Returns true if and only if the organism should subsequently
	// be destroyed after this function call.

	virtual void print() const = 0;

	virtual std::string get_type() const = 0;
};

#endif