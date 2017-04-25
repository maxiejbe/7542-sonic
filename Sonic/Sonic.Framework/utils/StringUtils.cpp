#include "StringUtils.h"

string& StringUtils::ltrim(string &str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
	return str;
}

string& StringUtils::rtrim(string &str) {
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
	return str;
}

string& StringUtils::trim(string &str) {
	return ltrim(rtrim(str));
}