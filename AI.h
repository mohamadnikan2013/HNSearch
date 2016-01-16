

#ifndef AI_H
#define AI_H

#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<map>
#include<vector>
#include<iterator>
#include "infrastructure.h"
using namespace std;



namespace new_indexing {

	unsigned int lev_distance(const std::string& s1, const std::string& s2)
	{
		const std::size_t len1 = s1.size(), len2 = s2.size();
		std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

		d[0][0] = 0;
		for (unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
		for (unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

		for (unsigned int i = 1; i <= len1; ++i)
			for (unsigned int j = 1; j <= len2; ++j)
				// note that std::min({arg1, arg2, arg3}) works only in C++11,
				// for C++98 use std::min(std::min(arg1, arg2), arg3)
				d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
		return d[len1][len2];
	}
	static int char_code(char ch)
	{
		switch (ch)
		{
		default:
			cout << "DANGER not in our words";
			break;
		case 'q':
			return 1;
			break;
		case 'a':
			return 2;
			break;
		case 'z':
			return 3;
			break;
		case 'w':
			return 4;
			break;
		case 's':
			return 5;
			break;
		case 'x':
			return 6;
			break;
		case 'e':
			return 7;
			break;
		case 'd':
			return 8;
			break;
		case 'c':
			return 9;
			break;
		case 'r':
			return 10;
			break;
		case 'f':
			return 11;
			break;
		case 'v':
			return 12;
			break;
		case 't':
			return 13;
			break;
		case 'g':
			return 14;
			break;
		case 'b':
			return 15;
			break;
		case 'y':
			return 16;
			break;
		case 'h':
			return 17;
			break;
		case 'n':
			return 18;
			break;
		case 'u':
			return 19;
			break;
		case 'j':
			return 20;
			break;
		case 'm':
			return 21;
			break;
		case 'i':
			return 22;
			break;
		case 'k':
			return 23;
			break;
		case 'o':
			return 24;
			break;
		case 'l':
			return 25;
			break;
		case 'p':
			return 26;
			break;
		}
	}
	static int code_generator(const string input1)
	{
		int itt = 0;
		for (int i = 0;i < input1.length();i++)
		{
			itt += char_code(input1[i]);
		}
		return itt;
	}
	static map<int, set<string>>* process_new_string(map<string, struct index_output::index_row>& mymap)
	{
		auto result = new map<int, set<string>>();

		for (auto item : mymap)
		{
			int my_code = code_generator((item.first));
			((*result)[my_code]).insert(item.first);
		}
		return result;
	}
}
#endif
