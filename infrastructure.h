	#ifndef INFRASTRUCTURE_H
	#define INFRASTRUCTURE_H

	#include<iostream>
	#include<fstream>
	#include <string>
	#include <cstring>
	#include <vector>
	#include <algorithm>
	#include <sstream>
	//#include <windows.h>
	#include <map>
	#include "OleanderStemmingLibrary-master/stemming/english_stem.h"
#include<set>
	using namespace std;
	namespace working_with_file {
		string file_path_replace(string content, string from, string to)
		{
			string result;
			int start_index = content.find(from);

			if (start_index == -1)
				return content;

			//std::replace(content.begin(), content.end(), from, to);
			while (start_index != -1) {
				content.replace(start_index, from.size(), to);//ATTENTION IT IS NOT SAFE: 
				start_index = content.find(from);
			}
			//int index_to_change = content.find(from);
			//content.erase(index_to_change, from.size());

			//content.insert(index_to_change, to);
			result = content;
			return result;
		}
		static vector<string> search_splitter(string input)
		{
			input = file_path_replace(input, " ", "?");
			vector<string> result;
			istringstream iss(input);
			while (iss)
			{
				string sub;
				iss >> sub;
				sub = file_path_replace(sub, "?", " ");
				result.push_back(sub);
			}
			result.erase(result.end() - 1);
			return result;
		}
		//static int id_maker(void)
		//{
		//	static int itterator = 0;
		//	itterator++;
		//	return itterator;
		//}
		class file
		{
			public:	
				//static int id_maker(void);
				string fileName;
				int size;
				int ID;
				string path;
				string content;
				short is_StartWork_handled;
				file(string st,int id)
				{
					ID=id;
					path=st;
					is_StartWork_handled = 0;
				}
				void StartWork(void);
				void EndWork(void);
				void write2(string str, short check_is_write_needed);
				void write(string str);
				//static int id_maker(void);
				//static int id_maker()
				//{
				//	static int no = 0;
				//	no++;
				//	return no;
				//}
		};
	
			void file::StartWork(void)
			{
				is_StartWork_handled = 1;
				char c;
				string inner_content = "";
				ifstream fin;
				fin.open(path.c_str());
				// while(1)
				// {
				// 	fin.get(c);
				// 	if (!fin.eof())
				// 		inner_content.append(&c);
				// 	else
				// 		break;
				// }
				string line;
				while (std::getline(fin, line))
				{
					// do something with text line
					inner_content += line + "\n";
				}
			
				content = inner_content;
				//content += "\0";
				size = content.length();
				// cout<<endl<<size<<" chars were read from "<<path<<endl;
				// cout<<endl<<endl<<"The content is: ******************************"<<endl;
				// cout<<content<<endl<<"end of content ============================="<<endl;
				fin.close();
				return;
			}
			void file::EndWork(void)
			{
			
			}
			void file::write(string str)
			{
				ofstream fout;
				fout.open(path.c_str(), std::ofstream::trunc);
				fout<<str.c_str();
				fout.close();
				content = str;
			}
			void file::write2(string str, short check_is_write_needed)
			{
				//THIS IS PRE-WRITE PROCESS
				if (check_is_write_needed)
				{
					if (!is_StartWork_handled)
						StartWork();
				

					if ((this->content) == str)
						return;
				}
			
				write(str);
			}
		
		class data_to_work
		{
			public:
				int test_property;
				vector<file> files;
			
			data_to_work(void)
			{
				test_property = 2;
			
				system("cd Data/Source & dir /s/A:-D/B > ../AppData/file_output.txt");
			
				file list_of_paths("Data/AppData/file_output.txt", 0);
				list_of_paths.StartWork();
				//list_of_paths.content += "\n";
				string paths = list_of_paths.content;
				//"E:/New Projects/SharifSearch/Data/Source/23/61039\nE:/New Projects/SharifSearch/Data/Source/23/60912\n";
				int counter = 1;
				while (paths.size() > 0)
				{
					string current_path_of_file = paths.substr(0, paths.find('\n'));
					file new_file(current_path_of_file, counter);
					counter++;
					files.push_back(new_file);
					cout<<"Importing: "<<new_file.path<<endl;
					paths = paths.substr(paths.find('\n') + 1, paths.size() - paths.find('\n') - 1) ;
				}
				//USE ONLY FOR TEST
				//cout<<files[2].path;			
			}
			void save_file_ids()
			{
				string output = "";
				for (int i = 0; i < files.size(); i++)
				{
					stringstream additional;
					additional << files[i].ID;
					output += additional.str() + "!" + files[i].path + "\n";
				}
				file id_data("Data/AppData/id.txt", 0);
				id_data.content = output;
				id_data.write2(output, 0);
				cout << "File Ids Saved" << endl;
			}

			static set<int>* retrieve_file_ids(void)
			{
				file id_data("Data/AppData/id.txt", 0);
				id_data.StartWork();
				vector<string> my_lines = search_splitter(id_data.content);
				auto result = new set<int>;
				for (auto line : my_lines)
				{
					result->insert(stoi(line.substr(0, line.find('!'))));
				}
				return result;
			}
			static map<int, string>* retrieve_file_ids_with_path(vector<string> my_lines)
			{
				/*file id_data("Data/AppData/id.txt", 0);
				id_data.StartWork();
				vector<string> my_lines = search_splitter(id_data.content);*/
				auto result = new map<int, string>;
				for (auto line : my_lines)
				{
					string id_str = line.substr(0, line.find('!'));
					string path_str = line.substr(id_str.size() + 1);
					(*result)[stoi(id_str)] = path_str;
				}
				return result;
			}
		};
	}
	namespace searching_tools{
		
		string my_replace(string content, string from, string to)
		{
			string result;
			int start_index = content.find(from);
		
			if (start_index == -1)
				return content;

			//std::replace(content.begin(), content.end(), from, to);
			while (start_index != -1) {
				content.replace(start_index, from.size(), to);//ATTENTION IT IS NOT SAFE: 
				start_index = content.find(from);
			}
			//int index_to_change = content.find(from);
			//content.erase(index_to_change, from.size());
		
			//content.insert(index_to_change, to);
			result = content;
			return result;
		}
		class a_search_result
		{
			public:
				int position;
				short is_word_checked;
				//ATTENTION: these below strings are pointer.
				working_with_file::file * file_obj;
				string* file_path;
				string* search_statement;
			a_search_result()
			{
				is_word_checked = 0;
			}
		};
		class file_and_count
		{
			public:
				int count;
				string file_path;
			file_and_count(int cou, string file_pa)
			{
				count = cou;
				file_path = file_pa;
			}
		};
		class search_work
		{
			private:
				void add_a_result(int position, string* file_path, string* search_statement, working_with_file::file* file_obj);
				int find_all_results(string* search_word, string file_contents, string* file_path, int real_index, working_with_file::file* file_obj, int found);
				void delete_no_words(string* file_contents);
				string get_around_of_str(string content, int position, int word_length);
				short is_index_valid(string* content, int index);
		 	
				//It is used for testing
			
		
			public:
				int time_of_search;
				void print_results(void);
				vector<string> statement_list;
				vector<a_search_result> result_list;
				vector<working_with_file::file> * input_data;
				void cal_for_each_file(void);
				short exist(vector<file_and_count>& list_of_file_paths, string& input);
			
			void do_it(void)
			{
				//Please SET input_data AND statement_list before running this function.
				int file_count = (*input_data).size();
				int search_words_count = this->statement_list.size();
			
				for (int i = 0; i < file_count; i++)
				{
					//int result = 0;
					(*input_data)[i].StartWork();
					for (int j = 0; j < search_words_count; j++)
					{
						find_all_results(&statement_list[j], (*input_data)[i].content, &((*input_data)[i].path), 0, &((*input_data)[i]), 0);

					}
					//if (result > 0)
					if (result_list.size() > 0)
						delete_no_words(&((*input_data)[i].content));
				}	
			
				//print_results();
		
			}
		
		};
		int search_work::find_all_results(string* search_word, string file_contents, string* file_path, int real_index, working_with_file::file* file_obj, int found)
		{
			//This is a recursive function which add results to result_list itself using add_a_result function
			//cout<<*search_word;
			int index = file_contents.find(*search_word);
			if (index == -1)
				return 0;
			// else
			// 	cout<<"found a thing";
			
		
			real_index += index;
			add_a_result(real_index, file_path, search_word, file_obj);
		
			real_index++;
			find_all_results(search_word, file_contents.substr(index + 1, file_contents.size() - index - 1), file_path, real_index, file_obj, 0);
		
			return 0;
		}
		void search_work::add_a_result(int position, string* file_path, string* search_statement, working_with_file::file* file_obj)
		{
			a_search_result new_result;
			new_result.file_path = file_path;
			new_result.search_statement = search_statement;
			new_result.position = position;
			new_result.file_obj = file_obj;
			result_list.push_back(new_result);
		}
		void search_work::delete_no_words(string* file_contents)
		{
			//FOR BETTER PERFORMANCE you should query result_list and check just not checked items
			//return;
			//cout<<endl<<endl<<*file_contents<<endl<<endl;
		
			for (int i = 0; i < result_list.size(); i++)
			{
				if (result_list[i].is_word_checked)
					continue;
			
				result_list[i].is_word_checked = 1;
				//first check
				int before_word_index = result_list[i].position - 1;
				//cout<<before_word_index<<endl;
				if(!is_index_valid(file_contents, before_word_index))
				{
					result_list.erase(result_list.begin() + i);
					i--;
					continue;
				}
			
				//second check
				int after_word_index = result_list[i].position + (*(result_list[i].search_statement)).size();
				//cout<<after_word_index<<endl;
				if (!is_index_valid(file_contents, after_word_index))
				{
					result_list.erase(result_list.begin() + i);
					i--;
					continue;
				}
			
			}
		
		}
		short search_work::is_index_valid(string* content, int index)
		{
			if (index == -1)
				return 0;
		
			if (index > ((*content).size() - 1))
				return 0;
		
			short result = 0;
		
		
			//cout<<index<<"\t"<<((*conwtent)[index])<<endl;
			//HEY THIS IS FOR PHASE1 SEARCH IT DOESN'T AFFECT PHASE 2 OR 3 AND LATER ...
			string spacing_chars[] = { " ", "\n", ",", ".", "\"", ">", "<", "!", "?", "/", "|", ")", "(", "}", "{", "\t", "+", "-", "[","]", ":" 
			};//ATTENTION IF YOU  CHANGE this array CHANGE for Index also
		
			for (int i = 0; i < 21; i++)
			{
				if (((*content)[index]) == (spacing_chars[i][0]))
					result = 1;
			}
		
			return result;
		}
		void search_work::cal_for_each_file(void)
		{
			vector<file_and_count> list_of;
			for (int i = 0; i < result_list.size(); i++)
			{
				if (!exist(list_of, *(result_list[i].file_path)))
					list_of.push_back(file_and_count(1, *(result_list[i].file_path)));
			}
		
		
			for (int i = 0; i < list_of.size(); i++)
			{
				cout<<"count is: "<<list_of[i].count<<"\t for: "<<list_of[i].file_path<<endl;
			}
		}
		short search_work::exist(vector<file_and_count>& list_of_file_paths, string& input)
		{
			for (int i = 0; i < list_of_file_paths.size(); i++)
			{
				if (list_of_file_paths[i].file_path == input)
				{
					//ADDs one
					list_of_file_paths[i].count++;
					return 1;
				}
			}
			return 0;
		}
		void search_work::print_results(void)
		{
			//<<"enter a test string to see results"<<endl;
			//string test;
			//cin>>test;
			cout<<"**********************************************************"<<endl<<"Results:"<<endl;
			cout<<"No. row number \t Start index \t path of file \n"<<"a little before and after the word place in string"<<endl<<
			"==================================================================="<<endl;
			for (int i = 0; i < result_list.size(); i++)
			{
			
				int word_size = (*(result_list[i].search_statement)).size();
				int position = result_list[i].position;
				string content = result_list[i].file_obj->content;
				string result = get_around_of_str(content, position, word_size);
			
				cout<<"No."<<i+1<<"\t"<<result_list[i].position<<"\t"<<*(result_list[i].file_path)<<endl<<
				endl<<result<<endl<<endl<<"-------------------------------------------"<<endl<<endl;
			}
			cout<<"Count is: "<<result_list.size()<<endl;
		}
		string search_work::get_around_of_str(string content, int position, int word_length)
		{
			int distance = 30;
			int start = position - distance;
			int end = position + distance + word_length; //It is for last_index
		
			string result = "";
		
			if (start < 0)
				start = 0;
	
			//cout<<start<<"\t"<<end<<endl;
			if (end >= content.size())
				end = content.size() - 1;
		
		
			if (start > 0)
				result = "...";
			
			result += content.substr(start, end - start + 1);
		
			if (end < (content.size() - 1))
				result += "...";
			
			return result;
		}
	
		//Replace Work Class
		class replace_work
		{
			private:
				void add_result(int position, working_with_file::file* file_obj);
				//void print_results(void);
		
			public:
				int time_of_replace;
			
				string from;
				string to;
				//search_work* search_obj;
			
				replace_work(string from, string to)
				{
					this->from = from;
					this->to = to;
				}
			
				void do_replace(vector<working_with_file::file> * input_data, search_work& search_it)
				{
				
	//				search_work search_it;
	//				
	//				search_it.input_data = input_data;
	//				
	//				search_it.statement_list.push_back(from);
				
					//
					//int a = search_it.time_of_search;
					//search_it.do_it();
	////				cout<<endl<<search.statement_list.size()<<endl;
					//cout<<endl<<search.statement_list.size()<<endl;
				
					//search_obj = &search; 
				
					for(int i = 0; i < search_it.result_list.size(); i++)
					{
						short is_change_needed = 0;
						// cout<<endl<<"raw_file_content_size:"<<(*(search_it.input_data))[0].content.size();
						// cout<<endl<<"search_it.result_list[i].file_obj->content: "<<search_it.result_list[i].file_obj->content.size()<<endl;
						string base_str = search_it.result_list[i].file_obj->content;
						// cout<<endl<<"base str size: "<<base_str.size();
					
						string after_replace_str;
						after_replace_str = my_replace(base_str, from, to);
						// cout<<endl<<"after str size: "<<after_replace_str.size();
					
						if (base_str != after_replace_str)
							is_change_needed = 1;
					
						if (is_change_needed)
						{
							search_it.result_list[i].file_obj->write2(after_replace_str, 0);
						}
					}				
				}
		};
	}
	//indexing namespace is mainly developed by Mohammad Nikan Ghorbani
	namespace indexing {
		
		//struct word_with_place {
		//	string word;
		//	index_output::place place;
		//};
		class normalize
		{
			public:
				void start_work(void);
				static vector<string> spliter (string str);
				vector<string> sort (vector<string> words);
				void stemming_function (void);
				//vector<string> duplicate_remover (vector<string> words);
				//void stop_words_remover(void);
				//vector<string>* stop_words;
			
				string content;
				vector<string> word;
			
				normalize(string input)
				{
					std::transform(input.begin(), input.end(), input.begin(), ::tolower);
					content = input;
					
				
					
					//stop_words = st_word;
					
					word = spliter(content);
					//stop_words_remover();
					/*if (content.find("computer") != -1)
						for (auto item : word)
							if (item == "computer")
								cout << "found computer" << endl;*/

					stemming_function();
				}			
		};
		void normalize::start_work(void)
		{
		
		}
		//void normalize::stop_words_remover(void)
		//{
		//	for (int i = 0; i < (*stop_words).size(); i++)
		//	{
		//		////NEW REMOVER
		//		//content = searching_tools::my_replace(this->content, stop_words[i], "");


		//		vector<string>::iterator itr = find(this->word.begin(), this->word.end(), (*stop_words)[i]);
		//		if (itr != this->word.end())
		//		{
		//			this->word.erase(itr);
		//		}
		//	}
		//}
		vector<string> normalize::spliter(string str)
		{
			//vector<string> spacing_chars = { " ", "\n", ",", ".", "\"", ">", "<", "!", "?", "/", "|", ")", "(", "}", "{" };
			char a = 9, b = 28, c = 96;
			stringstream as, bs, cs;
			as << a;
			bs << b;
			cs << c;
			string spacing_char_arr[] = { " ", "\n", ",", ".", "\"", ">", "<", "!", "?", "/", "|", ")", "(", "}", "{", "\t", "+", "-", "[","]", ":"
				, "~", "!", "@", "#", "$", "%", "^", "&", "*", "_", ";", "\"", "\'", "", "", "=", "\\", as.str(), bs.str(), cs.str() };//, "", ""};
			vector<string> spacing_chars(spacing_char_arr, spacing_char_arr + sizeof(spacing_char_arr) / sizeof(spacing_char_arr[0]));

			for (int i = 1; i < spacing_chars.size(); i++)
			{
				str = searching_tools::my_replace(str, spacing_chars[i], " ");
			}

			//FOR DEBUG
			if (str.find('\t') != -1)
				cout << "found \\ t in this str " << str<<endl;
			//CHECK FOR OTHER SEPERATORS
			vector<string> result;
			istringstream iss(str);
			while (iss)
			{
				string sub;
				iss >> sub;
				result.push_back(sub);
			}
			result.erase(result.end() - 1);
			return result;
		}

		void normalize::stemming_function(void)
		{
			for (int i = 0; i < normalize::word.size(); i++)
			{
				string str = normalize::word[i];

				/*if (str == "apple")
					cout << "ATTNETION: COMPUTER WAS FOUND";*/
				wstring word_ws;
				word_ws.assign(str.begin(), str.end());

				stemming::english_stem<> StemEnglish;
				StemEnglish(word_ws);
				str.assign(word_ws.begin(), word_ws.end());


				if (normalize::word[i] != str)
					if (str != "an")
						normalize::word[i] = str;
			}
		}
		vector<string> normalize::sort(vector<string> words)
			{
	//			vector<string> sbs;
	//			for(int i=0; i<words.size();i++) 
	//			for(int j=i+1; j<words.size()+1; j++) 
	//			if(words[i].compare(words[j])> 0) 
	//			{ 
	//			string t= words[ i ]; 
	//			words[ j ] = words[ i ]; 
	//			words[ i ] = t ;
	//			} 
	//			return words;
				std::sort(words.begin(), words.end());
				return words; 
			}
		/*vector<string> normalize::duplicate_remover(vector<string> words)
		{
			std::sort(words.begin(), words.end());
			words.erase( unique( words.begin(), words.end() ), words.end() );
			return words;
		}*/

		static vector<string> stop_words_vector_generator()
		{
			working_with_file::file stop_words_file("Data/AppData/stop_words.txt", 0);
			stop_words_file.StartWork();

			string stop_words_content = stop_words_file.content;
			vector<string> stop_words = indexing::normalize::spliter(stop_words_content);
			return stop_words;
		}
		static set<string>* stop_words_SET_generator()
		{
			working_with_file::file stop_words_file("Data/AppData/stop_words.txt", 0);
			stop_words_file.StartWork();

			string stop_words_content = stop_words_file.content;
			vector<string> stop_words = indexing::normalize::spliter(stop_words_content);

			auto result = new set<string>;
			for (auto item : stop_words)
				result->insert(item);

			return result;
		}
	}
	//index_output namespace is mainly developed by Mohammad Haghighat
	namespace index_output
	{
		struct place {
			//int index;
			int file_id;
		};
		struct index_row {
			string word;
			int count_of_repeats;
			vector<place> places_occurred;
		};
		map<int, string> text_splitter_booster(string& input)
		{
			int first_pos = -1;
			int counter = 1;
			map<int, string> result;
			while (1)
			{
				int second_pos = input.find('\n', first_pos + 1);
				if (second_pos == -1)
					break;
				
				result[counter] = input.substr(first_pos + 1, second_pos - first_pos);
				first_pos = second_pos;
				counter++;
			}
			return result;
			
		}
		string str_serializer(map<string, struct index_row>& input_map)
		{
			string result = "";
			for (map<string, struct index_row>::iterator it = input_map.begin(); it != input_map.end(); ++it)
			{
				//Add word
				result += it->first;
				if (it->first == "")
					cout << "My exception: str_serializer(...) is saying item->first is null"<<endl;
				//Add index_row
				stringstream ad;
				ad << it->second.count_of_repeats;
				result += "{" + it->second.word + "/" + ad.str() + "/";
				//Add index_row vector
				result += "[";
				
				for (int i = 0; i < it->second.places_occurred.size(); i++)
				{
					stringstream ad2;
					ad2 << it->second.places_occurred[i].file_id;
					result += ad2.str() + "/";
				}
				result += "]";
				result += "}\n";
				//result += it->second;
			}

			return result;
		}
		map<string, struct index_row> str_deserializer(string& main_input)
		{
			map<int, string> input_boost = text_splitter_booster(main_input);

			map<string, struct index_row> result;

			for (int counter = 1; counter <= input_boost.size(); counter++)
			{
				string input = input_boost[counter];
				int i = 0;
				while (input.size() > 0)
				{
					string map_row_str = input.substr(0, input.find('\n') + 1);
					if (input.size() >= map_row_str.size())
						input = input.substr(map_row_str.size(), input.size() - map_row_str.size());
					else
						cout << "myError: input is smaller than map_row input is " << input << endl;

					string first = map_row_str.substr(0, map_row_str.find('{')); // We don't need '{" so I didn't + 1 it!

					struct index_row second;
					int aculad_index = map_row_str.find('{');

					string second_str = map_row_str.substr(aculad_index + 1, map_row_str.find(']') - aculad_index);
					int slash_index = second_str.find('/');
					second.word = second_str.substr(0, slash_index);
					//Cleaning second_str from the word found
					second_str = second_str.substr(slash_index + 1, second_str.size() - slash_index);

					//Refreshing Index
					slash_index = second_str.find('/');

					
					second.count_of_repeats = stoi(second_str.substr(0, slash_index));

					second_str = second_str.substr(second_str.find('['), second_str.size() - second_str.find('[') - 1);
					while (second_str.size() > 0)
					{
						string file_id_str = second_str.substr(0, second_str.find('/') + 1);
						/*second_str.erase(file_id_str.size());*/
						second_str.erase(0, file_id_str.size());

						file_id_str = searching_tools::my_replace(file_id_str, "[", "");
						file_id_str = searching_tools::my_replace(file_id_str, "/", "");

						place p;
						p.file_id = std::stoi(file_id_str);
						second.places_occurred.push_back(p);


					}
					i++;

					
					if (counter % 500 == 0)
					{
						/*HANDLE  hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 2);*/
						cout << counter << " th word has been imported" << endl;
					}
					result[first] = second;
					//input is substr-ed at the first of loop
				}
			}
			return result;
		}
		struct index_row* main_search(string term, vector<index_row>& vector_of_data, vector<string>& brother, map<string, struct index_row>& map_input)
		{
			//very simple and bad performance algorithm:

			/*int distance_of = distance(vector_of_data.begin(), std::find(vector_of_data.begin(), vector_of_data.end(), term));
			cout << endl << distance_of << endl;
			if (1 == 1)
				return NULL;
			else
				return (vector_of_data.begin() + distance_of)._Ptr;*/
				//td::find(vector_of_data.begin(), vector_of_data.end(), term);
			return &map_input[term];
			///////////*vector<string>::iterator itr = find(brother.begin(), brother.end(), term);
			//////////if (itr == brother.end())
			//////////	return NULL;

			//////////int index = itr - brother.begin();
			//////////return &vector_of_data[index];*/
			//for (int i = 0; i < vector_of_data.size(); i++)
			//{
			//	if (vector_of_data[i].word == term)
			//		return &vector_of_data[i];
			//	//	USE FIND IN VECTOR
			//}

			//return NULL;
			//cout << "me: Error nothing found";
		}

		class structured_data {
		public:
			vector<index_row> index_table;
			std::map<string, index_row> index_table2;

			vector<string> index_table_brother;
			void save(void);
			void add_input(struct index_row row, vector<index_row>& table)
			{
				/*table.push_back(row);
				index_table_brother.push_back(row.word);*/
				
				index_table2[row.word] = row;
			}
			void process_inputs(vector<string>& words, int file_id)
			{
				for (int i = 0; i < words.size(); i++) 
				{
					struct index_row* ir = main_search(words[i], index_table, index_table_brother, index_table2);
					if (ir->word == "")
					{
						/*if (words[i] == "")
							string er;*/
						struct index_row new_row;
						struct place p;
						p.file_id = file_id;
						new_row.places_occurred.push_back(p);
						new_row.word = words[i];
						new_row.count_of_repeats = 1;

						add_input(new_row, index_table);
					}
					else
					{
						ir->count_of_repeats++;
						struct place p;
						p.file_id = file_id;
						ir->places_occurred.push_back(p);
					}
				}
				//std::sort(index_table_brother.begin(), index_table_brother.end());
				//std::sort(index_table.begin(), index_table.end()); PROBLEM IS HERE WRITE A FUNCTION FOR THAT
				
			}
			void remove_stop_words(vector<string>* stop_words_list)
			{
				for (int i = 0; i < stop_words_list->size(); i++)
				{
					if (index_table2.find((*stop_words_list)[i]) != index_table2.end())
						index_table2.erase((*stop_words_list)[i]);
				}
			}
		};
		void structured_data::save()
		{
			cout << "Not Completed yet!";
		}

		//THIS IS MAIN SEARCH FUNCTION, MOST OF PERFORMANCE IMPROVEMENTS MUST HAPPEN HERE
		//After Using map the performance has been improved a lot

	}

	#endif
