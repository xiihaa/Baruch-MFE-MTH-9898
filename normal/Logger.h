#ifndef LOGGER_H_
#define LOGGER_H_
#pragma warning(disable : 4996)
#include <sstream>
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <string>

using namespace std;

//Define Enum for each log level
enum TLogLevel {logDEBUG, logINFO, logWARNING, logERROR};

#define CURR_TIMER std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

template <typename OutputPolicy>
class Logger
{
public:
   Logger();
   virtual ~Logger();
   std::ostringstream& Get(TLogLevel level = logINFO);

public:
   static TLogLevel& ReportingLevel();

   static TLogLevel ReportingLevel(string mode);
protected:
   std::ostringstream os;
private:
   Logger(const Logger&);
   Logger& operator =(const Logger&);
private:
   TLogLevel messageLevel;
};


inline const char* ToString(TLogLevel v)
{
    switch (v)
    {
        case logERROR:   return "logERROR";
        case logWARNING:   return "logWARNING";
        case logINFO: return "logINFO";
        default:      return "logDEBUG";
    }
}

inline TLogLevel FromString(string mode)
{
    if (mode == "logERROR")
    	return logERROR;
    else if (mode == "logWARNING")
    	return logWARNING;
    else if (mode == "logINFO")
    	return logINFO;
    else
    	return logDEBUG;
}

template <typename T>
Logger<T>::Logger()
{
}

inline string NowTime()
{
	time_t tt = CURR_TIMER;

	string t( ctime( &tt ) );

	return t.substr(0, t.length() - 1);
}

template <typename OutputPolicy>
std::ostringstream& Logger<OutputPolicy>::Get(TLogLevel level)
{
	os << "- " << NowTime();
	os << " " << ToString(level) << ": ";

	messageLevel = level;

	return os;
}

template <typename OutputPolicy>
Logger<OutputPolicy>::~Logger()
{
	os << std::endl;

	OutputPolicy::Output(os.str().c_str());
}

template <typename T>
TLogLevel& Logger<T>::ReportingLevel()
{
    static TLogLevel reportingLevel = logDEBUG;
    return reportingLevel;
}

template <typename T>
TLogLevel Logger<T>::ReportingLevel(string mode)
{
    return FromString(mode);
}

class Output2FILE // implementation of OutputPolicy
{
   public:
   static FILE*& Stream();
   static void Output(const std::string& msg);
};


inline FILE*& Output2FILE::Stream()
{
   static FILE* pStream = stderr;
   return pStream;
}

inline void Output2FILE::Output(const std::string& msg)
{
    FILE* pStream = Stream();
    if (pStream)
    {
	    fprintf(pStream, "%s", msg.c_str());
	    fflush(pStream);
    }
}

#endif /* LOGGER_H_ */
