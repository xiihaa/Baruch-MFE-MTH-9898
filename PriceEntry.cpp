#include "PriceEntry.h"

using namespace std;

ostream & operator << (std::ostream & os, const Tick & output)
{
	os << "Date: " << output.date << ", Time: " << output.time << ", Price: " << output.price << ", Volume: " << output.volume << endl;
	return os;
}

int convertDate(const string & datetime){  //take the string of the format 20140804:10:00:00.574914, to convert to integer 20140804
	int theyear;
	int themonth;
	int theday;
	int theYear = stoi(datetime.substr(0, 4));
	int theMonth = stoi(datetime.substr(4, 2));
	int theDay = stoi(datetime.substr(6, 2));
	return theYear * 10000 + theMonth * 100 + theDay;
}
