#include "TimeSeries.h"
#include <vector>
#include <fstream>
#include <algorithm>

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

void Scrub::markduplicates(){
	sortByTime();
	if (TimeS.size() > 1){
		for (int i = 1; i < TimeS.size(); i++)
		{
			if (TimeS[i].date == TimeS[i - 1].date && TimeS[i].hours == TimeS[i - 1].hours && TimeS[i].minutes == TimeS[i - 1].minutes &&TimeS[i].seconds == TimeS[i - 1].seconds){
				TimeS[i].flag = 1;
			}
		}
	}
	else{
		return;
	}

}

int Scrub::size(){
	return TimeS.size();
}

void Scrub::markoutlierbyPrice(){
	unsigned long n = size();
	unsigned long percentile1_4 = n / 4;
	unsigned long percentile3_4 = n / 4*3;
	sortByPrice();
	double range = (TimeS[percentile3_4].price - TimeS[percentile1_4].price) / 2;
	float mid = TimeS[n / 2].price;

	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].price > 3 * range + mid || TimeS[i].price < std::max(mid - 3 * range, 0.0)){
			TimeS[i].flag = 1;
		}
	}


	return;

}

void Scrub::markoutlierbyVolumn(){
	unsigned long n = size();
	unsigned long percentile1_4 = n / 4;
	unsigned long percentile3_4 = n / 4 * 3;
	sortByVolumn();
	double range = (TimeS[percentile3_4].volume - TimeS[percentile1_4].volume) / 2;
	float mid = TimeS[n / 2].volume;

	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].volume > 3 * range + mid || TimeS[i].volume < std::max(mid - 3 * range, 0.0)){
			TimeS[i].flag = 1;
		}
	}


	return;



}
