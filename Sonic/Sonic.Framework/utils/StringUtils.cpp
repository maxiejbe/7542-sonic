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

void StringUtils::split(vector<string>* items, string str, string delimiter)
{
	istringstream iss(str);
	string item;
	while (getline(iss, item, *delimiter.c_str())) {
		string itemToInsert = item;
		items->push_back(itemToInsert);
	}
}

/*string & StringUtils::join(vector<string>, string delimiter)
{
	// TODO: insert return statement here
}*/

