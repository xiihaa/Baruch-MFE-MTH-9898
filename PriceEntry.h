#ifndef PriceEntry_H
#define PriceEntry_H

#include <string>
#include <iostream>

typedef unsigned int Date;

//float convertTime(const std::string & datetime);  ////take the string of the format 20140804:10:00:00.574914, to convert to integer 36000.574914
int convertDate(const std::string & datetime);  //take the string of the format 20140804:10:00:00.574914, to convert to integer 20140804

class Tick
{
public:
	std::string Initial;  //to store the initial record
	Date date;
	double times;
	//unsigned int hours;
	//unsigned int minutes;
	//double seconds;
	float price;
	int volume;

	double percentreturn; //return (per second)

	int flag;  //mark the data, to seperate signal or noise
	Tick(std::string CSVstring); //construct a tick form the CSV string 20140804:10:00:00.574914,1173.56,471577
	Tick(); //default constructor
	friend std::ostream & operator << (std::ostream & os, const Tick & output);  //print a tick
//	friend std::ofstream & operator << (std::ofstream & os, const Tick & output); //print a tick to file in the 20140804:10:00:00.574914,1173.56,471577 form
};

bool comparetickBytime(const Tick & tick1, const Tick & tick2); //compare two ticks by time (for sorting)
bool comparetickByprice(const Tick & tick1, const Tick & tick2); //compare two ticks by price (for sorting)
bool comparetickByvolumn(const Tick & tick1, const Tick & tick2); //compare two ticks by volume (for sorting)
bool comparetickByreturn(const Tick & tick1, const Tick & tick2); //compare two ticks by volume (for sorting)

#endif
