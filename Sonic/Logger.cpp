#include "Logger.h"

using namespace std;

/* Definicion de niveles de log
	LOW: INFO
	MEDIUM: INFO + WARNING
	HIGH: INFO + WARNING + ERROR
*/

Logger::Logger() {
}

Logger::~Logger() {
	FILE* stream = Stream();
	if (!stream)
		return;

	os << endl;
	fprintf(stream, "%s", os.str().c_str());
	fflush(stream);
}

void Logger::Init() {
	string fileName = "log_" + DateUtils::getCurrentDate() + ".log";
	FILE* file = fopen(fileName.c_str(), "a");
	Logger::Stream() = file;

	Logger().GetSeparator();
	Logger().Get(logINFO) << "La aplicación se ha iniciado.";
	Logger().GetSeparator();
}

std::ostringstream& Logger::GetSeparator() {
	os << SEPARATOR;
	return os;
}

std::ostringstream& Logger::Get(LogType type) {
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

LogLevel Logger::FromString(string level) {
	transform(level.begin(), level.end(), level.begin(), ::toupper);

	if (level == "LOW")
		return logLOW;
	if (level == "MEDIUM")
		return logMEDIUM;
	if (level == "HIGH")
		return logHIGH;
	
	Logger().Get(logWARNING) << "El nivel de log '" << level << "' no existe. Se tomará el nivel MEDIUM por defecto.";
	return logMEDIUM;
}

LogLevel& Logger::LoggingLevel()
{
	static LogLevel loggingLevel = logMEDIUM;
	return loggingLevel;
}

FILE*& Logger::Stream()
{
	static FILE* stream = stderr;
	return stream;
}