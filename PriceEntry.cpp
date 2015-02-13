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
#include "PriceEntry.h"
#include "csvline_populate.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

ostream & operator << (std::ostream & os, const Tick & output)
{
	os << "Date: " << output.date << ", Time: " << output.time << ", Price: " << output.price << ", Volume: " << output.volume << endl;
	return os;
}

int convertDate(const string & datetime){  //take the string of the format 20140804:10:00:00.574914, to convert to integer 20140804
	int theYear = stoi(datetime.substr(0, 4));
	//cout << theYear << endl;
	int theMonth = stoi(datetime.substr(4, 2));
	//cout << theMonth << endl;
	int theDay = stoi(datetime.substr(6, 2));
	//cout << theDay << endl;
	return theYear * 10000 + theMonth * 100 + theDay;
}

float convertTime(const string & datetime){  ////take the string of the format 20140804:10:00:00.574914, to convert to integer 36000.574914
	//int hour = stoi(datetime.substr(9, 1)) * 10 + stoi(datetime.substr(10, 1)) * 1;
	//int hour = int(datetime[9] - '0') * 10 + int(datetime[10] - '0') * 10 * 1;
	int hour = stoi(datetime.substr(9, 2));
	//cout << hour << endl;
	//int min = stoi(datetime.substr(12, 1)) * 10 + stoi(datetime.substr(13, 1));
	//int min = int(datetime[12] - '0') * 10 + int(datetime[13] - '0');
	int min = stoi(datetime.substr(12, 2));
	//cout << min << endl;
	//float sec = stoi(datetime.substr(15, 1)) * 10 + stoi(datetime.substr(16, 1)) + stof(datetime.substr(17, 7));
	float sec = stof(datetime.substr(15, 9));
	//cout << sec << endl;
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
