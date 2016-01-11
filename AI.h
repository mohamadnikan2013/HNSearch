
#ifndef AI_H
#define AI_H

#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<map>
#include<vector>
//#include<iterator>
#include "infrastructure.h"
using namespace std;
namespace new_indexing {

	//static int levenestien_distance(string& input1, string& input2)
	//static int char_code(char ch)
	static int code_generator(const string* input)
	{
		return 0;
	}
	static map<int, set<string>>* process_new_string(map<string, struct index_output::index_row>& mymap)
	{
		auto result = new map<int, set<string>>();

		for (auto item : mymap)
		{
			int my_code = code_generator(&(item.first));
			((*result)[my_code]).insert(item.first);
		}
		return result;
	}
}
#endif
