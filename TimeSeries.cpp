#include "TimeSeries.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
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

void Scrub::sortByReturn(){
	std::sort(TimeS.begin(), TimeS.end(), comparetickByreturn);
}

void Scrub::markduplicates(){
	sortByTime();
	if (TimeS.size() > 1){
		for (int i = 1; i < TimeS.size(); i++)
		{
			if (TimeS[i].date == TimeS[i - 1].date && TimeS[i].times == TimeS[i - 1].times){
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
		if (TimeS[i].price > 2* range + mid || TimeS[i].price < std::max(mid - 2* range, 0.0)){
			TimeS[i].flag = 1;
		}
	}
	return;
}

void Scrub::markoutlierbyPriceRunningMean(){
	sortByTime();
	double msize = 200;
	double runningmean = 0;
	double max = 0;
	double min = 1000000000000000;
	double range;

	for (int i = 0; i < TimeS.size(); i++){
		if (i < msize) {
			runningmean = runningmean + (TimeS[i].price / msize);
			if (TimeS[i].price > max){ max = TimeS[i].price; }
			if (TimeS[i].price < min) { min = TimeS[i].price; }
		}
		else{
			range = 0.1*(max - min);
			if (TimeS[i].price > runningmean + range || TimeS[i].price < runningmean - range){
				TimeS[i].flag = 1;
			}
			runningmean = runningmean + (TimeS[i].price / msize) - (TimeS[i - msize].price / msize);
			if (TimeS[i].price > max){ max = TimeS[i].price; }
			if (TimeS[i].price <min) { min = TimeS[i].price; }
		}
	}
	return;
}

void Scrub::markoutlierbyReturnRunningMean(){
	sortByTime();
	double msize = 200;
	double runningmean = 0;
	double max = -100000000000000;
	double min = 1000000000000000;
	double range;

	for (int i = 0; i < TimeS.size(); i++){
		if (i < msize) {
			runningmean = runningmean + (TimeS[i].percentreturn / msize);
			if (TimeS[i].percentreturn > max){ max = TimeS[i].percentreturn; }
			if (TimeS[i].percentreturn < min) { min = TimeS[i].percentreturn; }
		}
		else{
			range = 0.1*(max - min);
			if (TimeS[i].percentreturn > runningmean + range || TimeS[i].percentreturn < runningmean - range){
				TimeS[i].flag = 1;
			}
			runningmean = runningmean + (TimeS[i].percentreturn / msize) - (TimeS[i - msize].percentreturn / msize);
			if (TimeS[i].percentreturn > max){ max = TimeS[i].percentreturn; }
			if (TimeS[i].percentreturn <min) { min = TimeS[i].percentreturn; }
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

void Scrub::markoutlierbyTime(Date datelow, Date datehigh, int timeslow, int timeshigh){
	Tick ticklow;
	ticklow.date = datelow;
	ticklow.times = timeslow;
	Tick tickhigh;
	tickhigh.date = datehigh;
	tickhigh.times = timeshigh;
	for (int i = 0; i < TimeS.size(); i++){
		if (comparetickBytime(TimeS[i], ticklow) || comparetickBytime(tickhigh, TimeS[i])){
			TimeS[i].flag = 1;
		}
	}
}

void Scrub::markoutlierbyReturn(){
	unsigned long n = size();
	unsigned long percentile1_4 = n / 4;
	unsigned long percentile3_4 = n / 4 * 3;
	sortByReturn();
	double range = (TimeS[percentile3_4].percentreturn - TimeS[percentile1_4].percentreturn) / 2;
	float mid = TimeS[n / 2].percentreturn;

	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].percentreturn > 8 * range + mid || TimeS[i].percentreturn < std::max(mid - 8 * range, 0.0)){
			TimeS[i].flag = 1;
		}
	}

	return;
}

void Scrub::markoutlierbyTime(Date datelow, Date datehigh){
	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].date > datehigh || TimeS[i].date < datelow){
			TimeS[i].flag = 1;
		}
	}
}

void Scrub::fillreturn(){
	sortByTime();
	TimeS[0].percentreturn = 0;
	double timediff;
	for (int i = 1; i < TimeS.size(); i++){
		timediff = TimeS[i].times - TimeS[i - 1].times;
		TimeS[i].percentreturn = (log(TimeS[i].price / TimeS[i - 1].price)) / timediff/ 1000;
		/*TimeS[i].percentreturn = (log(TimeS[i].price / TimeS[i - 1].price));*/
	}
}

void Scrub::removeflag(std::ofstream & os){
	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].flag >0){
			os << TimeS[i].Initial << "\n";
			TimeS.erase(TimeS.begin() + i);
			i--;
		}
	}
}

void Scrub::removeflag(){
	for (int i = 0; i < TimeS.size(); i++){
		if (TimeS[i].flag >0){
			TimeS.erase(TimeS.begin() + i);
			i--;
		}
	}
}
