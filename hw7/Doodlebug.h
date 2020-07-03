#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Organism.h"

class Doodlebug : public Organism	// Inheritance
{
	int time_since_last_meal;

public:

	Doodlebug(size_t x, size_t y) : Organism(x, y), time_since_last_meal(0) {}

	void move(Grid&);
	void breed(Grid&);
	bool starve();

	void print() const;
	std::string get_type() const;
};

#endif