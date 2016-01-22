
#ifndef JUSTSEARCH_H
#define JUSTSEARCH_H

#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<map>
#include<vector>
//#include<iterator>
#include"infrastructure.h"
#include "AI.h"
using namespace std;
namespace bool_search
{
	class tools {
	public:
		static string wrong_finder(string input, map<string, struct index_output::index_row>& mymap)
		{
			new_indexing::process_of_match_calculation doer(input, mymap);
			string result = doer.gen_output();
			if (result == "#")
			{
				return input;
			}
			else
			{
				return result;
			}
		}
		static vector<string> search_splitter(string input)
		{
			vector<string> result;
			istringstream iss(input);
			while (iss)
			{
				string sub;
				iss >> sub;
				result.push_back(sub);
			}
			result.erase(result.end() - 1);
			return result;
		}
		static short AND_OR_determiner(string& input)
		{
			if ((input == "AND") || (input == "and"))
				return 1;
			else if ((input == "OR") || (input == "or"))
				return 0;
			else
				cout << "me: Error in AND_OR_determiner, input is " << input << endl;

			return 0;
		}
		
		
	
		static void print_set(set<int>* input)
		{
			for (auto item : (*input))
				cout << item << endl;

			cout << "Finished set print" << endl;
		}
		static set<int>* place_vector_to_Int_set(vector<index_output::place>& input)
		{
			set<int>* result = new set<int>();
			for (int i = 0; i < input.size(); i++)
			{
				result->insert(input[i].file_id);
			}
			return result;
		}
		
	};
	//template<class my_T>
	class object_to_compare
	{
	public:
		short is_string;
		short is_not;
		string main_object_if_string;
		set<int>* main_object_if_object;
		string Description;//CAN BE USED FOR DEBUG
		set<int>* object_results;
		//ATTENTION: DO NOT USE object_results BEFORE CALLING cal_result method

		//my_T main_object;
		object_to_compare(string& input)
		{
			//, short _is_not = 0
			if (input.substr(0, 4) == "NOT_")
			{
				main_object_if_string = input.substr(4);
				is_string = 1;
				Description = input + " : That was the string";
				this->is_not = 1;
			}
			else
			{
				main_object_if_string = input;
				is_string = 1;
				Description = input + " That was the string";
				this->is_not = 0;
			}
		}
		object_to_compare(set<int>* input, string& Description, short _is_not = 0)
		{
			
			main_object_if_object = input;
			is_string = 0;
			this->Description = Description;
			this->is_not = _is_not;
		}
		set<int>* cal_result(map<string, struct index_output::index_row>* main_index_table = NULL)
		{
			if (is_string)
			{
				//Needs more tests to see if duplicated file_ids in vector can cause bug.
				if (main_index_table == NULL)
					cout << "my Error main_index_table = NULL" << endl;
				object_results = tools::place_vector_to_Int_set((*main_index_table)[main_object_if_string].places_occurred);


				if (this->is_not)
				{
					auto whole_file_ids = working_with_file::data_to_work::retrieve_file_ids();
					auto final_result = new set<int>;
					set_difference(whole_file_ids->begin(), whole_file_ids->end(), object_results->begin(), object_results->end(),
						inserter(*final_result, final_result->end()));

					object_results = final_result;
				}
				return object_results;
				//* myvec = &((*main_index_table)[main_object_if_string].places_occurred);
			}
			else if (is_string == 0)
			{
				object_results = main_object_if_object;
			}
			return object_results;
		}
	};
	class compare_doer
	{
		object_to_compare* first;
		object_to_compare* second;
		
