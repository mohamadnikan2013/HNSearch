
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
			return 0;
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
		case '0':
			return 40;
			break;
		case '1':
			return 41;
			break;
		case '2':
			return 42;
			break;
		case '3':
			return 43;
			break;
		case '4':
			return 44;
			break;
		case '5':
			return 45;
			break;
		case '6':
			return 46;
			break;
		case '7':
			return 47;
			break;
		case '8':
			return 48;
			break;
		case '9':
			return 49;
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

	class process_of_match_calculation
	{
	public:
		multimap<int, string>* similar_words;
		process_of_match_calculation(string user_input, map<string, struct index_output::index_row>& mymap)
		{
			auto table2 = process_new_string(mymap);
			auto input_code = code_generator(user_input);
			similar_words = new multimap<int, string>;

			for (int i = input_code - 100; i < input_code + 100; i++)
			{
				for (auto kalame : (*table2)[i])
				{
					auto lev_dis = lev_distance(user_input, kalame);
					similar_words->insert({ lev_dis, kalame });

				}
			}

		}
		/*map<int, string>* output_map;*/
		void gen_output()
		{
			/*output_map = new map<int, string>;*/
			vector<string> output_vec;
			auto ret = similar_words->equal_range(1);
			for (auto it = ret.first; it != ret.second; ++it)
			{
				output_vec.push_back(it->second);
				cout << it->second << endl;
				if (output_vec.size() > 10)
					break;
			}
			ret = similar_words->equal_range(2);
			for (auto it = ret.first; it != ret.second; ++it)
			{
				output_vec.push_back(it->second);
				cout << it->second << endl;
				if (output_vec.size() > 20)
					break;
			}
			ret = similar_words->equal_range(3);
			for (auto it = ret.first; it != ret.second; ++it)
			{
				output_vec.push_back(it->second);
				cout << it->second << endl;
				if (output_vec.size() > 30)
					break;
			}


		}
	};
}
namespace machine_learning
{
	typedef struct Relation_T
	{
		string correct_word;
		int score;
	} relation_target;


	class relation
	{

	private:
		multimap <string, relation_target> object_table;

	public:
		void add(string wrong_word, string correct_word)
		{
			relation_target target;
			auto ret = object_table.equal_range(wrong_word);
			//If relation  exists in table
			if (ret.first != ret.second)
			{
				for (auto it = ret.first; it != ret.second; ++it)
				{
					if (it->second.correct_word == correct_word)
					{
						it->second.score++;
						return;
					}
				}

			}
			//If relation  exists in table
			target.correct_word = correct_word;
			target.score = 1;
			object_table.insert({ wrong_word,target });
			}
		vector<relation_target> read(string word)
		{//ATTENTION OUTPUT IS NOT SORTED//
			vector<relation_target> my_vec;
			auto ret = object_table.equal_range(word);
			for (auto it = ret.first; it != ret.second; ++it)
			{
				my_vec.push_back(it->second);
			}
			return my_vec;
		}
		string str_serializer(void)
		{
			string result;
			for (auto it = object_table.begin(); it != object_table.end(); ++it)
			{
				result += it->first + '{' + it->second.correct_word + '/' +to_string( it->second.score) + '\n';
			}
			return result;
		}
		void str_deserializer(string mystr)
		{
			auto mymap = index_output::text_splitter_booster(mystr);
			for (int counter = 1; counter <= mymap.size(); counter++)
			{
				relation_target myrelation;
				string input = mymap[counter];
				string first = input.substr(0, input.find('{'));
				myrelation.correct_word = input.substr(input.find('{')+1, input.find('/')- input.find('{'));
				myrelation.score = stoi(input.substr(input.find('/') + 1, input.size() - input.find('/')));
				object_table.insert({ first,myrelation });
			}
		}
	};
}
#endif
