#include "threadfunction.h"

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include "normaltest.h"
#include "TimeSeries.h"
#include "PriceEntry.h"
using namespace std;

mutex m;
void threadfunction(std::string input, long pos, long pos_next, int i, std::string sigout, std::string noiseout){
	FILELog::ReportingLevel() = FILELog::ReportingLevel("logINFO");
	string date = "20150215";
	m.lock();
	const char* fileName = "application_scrub.log";

	FILE* pFile = fopen(fileName, "a");
	Output2FILE::Stream() = pFile;
	m.unlock();
	
	ifstream fin;
	fin.open(input);
	fin.seekg(pos);

	Scrub newseries;
//	cout << "-------" << pos << endl;
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " reading data start...";
	m.unlock();
	newseries.readfromCSV(fin, pos, pos_next);
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " reading data end";
	m.unlock();
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " scrubing data start...";
	m.unlock();
	newseries.sortByTime();
	int targetdate = convertDate("20140804:10:00:00.574914");
	newseries.markoutlierbyTime(targetdate, targetdate); //keep the date "20140804" only

       	newseries.markduplicates(); //mark duplicates
       	newseries.markoutlierbyPrice(); //mark unreasonably low and high price

       	newseries.markoutlierbyVolumn(); //mark unreasonably low and high price

       	newseries.fillreturn(); //calculate the return in each entry
       	newseries.markoutlierbyReturnRunningMean(); //mark unreasonably return spike
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " scrubing data end...";
	m.unlock();
	ofstream on2;
	on2.open(noiseout,ofstream::out|std::ofstream::app); // noise output
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " writing noise data start...";
       	newseries.removeflag(on2);  //remove marked entry
	FILE_LOG(logINFO) << "Thread " << i << " writing noise data end...";
	m.unlock();
	on2.close();
	on2.clear();
	//cout << "output "<< i <<" closed"<< endl;
	ofstream on1;
	on1.open(sigout,ofstream::out|std::ofstream::app); // signal output
	//cout << "output "<< i <<" created"<< endl;
	for (int k = 0; k < newseries.size(); k++){
	  m.lock();
		on1 << newseries[k] << endl;
		m.unlock();
	}
	on1.close();


}

void threadfunctionNormal(std::string input, long pos, long pos_next, int i, double & record, double & NMmean, double & NMvariance){
	FILELog::ReportingLevel() = FILELog::ReportingLevel("logINFO");
	string date = "20150215";
	m.lock();
	const char* fileName = "application_normal.log";

	FILE* pFile = fopen(fileName, "a");
	Output2FILE::Stream() = pFile;
	m.unlock();


	ifstream fin;
	fin.open(input);
	fin.seekg(pos);
	Scrub newseries;
	//	cout << "-------" << pos << endl;
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " reading data start...";
	m.unlock();
	newseries.readfromCSV(fin, pos, pos_next);
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " reading data end...";
	m.unlock();
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " analysing data start...";
	m.unlock();
	newseries.fillreturn(); //update the return in each entry
	Normaltest newnormal(newseries);  //normality test
	NMmean = newnormal.mean;
	NMvariance = newnormal.variance;
	record = newnormal.Jarque_Bera_test();
	m.lock();
	FILE_LOG(logINFO) << "Thread " << i << " analysing data end...";
	m.unlock();
}
