#ifndef Normaltest_H
#define Normaltest_H

#include "PriceEntry.h"
#include "TimeSeries.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "chisqr.h"

using namespace std;

double excdf(double value);   //right tail with exponetial 1/2

class Normaltest{
public:
	Scrub & TimeS;
	double size;
	double mean;
	double variance;
	double skewness;  //third order
	double kurtosis;  //fourth order

//	Normaltest(); //default constructor
	Normaltest(Scrub & list); //default constructor
	double Jarque_Bera_test();  //return the p-lavue based on the Jarqie-Bera Normality test
};

#endif
