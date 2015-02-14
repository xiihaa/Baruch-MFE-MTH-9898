#ifndef TimeSeries_H
#define TimeSeries_H
#include "PriceEntry.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>

class Scrub
{
private:
	std::vector<Tick> TimeS;
public:
	Scrub();
	void readfromCSV(std::ifstream & ip);   //readfrom CSV to build up record
	Tick getentry(int n);  //return the nth entry of the time series;
	Tick & operator[] (int n); //return the nth entry of the time series;

	void sortByTime();   //sort the time series by time
	void sortByPrice();   //sort the time series by price
	void sortByVolumn();    //sort the time series by volumn

#endif
