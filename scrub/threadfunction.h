#ifndef threadfunction_h
#define threadfunction_h

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include "Logger.h"
#include "TimeSeries.h"
#include "PriceEntry.h"

typedef Logger<Output2FILE> FILELog;

#define FILE_LOG(level) \
if (level < FILELog::ReportingLevel() || !Output2FILE::Stream()) ; \
else FILELog().Get(level)

void threadfunction(std::string input, long pos, long pos_next, int i, std::string sigout, std::string noiseout);

void threadfunctionNormal(std::string input, long pos, long pos_next, int i, double & record, double & NMmean, double & NMvariance);

#endif
