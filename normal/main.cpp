#include "PriceEntry.h"
#include "TimeSeries.h"
#include "normaltest.h"
#include "threadfunction.h"
#include <iomanip>
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <thread>
#include <mutex>

double excdf(double value){  //for the P value of the JB test
	return std::exp(-0.5 * value);  
}

typedef Logger<Output2FILE> FILELog;

#define FILE_LOG(level) \
if (level < FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)

//std::mutex m;

using namespace std;


int main(){
	//FILELog::ReportingLevel() = FILELog::ReportingLevel("logERROR");
	FILELog::ReportingLevel() = FILELog::ReportingLevel("logINFO");
	string date = "20150215";

	const char* fileName = "application_normal.log";

	FILE* pFile = fopen(fileName, "a");
	Output2FILE::Stream() = pFile;

	const int threadNumber = 4;   //thread number definition, should customize according to input

	string input = "signal01.txt"; //input

	ifstream fin;
	fin.open(input);
	fin.seekg(0, fin.end);
	const long long filelength = fin.tellg();

	const int threadNum = threadNumber;

	long position[threadNum + 1];
	for (int i = 0; i <= threadNum; i++) { position[i] = filelength / threadNum * i; }

	std::thread thread[threadNum];
	double JBstatistics[threadNum];
	double NMmean[threadNum];
	double NMvariance[threadNum];

	double mean = 0;
	double variance = 0;
	double JBtest = 0;
	double p_value;

	//Load multi-threads
	for (int i = 0; i < threadNum; ++i)
	{
		long pos = position[i]; long pos_next = position[i + 1];
		thread[i] = std::thread(threadfunctionNormal, input, pos, pos_next, i, std::ref(JBstatistics[i]), std::ref(NMmean[i]), std::ref(NMvariance[i]));
	}

	for (int i = 0; i < threadNum; ++i)
	{
		thread[i].join();
	}

	for (int i = 0; i < threadNum; ++i){
		mean = mean + NMmean[i] / threadNum;
		
		variance = variance + NMvariance[i] / threadNum;
		JBtest = JBtest + JBstatistics[i] / threadNum;
	}

	p_value = excdf(JBtest);
	cout << setprecision(10) << "The test statistics of JB test is " << JBtest <<". "<< endl << "p-value of the JB test: " << p_value << endl;
	if (p_value < 0.05){
		cout << "Null hyposthesis (return is a normal distribution) is rejected on significance level 0.05." << endl;
	}
	else{
		cout << "Null hyposthesis (return is a normal distribution) is accepted on significance level 0.05" << endl;
	}


	return 0;

}
