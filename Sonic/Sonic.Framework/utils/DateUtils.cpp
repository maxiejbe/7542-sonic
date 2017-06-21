#include "DateUtils.h"

string DateUtils::getCurrentDateTime() {
	return getCurrentDate(true);
}

string DateUtils::getCurrentDate() {
	return getCurrentDate(false);
}

string DateUtils::getCurrentDate(bool time) {
	auto now = system_clock::now();
	auto in_time_t = system_clock::to_time_t(now);

	stringstream ss;
	const char *args = time ? "%Y-%m-%d %X" : "%Y-%m-%d";
	struct tm timeinfo;
	localtime_s(&timeinfo, &in_time_t);
	ss << put_time(&timeinfo, args);
	return ss.str();
}