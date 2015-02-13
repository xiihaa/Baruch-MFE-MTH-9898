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

float convertTime(const string & datetime){  ////take the string of the format 20140804:10:00:00.574914, to convert to integer 36000.574914
	int hour = stoi(datetime.substr(9, 2));
	int min = stoi(datetime.substr(11, 2));
	float sec = stoi(datetime.substr(13, 9));
	return hour * 3600 + min * 60 + sec;
}

Tick::Tick(string CSVstring){
	vector<string> temp;
	csvline_populate(temp, CSVstring, ',');
	date = convertDate(temp[0]);
	time = convertTime(temp[0]);
	price = stof(temp[1]);
	volume = stoi(temp[2]);
}
