#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

class Logger {

public:

	enum LogLevel { logLOW, logMEDIUM, logHIGH };

	Logger(const string fileName = "log.txt") {
		// Open file
		logFile.open(fileName);

		// Write init line
		if (logFile.is_open()) {
			logFile << "Logger initialized" << endl;
		}
	}

	friend Logger &operator << (Logger &logger, const LogLevel logLevel) {
		logger.logFile << logger.getCurrentDateTime();

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
			logFile << "Logger terminated" << endl;
			logFile.close();
		}
	}
private:
	ofstream logFile;

	string getCurrentDateTime() {
		auto now = system_clock::now();
		auto in_time_t = system_clock::to_time_t(now);

		stringstream ss;
		ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
		return ss.str();
	}

	string getCurrentDate() {
		auto now = system_clock::now();
		auto in_time_t = system_clock::to_time_t(now);

		stringstream ss;
		ss << put_time(localtime(&in_time_t), "%Y-%m-%d");
		return ss.str();
	}
};