		map<string, struct index_output::index_row>* main_index_table;
		short is_and;
	public:
		object_to_compare* result;
		compare_doer(short is_and, map<string, struct index_output::index_row>* main_index_table,object_to_compare* first, object_to_compare* second)
		{
			this->first = first;
			this->second = second;
			this->is_and = is_and;
			this->main_index_table = main_index_table;
		}
		object_to_compare* calculate_result()
		{
			this->result = NULL;
			first->cal_result(main_index_table);
			second->cal_result(main_index_table);
			if (is_and)
			{
				/*first->cal_result(main_index_table);
				second->cal_result(main_index_table);*/

				set<int>* intersect = new set<int>();
				set_intersection(first->object_results->begin(), first->object_results->end(),
					second->object_results->begin(), second->object_results->end(),
					std::inserter(*intersect, intersect->begin()));

				cout << intersect->size() << " items calculated in AND operation" << endl;
				string Description = "Output set of ANDing two other objects";
				result = new object_to_compare(intersect, Description);
				
			}
			else
			{
				//Here is OR Calculations
				set<int>* merged_result = new set<int>();
				//FIRST USED ALGORITHM
				merged_result->insert(first->object_results->begin(), first->object_results->end());
				merged_result->insert(second->object_results->begin(), second->object_results->end());
				//SECOND ALGORITHM
				/*merge(first->object_results->begin(), first->object_results->end(),
					second->object_results->begin(), second->object_results->end(),
					merged_result->begin());*/
				cout << merged_result->size() << " items found in OR operation" << endl;
				string Description = "Output set of ORing two other objects";
				result = new object_to_compare(merged_result, Description);
			}
			return result;
		}
	};

	static object_to_compare* constructor_when_OBJ_ID_is_combined_with_raw_string(string& input, map<int, object_to_compare*>* saved_objects,
		map<string, struct index_output::index_row>* main_index_table)
	{
		if (input.substr(0, 6) == "OBJ_ID")
			return (*saved_objects)[stoi(input.substr(6, input.size() - 6))];
		else
		{
			auto result = new object_to_compare(input);
			result->cal_result(main_index_table);
			if (result->object_results->size() == 0)
			{
				string function_output = tools::wrong_finder(input, *main_index_table);
				result = new object_to_compare(function_output);
			}


			return result;
		}
	}

	static object_to_compare* two_word_compare(object_to_compare* first_result, string& AND_or_OR, string& second_word, map<string, index_output::index_row>* main_index_table,
		map<int, object_to_compare*>* saved_objects)
	{
		auto second = constructor_when_OBJ_ID_is_combined_with_raw_string(second_word, saved_objects, main_index_table);
		auto is_and = tools::AND_OR_determiner(AND_or_OR);

		auto compare_action = new compare_doer(is_and, main_index_table, first_result, second);
		compare_action->calculate_result();
		return compare_action->result;
	}
	
	static object_to_compare* three_word_compare_then_two_By_two(vector<string>& my_words,
		map<string, struct index_output::index_row>* main_index_table, map<int, object_to_compare*>* saved_objects)
	{
		object_to_compare* result = NULL;
		if (my_words.size() < 3)
			cout << "me: Error in three_word_compare, my_words.size() is less than 3" << endl; //FOR DEBUG
		else if ((my_words.size() % 2) != 1)
			cout << "me: Error invalid my_words.size() - it is = " << my_words.size() << endl; //FOR DEBUG

		auto first = constructor_when_OBJ_ID_is_combined_with_raw_string (my_words[0], saved_objects, main_index_table);

		auto second = constructor_when_OBJ_ID_is_combined_with_raw_string(my_words[2], saved_objects, main_index_table); //It should be 2 because my_words[1] contains AND or OR

		auto is_and = tools::AND_OR_determiner(my_words[1]);

		auto compare_action = new compare_doer(is_and, main_index_table, first, second);
		//We should call calculate_result() before using compare_action->result
		compare_action->calculate_result();
		result = compare_action->result;

		int counter = 3;
		while (counter < my_words.size())
		{
			auto new_result = two_word_compare(result, my_words[counter], my_words[counter + 1], main_index_table, saved_objects);
			delete result;
			result = new_result;
			counter += 2;
		}
		return result;
	}

