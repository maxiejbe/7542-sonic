#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "DateUtils.cpp"

using namespace std;

/* Definicion de niveles de log
	LOW: INFO
	MEDIUM: INFO + WARNING
	HIGH: INFO + WARNING + ERROR
*/

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


inline Logger::Logger() {
}

inline Logger::~Logger() {
	FILE* stream = Stream();
	if (!stream)
		return;

	os << endl;
	fprintf(stream, "%s", os.str().c_str());
	fflush(stream);
}

inline void Logger::Init() {
	string fileName = "log_" + DateUtils::getCurrentDate() + ".log";
	FILE* file = fopen(fileName.c_str(), "a");
	Logger::Stream() = file;

	Logger().GetSeparator();
	Logger().Get(logINFO) << "La aplicación se ha iniciado.";
	Logger().GetSeparator();
}

inline std::ostringstream& Logger::GetSeparator() {
	os << SEPARATOR;
	return os;
}

inline std::ostringstream& Logger::Get(LogType type) {
	os << DateUtils::getCurrentDateTime() << " ";

	switch (type) {
	case LogType::logINFO:
		os << "[INFO] ";
		break;
	case LogType::logWARNING:
		os << "[WARNING] ";
		break;
	case LogType::logERROR:
		os << "[ERROR] ";
		break;
	}

	return os;
}

inline LogLevel& Logger::LoggingLevel()
{
	static LogLevel loggingLevel = logMEDIUM;
	return loggingLevel;
}

inline FILE*& Logger::Stream()
{
	static FILE* stream = stderr;
	return stream;
}

#define LOG(type) \
	if (type > Logger::LoggingLevel() || !Logger::Stream()) ; \
	else Logger().Get(type)