#include "PriceEntry.h"
#include "csvline_populate.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;

ostream & operator << (std::ostream & os, const Tick & output)
{
//	cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
//	os << "Date: " << output.date << ", Time: " << setprecision(6) << output.time << setprecision(2) << ", Price: " << output.price << ", Volume: " << setprecision(0) << output.volume;
	os << output.Initial;
	return os;
}

//ofstream & operator << (std::ofstream & os, const Tick & output) //
//{
//	std::string abc = output.Initial;
//	os << abc;
//	return os;
//}


int convertDate(const string & datetime){  //take the string of the format 20140804:10:00:00.574914, to convert to integer 20140804
	int theYear = stoi(datetime.substr(0, 4));
	//cout << theYear << endl;
	int theMonth = stoi(datetime.substr(4, 2));
	//cout << theMonth << endl;
	int theDay = stoi(datetime.substr(6, 2));
	//cout << theDay << endl;
	return theYear * 10000 + theMonth * 100 + theDay;
}

//float convertTime(const string & datetime){  ////take the string of the format 20140804:10:00:00.574914, to convert to integer 36000.574914
//	//int hour = stoi(datetime.substr(9, 1)) * 10 + stoi(datetime.substr(10, 1)) * 1;
//	//int hour = int(datetime[9] - '0') * 10 + int(datetime[10] - '0') * 10 * 1;
//	//int hour = stoi(datetime.substr(9, 2));
//	//cout << hour << endl;
//	//int min = stoi(datetime.substr(12, 1)) * 10 + stoi(datetime.substr(13, 1));
//	//int min = int(datetime[12] - '0') * 10 + int(datetime[13] - '0');
//	//int min = stoi(datetime.substr(12, 2));
//	//cout << min << endl;
//	//float sec = stoi(datetime.substr(15, 1)) * 10 + stoi(datetime.substr(16, 1)) + stof(datetime.substr(17, 7));
//	//float sec = stof(datetime.substr(15, 9));
//	//cout << sec << endl;
//	return stof(datetime.substr(9, 2)) * 3600.0 + stof(datetime.substr(12, 2)) * 60.0 + stof(datetime.substr(15, 9));
//}

Tick::Tick(string CSVstring){
	Initial = CSVstring;
	vector<string> temp;
	csvline_populate(temp, CSVstring, ',');
	date = convertDate(temp[0]);
	hours = stoi(temp[0].substr(9, 2));
	minutes = stoi(temp[0].substr(12, 2));
	seconds = stof(temp[0].substr(15, 9));
	//time = hours*3600.0 + minutes*60.0 + seconds;
	price = stof(temp[1]);
	volume = stoi(temp[2]);
}

//bool comparetickBytime(const Tick & tick1, const Tick & tick2){
//	if (tick1.date < tick2.date) return true;
//	else if (tick1.date > tick2.date) return false;
//	else{
//		return tick1.time < tick2.time;
//	}
//}

bool comparetickBytime(const Tick & tick1, const Tick & tick2){
		if (tick1.date < tick2.date) return true;
		else if (tick1.date > tick2.date) return false;
		else{
			if (tick1.hours == tick2.hours){
				if (tick1.minutes == tick2.minutes){
					return tick1.seconds < tick2.seconds;
				}
				else{
					return tick1.minutes < tick2.minutes;
				}
			}
			else{
				return tick1.hours < tick2.hours;
			}
			
		}
}

bool comparetickByprice(const Tick & tick1, const Tick & tick2){
	return tick1.price < tick2.price;
}

bool comparetickByvolumn(const Tick & tick1, const Tick & tick2){
	return tick1.volume < tick2.volume;
}
