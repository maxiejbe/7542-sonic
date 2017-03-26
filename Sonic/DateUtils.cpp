#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

static class DateUtils {
public:
	static string getCurrentDateTime() {
		return getCurrentDate(true);
	}

	static string getCurrentDate() {
		return getCurrentDate(false);
	}

	static string getCurrentDate(bool time) {
		auto now = system_clock::now();
		auto in_time_t = system_clock::to_time_t(now);

		stringstream ss;
		const char *args = time ? "%Y-%m-%d %X" : "%Y-%m-%d";
		ss << put_time(localtime(&in_time_t), args);
		return ss.str();
	}
};