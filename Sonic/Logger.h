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
	static void Init();
	std::ostringstream& Get(LogType level = logINFO);
	static LogLevel FromString(string level);
	static string ToString();
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

