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
	std::ostringstream& GetHeader();
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

	Logger().GetHeader();
}

inline std::ostringstream& Logger::GetHeader() {
	os << endl << SEPARATOR << endl;
	os << DateUtils::getCurrentDateTime();
	os << " La aplicación se ha iniciado." << endl;
	os << SEPARATOR << endl;
	return os;
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
	default:
		os << " ";
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
	static FILE* stream = stderr;
	return stream;
}

#define LOG(level) \
	if (level > Logger::ReportingLevel() || !Logger::Stream()) ; \
	else Logger().Get(level)