	static object_to_compare* search_statement_to_result(string input,
		map<string, struct index_output::index_row>* main_index_table, map<int, object_to_compare*>* saved_objects)
	{
		auto my_search_words = tools::search_splitter(input);
		if (my_search_words.size() == 1)
		{
			auto pre_result = constructor_when_OBJ_ID_is_combined_with_raw_string(my_search_words[0], saved_objects, main_index_table);
			if (pre_result->is_string)
			{
				pre_result->cal_result(main_index_table);
				string myDes = "This is constructed object from search_statement_to_result when just one word inserted";
				auto result = new object_to_compare(pre_result->object_results, myDes);
				return result;
			}
			else
				return pre_result;
		}
		auto result = three_word_compare_then_two_By_two(my_search_words, main_index_table, saved_objects);
		return result;
	}

	static string replace_items_in_parentheses(string input, map<int, object_to_compare*>* saved_objects,
		map<string, struct index_output::index_row>* main_index_table)
	{
		//CHECK USER INPUT VALIDATION BEFORE CALLING THIS FUNCTION
		//vector<string> result;
		if (input.find("(") == -1) {
			/*result.push_back(input);*/
			return input;
		}

		string subtract_parenthesis = input;
		int first_back_parenthes_index = input.find(')', 0);
		int last_front_parenthes_before_back_index = input.find('(', 0);
		while (1)
		{
			int current = input.find('(', last_front_parenthes_before_back_index + 1);
			if ((current >= first_back_parenthes_index) || (current == -1))
				break;
			else
				last_front_parenthes_before_back_index = current;
		}

		string inner_text_of_parentheses = input.substr(last_front_parenthes_before_back_index + 1, first_back_parenthes_index - last_front_parenthes_before_back_index - 1);
		auto save_this_obj = search_statement_to_result(inner_text_of_parentheses, main_index_table, saved_objects);
		saved_objects->insert({ (saved_objects->size()) + 1, save_this_obj });

		input = searching_tools::my_replace(input, "(" + inner_text_of_parentheses + ")", "OBJ_ID" + to_string(saved_objects->size()));
		return replace_items_in_parentheses(input, saved_objects, main_index_table);
		//ADD SUPPORT TO SEARCH_STATEMENT_TO_RESULT FOR RECOGNIZING OBJ_ID FROM MAP
		//This function should be tested seperately
	}
	
	static void stop_words_in_query_checker_and_alerter(string input, set<string>* stop_words)
	{
		input = searching_tools::my_replace(input, "(", " ");
		input = searching_tools::my_replace(input, ")", " ");

		auto my_vec = tools::search_splitter(input);
		
		for (auto item : my_vec)
		{
			if (stop_words->count(item))
				cout << "Your query contains \"" + item + "\" which is a stop word and that can affect your search result in a bad way." << endl
				<< "Please use another query without this word" << endl;
			//check if exists in set
			//then alert the user
			
		}
	}
	static object_to_compare* final_result_of_query(string input,
		map<string, struct index_output::index_row>* main_index_table,
		set<string>* stop_words_set)
	{
		map<int, object_to_compare*>* saved_objects = new map<int, object_to_compare*>;
		
		
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);

		
		input = searching_tools::my_replace(input, "not ", "NOT_");
		input = searching_tools::my_replace(input, "and", "AND");
		input = searching_tools::my_replace(input, "or", "OR");
		//THESE REPLACEMENTS OF INPUT ARE NEEDED FOR CORRECT FUNCTION OF STOP WORDS REMOVER
		
		stop_words_in_query_checker_and_alerter(input, stop_words_set);

		string str = input;
		wstring word_ws;
		word_ws.assign(str.begin(), str.end());

		stemming::english_stem<> StemEnglish;
		StemEnglish(word_ws);
		str.assign(word_ws.begin(), word_ws.end());

		input = str;

		string processed_input = replace_items_in_parentheses(input, saved_objects, main_index_table);

		return search_statement_to_result(processed_input, main_index_table, saved_objects);
	}
}
#endif
