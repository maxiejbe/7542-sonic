#include <fstream>
#include <string>
#include "DateUtils.cpp"

using namespace std;

class Logger {

public:

	enum LogLevel { logLOW, logMEDIUM, logHIGH };

	Logger() {
		// Open file
		string fileName = "log_" + DateUtils::getCurrentDate() + ".txt";
		logFile.open(fileName);

		// Write init line
		if (logFile.is_open()) {
			logFile << "Logger initialized" << endl << endl;
		}
	}

	friend Logger &operator << (Logger &logger, const LogLevel logLevel) {
		logger.logFile << DateUtils::getCurrentDateTime();

		switch (logLevel) {
		case LogLevel::logLOW:
			logger.logFile << " [LOW] ";
			break;
		case LogLevel::logMEDIUM:
			logger.logFile << " [MEDIUM] ";
			break;
		case LogLevel::logHIGH:
			logger.logFile << " [HIGH] ";
			break;
		}

		return logger;
	}

	friend Logger &operator << (Logger &logger, const char *text) {
		logger.logFile << text << endl;
		return logger;
	}

	~Logger() {
		// Write end line and close file
		if (logFile.is_open()) {
			logFile << endl << "Logger terminated" << endl;
			logFile.close();
		}
	}
private:
	ofstream logFile;
};