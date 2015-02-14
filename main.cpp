#include "PriceEntry.h"
#include "TimeSeries.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	ifstream in("C:\\Users\\xii\\Dropbox\\MFE\\9898\\hw1\\hw1\\data10k.csv");
	Scrub newseries;
	string s = "20140804:10:00:00.574914, 1173.56, 471577";
	cout << 1 << endl;
	Tick A(s);
	cout << 2 << endl;
	cout << A << endl;
	newseries.readfromCSV(in);
	cout << 3 << endl;
	cout << newseries[0] << endl;
	cout << newseries[1] << endl;
	newseries.sortByTime();
	cout << 4 << endl;
	cout << newseries[0] << endl;
	cout << newseries[1] << endl;
	for (int i = 0; i < 20; i++){
		cout << newseries[i] << endl;
	}
}
