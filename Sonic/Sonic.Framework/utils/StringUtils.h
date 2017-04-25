#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

class StringUtils {
public:
	static string &ltrim(string &str);
	static string &rtrim(string &str);
	static string &trim(string &str);
};

#endif // !STRINGUTILS_H
