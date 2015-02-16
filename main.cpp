
#include "PriceEntry.h"
#include "TimeSeries.h"
#include "normaltest.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

typedef Logger<Output2FILE> FILELog;

#define FILE_LOG(level) \
if (level < FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)

using namespace std;

int main(){
	//FILELog::ReportingLevel() = FILELog::ReportingLevel("logERROR");
	FILELog::ReportingLevel() = FILELog::ReportingLevel("logINFO");
	string date = "20150215";

	const char* fileName = "application.log";

	FILE* pFile = fopen(fileName, "a");
	Output2FILE::Stream() = pFile;

	ifstream in("C:\\Users\\xii\\Dropbox\\MFE\\9898\\hw1\\hw1\\data10k.csv"); //input
	ofstream on1("C:\\Users\\xii\\Dropbox\\MFE\\9898\\hw1\\hw1\\signal01.csv"); // signal output
	ofstream on2("C:\\Users\\xii\\Dropbox\\MFE\\9898\\hw1\\hw1\\noise01.csv"); // noise output
	Scrub newseries;
	FILE_LOG(logINFO) << "Reading data start...";
	newseries.readfromCSV(in);
	newseries.sortByTime();
	FILE_LOG(logINFO) << "Reading data completed";
	FILE_LOG(logINFO) << "Scrub start...";
	int targetdate = convertDate("20140804:10:00:00.574914");
	newseries.markoutlierbyTime(targetdate, targetdate); //keep the date "20140804" only

	newseries.markduplicates(); //mark duplicates
	newseries.markoutlierbyPrice(); //mark unreasonably low and high price
	

	newseries.markoutlierbyVolumn(); //mark unreasonably low and high price
	newseries.markoutlierbyPriceRunningMean(); //mark unreasonably price spike
	newseries.removeflag(on2); //remove marked entry

	newseries.fillreturn(); //calculate the return in each entry
	newseries.markoutlierbyReturnRunningMean(); //mark unreasonably return spike

	newseries.removeflag(on2);  //remove marked entry
	newseries.fillreturn(); //update the return in each entry

	//for (int i = 0; i < 20; i++){
	//	cout << newseries[i].times << newseries[i].percentreturn << endl;
	//}
	//for (int i = 0; i < newseries.size(); i++){
	//	on1 << newseries[i] << "\n";
	//}
	FILE_LOG(logINFO) << "Scrub completed";
	FILE_LOG(logINFO) << "Normality Test starts..";
	Normaltest newnormal(newseries);  //normality test
	//std::cout << newnormal.mean << "\t" << newnormal.variance << "\t" << newnormal.skewness << "\t" << newnormal.kurtosis << endl;
	std::cout << newnormal.Jarque_Bera_test() << endl;  //output the p-value

	FILE_LOG(logINFO) << "Normality Test completed";
}
