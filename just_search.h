
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
using namespace std;
namespace bool_search
{
	class tools {
	public:
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
		object_to_compare(string& input, short _is_not = 0)
		{
			main_object_if_string = input;
			is_string = 1;
			Description = input + " That was the string";
			this->is_not = _is_not;
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
				object_results = tools::place_vector_to_Int_set((*main_index_table)[main_object_if_string].places_occurred);
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
		object_to_compare* result;
		map<string, struct index_output::index_row>* main_index_table;
		short is_and;
	public:
		compare_doer(short is_and, map<string, struct index_output::index_row>* main_index_table,
			object_to_compare* first, object_to_compare* second)
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
}
#endif
