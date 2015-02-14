#include "TimeSeries.h"
#include <vector>
#include <fstream>

#include <iostream>


Scrub::Scrub(){
}

void Scrub::readfromCSV(std::ifstream & ip){
	if (ip.fail())  {
		std::cout << "File not found" << std::endl; int theFix;
		std::cout << "Enter a character to exit" << std::endl;
		std::cin >> theFix;
	}
	std::string newline;
	while (std::getline(ip, newline) && ip.good()){
		if (newline.empty())
		{
			continue;
		}
		TimeS.push_back(Tick(newline));
	}
}

Tick Scrub::getentry(int n){
	assert(n < TimeS.size() && n >= 0);
	return TimeS[n];
}

Tick & Scrub::operator[] (int n){
	assert(n < TimeS.size() && n >= 0);
	return TimeS[n];
}

void Scrub::sortByTime(){
	std::sort(TimeS.begin(), TimeS.end(), comparetickBytime);
}

void Scrub::sortByPrice(){
	std::sort(TimeS.begin(), TimeS.end(), comparetickByprice);
}

void Scrub::sortByVolumn(){
	std::sort(TimeS.begin(), TimeS.end(), comparetickByvolumn);
}
