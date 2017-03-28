#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

class DateUtils {
public:
	static string getCurrentDateTime();
	static string getCurrentDate();
	static string getCurrentDate(bool time);
};

#endif // !DATEUTILS_H

