#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "DateUtils.h"

using namespace std;

enum LogLevel { logLOW, logMEDIUM, logHIGH };
enum LogType { logINFO, logWARNING, logERROR };

class Logger {

public:
	Logger();
	~Logger();
	static void Init();
	std::ostringstream& Get(LogType level = logINFO);
	static LogLevel& LoggingLevel();
	static FILE*& Stream();
protected:
	std::ostringstream os;
private:
	Logger(const Logger&);
	std::ostringstream& GetSeparator();
	Logger& operator =(const Logger&);
	ofstream logFile;
	const string SEPARATOR = "========================================";
};

#define LOG(type) \
	if (type > Logger::LoggingLevel() || !Logger::Stream()) ; \
	else Logger().Get(type)

#endif // !LOGGER_H

