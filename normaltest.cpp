#include "normaltest.h"
#include <algorithm>
#include <cmath>

double excdf(double value){
	return std::exp(-0.5 * value);
}
Normaltest::Normaltest(Scrub & list) :TimeS(list){
	size = TimeS.size();
	cout << "size of the data: " << size << endl;
	mean = 0;
	variance = 0;
	skewness = 0;
	kurtosis = 0;
	for (int i = 0; i < size; i++){
		mean = mean + (TimeS[i].percentreturn / size);
		//mean = mean + TimeS[i].percentreturn;
		//cout << ": " << mean << "\t" << TimeS[i].times<< "\t"<< TimeS[i].price << "\t" << TimeS[i].volume << "\t" << TimeS[i].percentreturn / size << endl;
		//if (mean != mean || mean == numeric_limits<double>::infinity()){
		//	assert(!"nan");
		//}
	}
	//mean = mean / size;
	for (int i = 0; i < size; i++){
		variance = variance + ((TimeS[i].percentreturn - mean)*(TimeS[i].percentreturn - mean) / size);
		skewness = skewness + ((TimeS[i].percentreturn - mean)*(TimeS[i].percentreturn - mean) * (TimeS[i].percentreturn - mean) / size);
		kurtosis = kurtosis + ((TimeS[i].percentreturn - mean)*(TimeS[i].percentreturn - mean) * (TimeS[i].percentreturn - mean)*(TimeS[i].percentreturn - mean) / size);
	}
	cout << "mean of the data: " << mean << endl;
	cout << "variance of the data: " << variance << endl;
	cout << "skewness of the data: " << skewness << endl;
	cout << "kurtosis of the data: " << kurtosis << endl;
}

double Normaltest::Jarque_Bera_test(){
	double S = skewness / sqrt(variance*variance*variance);
	double K = kurtosis / variance*variance;
	double JB = (size / double(6)) * (S*S + 0.25*(K - 3)*(K - 3));
	cout << "JB Test statistic: " << JB << endl;
	double p_value = excdf(JB);
	cout << "p-value of the JB test: " << p_value << endl;
	if (p_value < 0.05){
		cout << "Null hyposthesis (return is a normal distribution) is rejected on significance level 0.05." << endl;
	}
	else{
		cout << "Null hyposthesis (return is a normal distribution) is accepted on significance level 0.05" << endl;
	}
	return p_value;
}
