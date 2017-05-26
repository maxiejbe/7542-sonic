#include "Logger.h"
#include <thread>

using namespace std;

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

void Logger::init() {
	string fileName = "log_" + DateUtils::getCurrentDate() + ".log";
	FILE* file = fopen(fileName.c_str(), "a");
	Logger::Stream() = file;

	Logger().GetSeparator();
	Logger().get(logINFO) << "El juego ha sido iniciado.";
}

void Logger::init(LogLevel logLevel) {
	Logger::loggingLevel() = logLevel;
	string fileName = "log_" + DateUtils::getCurrentDate() + ".log";
	FILE* file = fopen(fileName.c_str(), "a");
	Logger::Stream() = file;

	Logger().GetSeparator();
	Logger().get(logINFO) << "El juego ha sido iniciado.";
}

std::ostringstream& Logger::GetSeparator() {
	os << SEPARATOR;
	return os;
}

std::ostringstream& Logger::get(LogType type) {
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

	thread::id threadId = this_thread::get_id();
	os << "[T-" << threadId << "] ";

	return os;
}

LogLevel Logger::fromString(string level) {
	transform(level.begin(), level.end(), level.begin(), ::toupper);

	if (level == "BAJO")
		return logLOW;
	if (level == "MEDIO")
		return logMEDIUM;
	if (level == "ALTO")
		return logHIGH;

	Logger().get(logWARNING) << "El nivel de log '" << level << "' no existe. Se tomará el nivel MEDIO por defecto.";
	return logMEDIUM;
}

string Logger::toString() {
	switch (Logger::loggingLevel()) {
	case LogLevel::logLOW:
		return "bajo";
	case LogLevel::logMEDIUM:
		return "medio";
	case LogLevel::logHIGH:
		return "alto";
	default:
		return "";
	}
}

LogLevel& Logger::loggingLevel()
{
	static LogLevel loggingLevel = logMEDIUM;
	return loggingLevel;
}

FILE*& Logger::Stream()
{
	static FILE* stream = stderr;
	return stream;
}