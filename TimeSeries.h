#ifndef TimeSeries_H
#define TimeSeries_H
#include "PriceEntry.h"
#include <vector>
#include <fstream>

class Scrub
{
private:
	std::vector<Tick> TimeS;
public:
	Scrub();
	void readfromCSV(std::fstream & ip);   //readfrom CSV to build up recordvoid readfromCSV(std::fstream & ip);
};

#endif
