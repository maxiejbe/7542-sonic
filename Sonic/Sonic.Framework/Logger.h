#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include "utils/DateUtils.h"

using namespace std;

/* Definicion de niveles de log
	LOW: ERROR
	MEDIUM: ERROR + WARNING
	HIGH: ERROR + WARNING + INFO
*/

enum LogLevel { logLOW, logMEDIUM, logHIGH };
enum LogType { logERROR, logWARNING, logINFO };

class Logger {

public:
	Logger();
	~Logger();
	static void init();
	static void init(LogLevel logLevel);
	std::ostringstream& get(LogType level = logINFO);
	static LogLevel fromString(string level);
	static string toString();
	static LogLevel& loggingLevel();
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
	if (type > Logger::loggingLevel() || !Logger::Stream()) ; \
	else Logger().get(type)

#endif // !LOGGER_H

