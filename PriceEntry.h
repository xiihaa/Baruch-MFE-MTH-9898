#ifndef PriceEntry_H
#define PriceEntry_H

#include <iostream>

typedef unsigned int Date;
typedef float Time;

class Tick
{
public:
	Date date;
	Time time;
	float price;
	int volume;
	int flag; //to mark the valid data
	friend std::ostream & operator << (std::ostream & os, const Tick & output); //to print the Tick
};

#endif
