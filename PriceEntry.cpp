#include "PriceEntry.h"

using namespace std;

ostream & operator << (std::ostream & os, const Tick & output)
{
	os << "Date: " << output.date << ", Time: " << output.time << ", Price: " << output.price << ", Volume: " << output.volume << endl;
	return os;
}
