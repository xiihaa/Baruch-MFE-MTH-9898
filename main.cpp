#include "PriceEntry.h"
#include "TimeSeries.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream in("data10k.csv");
	Scrub newseries;
	newseries.readfromCSV(in);
	cout << newseries[0];
}
