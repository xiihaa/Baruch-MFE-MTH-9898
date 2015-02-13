#include "PriceEntry.h"
#include "TimeSeries.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	ifstream in("data10k.csv");
	Scrub newseries;
	string s = "20140804:10:00:00.574914, 1173.56, 471577";
	cout << 1 << endl;
	Tick A(s);
	cout << 2 << endl;
	cout << A << endl;
	newseries.readfromCSV(in);
	cout << 3 << endl;
	cout << newseries[0];
	return 0;
}
