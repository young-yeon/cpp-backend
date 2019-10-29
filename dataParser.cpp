#include "func_list.h"

vector<string> split(const string& s, char delim) {
	vector<string> elems;
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim)) elems.push_back(item);
	return elems;
}

map<string, string> parser(const string& content) {
	map<string, string> result;

	vector<string> data = split(content, '&');
	for (string each : data) {
		vector<string> tmp = split(each, '=');
		result.insert(make_pair(tmp[0], tmp[1]));
	}
	
	return result;
}