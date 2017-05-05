#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include <sstream>

using namespace std;

class StringUtils {
public:
	static string &ltrim(string &str);
	static string &rtrim(string &str);
	static string &trim(string &str);
	static void split(vector<string>* items, string str, string delimiter);
	static char* convert(string &str);
	//static string &join(vector<string>, string delimiter);
};

#endif // !STRINGUTILS_H
