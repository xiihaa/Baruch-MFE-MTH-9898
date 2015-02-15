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

	void markduplicates();   //mark duplicates from the time series
	int size();
	void markoutlierbyPrice(); //mark outlier from the time series by recognize abnormal price
	void markoutlierbyVolumn(); //mark outlier from the time series by recognize abnormal price
};
#endif
