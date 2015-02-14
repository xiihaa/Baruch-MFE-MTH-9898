#ifndef PriceEntry_H
#define PriceEntry_H

#include "csvline_populate.h"
#include <string>
#include <iostream>

typedef unsigned int Date;
typedef float Time;

float convertTime(const std::string & datetime);  ////take the string of the format 20140804:10:00:00.574914, to convert to integer 36000.574914
int convertDate(const std::string & datetime);  //take the string of the format 20140804:10:00:00.574914, to convert to integer 20140804

bool comparetickBytime(const Tick & tick1, const Tick & tick2); //compare two ticks by time (for sorting)
bool comparetickByprice(const Tick & tick1, const Tick & tick2); //compare two ticks by price (for sorting)
bool comparetickByvolumn(const Tick & tick1, const Tick & tick2); //compare two ticks by volume (for sorting)


class Tick
{
public:
	Date date;
	Time time;
	float price;
	int volume;

	int flag;  //mark the data, to seperate signal or noise
	friend std::ostream & operator << (std::ostream & os, const Tick & output);  //print a tick
	Tick(std::string CSVstring); //construct a tick form the CSV string 20140804:10:00:00.574914,1173.56,471577
};

#endif
