#ifndef ANT_H
#define ANT_H

#include "Organism.h"

class Ant : public Organism	// Inheritance
{

public:

	Ant(size_t x, size_t y) : Organism(x,y) {}

	void move(Grid &);
	void breed(Grid&);
	bool starve();

	void print() const;
	std::string get_type() const;
};

#endif