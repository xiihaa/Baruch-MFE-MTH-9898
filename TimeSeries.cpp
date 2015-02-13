#include "TimeSeries.h"
#include <vector>
#include <fstream>

Scrub::Scrub(){
}

void Scrub::readfromCSV(std::fstream & ip){
	std::string newline;
	while (std::getline(ip, newline)){
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
