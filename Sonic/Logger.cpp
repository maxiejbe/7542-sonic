#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "DateUtils.cpp"

using namespace std;

enum LogLevel { logLOW, logMEDIUM, logHIGH };

class Logger {

public:
	Logger();
	~Logger();
	static void Init();
	std::ostringstream& Get(LogLevel level = logMEDIUM);
	static LogLevel& ReportingLevel();
	static FILE*& Stream();
protected:
	std::ostringstream os;
private:
	Logger(const Logger&);
	Logger& operator =(const Logger&);
	ofstream logFile;
};


inline Logger::Logger() {
}

inline Logger::~Logger() {
	FILE* pStream = Stream();
	if (!pStream)
		return;

	os << endl;
	fprintf(pStream, "%s", os.str().c_str());
	fflush(pStream);
}

inline void Logger::Init() {
	string fileName = "log_" + DateUtils::getCurrentDate() + ".log";
	FILE* pFile = fopen(fileName.c_str(), "a");
	Logger::Stream() = pFile;

	Logger().Get(logLOW) << "Inicializado!" << endl;
}

inline std::ostringstream& Logger::Get(LogLevel level) {
	os << DateUtils::getCurrentDateTime();

	switch (level) {
	case LogLevel::logLOW:
		os << " [LOW] ";
		break;
	case LogLevel::logMEDIUM:
		os << " [MEDIUM] ";
		break;
	case LogLevel::logHIGH:
		os << " [HIGH] ";
		break;
	}

	return os;
}

inline LogLevel& Logger::ReportingLevel()
{
	static LogLevel reportingLevel = logMEDIUM;
	return reportingLevel;
}

inline FILE*& Logger::Stream()
{
	static FILE* pStream = stderr;
	return pStream;
}

#define LOG(level) \
	if (level > Logger::ReportingLevel() || !Logger::Stream()) ; \
	else Logger().Get(level)