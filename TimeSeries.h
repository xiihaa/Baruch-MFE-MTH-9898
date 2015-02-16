#ifndef TimeSeries_H
#define TimeSeries_H
#include "PriceEntry.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include <fstream>

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
	void sortByReturn();    //sort the time series by volumn

	void markduplicates();   //mark duplicates from the time series
	int size();
	void markoutlierbyPrice(); //mark outlier from the time series by recognize abnormal price
	void markoutlierbyPriceRunningMean();  //mark outlier from the time series by recognize abnormal price with running mean filter
	void markoutlierbyVolumn(); //mark outlier from the time series by recognize abnormal price
	void markoutlierbyTime(Date datelow, Date datehigh, int timeslow, int timeshigh);  //mark outlier outside a certain time range
	void markoutlierbyTime(Date datelow, Date datehigh);   //mark outlier outside a certain date
	void markoutlierbyReturn();   //mark outlier by check unreasonable return
	void markoutlierbyReturnRunningMean(); //mark outlier from the time series by recognize return spike with running mean filter
	void fillreturn();  //calculate the return at each entry

	void removeflag(std::ofstream & os);  //remove outlier and duplicates, write noises into file, output noise to os
	void removeflag();  //remove outlier and duplicates, write noises into file, no output
};
#endif
