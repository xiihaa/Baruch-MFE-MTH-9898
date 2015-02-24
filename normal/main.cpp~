#include "PriceEntry.h"
#include "TimeSeries.h"
#include "normaltest.h"
#include "threadfunction.h"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <thread>
#include <mutex>



//std::mutex m;

using namespace std;


int main(){
	//FILELog::ReportingLevel() = FILELog::ReportingLevel("logERROR");
	//FILELog::ReportingLevel() = FILELog::ReportingLevel("logINFO");
	
	const int threadNumber = 4;   //thread number definition, should customize according to input

	string input= "data10k.txt"; //input
	string sigout = "signal01.txt"; //signal output
	string noiseout = "noise01.txt"; //noise output
	
	ifstream fin;
	fin.open(input);
	fin.seekg(0, fin.end);
	const long long filelength = fin.tellg();

	const int threadNum = threadNumber;

	long position[threadNum + 1];
	for (int i = 0; i <= threadNum; i++) { position[i] = filelength / threadNum * i; }

	std::thread thread[threadNum];

	//Load multi-threads
	for (int i = 0; i < threadNum; ++i)
	{
		long pos = position[i]; long pos_next = position[i + 1];
		thread[i] = std::thread(threadfunction, input, pos, pos_next, i, sigout, noiseout);
	}

	for (int i = 0; i < threadNum; ++i)
	{
		thread[i].join();
	}

	return 0;

}
