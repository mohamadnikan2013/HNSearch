#include<iostream>
#include<string>
#include "infrastructure.h"
#include "just_search.h"
#include "AI.h"
using namespace std;
//using namespace searching_tools;
using namespace working_with_file;
namespace phase4
{
	void test()
	{
		cout << "Started" << endl;
		cout << new_indexing::lev_distance("hell","hallooko");
		file myfile("Data/AppData/index.txt", 0);
		myfile.StartWork();
		map<string, struct index_output::index_row> mymap = index_output::str_deserializer(myfile.content);
		cout << mymap.size() << endl;

		auto new_map = new_indexing::process_new_string(mymap);
		cout << new_map->size() << endl;
	}
	
}
namespace phase3
{
	void test_of_final_query_resolver()
	{
		file myfile("Data/AppData/index.txt", 0);
		myfile.StartWork();
		map<string, struct index_output::index_row> mymap = index_output::str_deserializer(myfile.content);
		cout << mymap.size() << endl;

		while (1)
		{
			cout << "Please Enter your query:" << endl;
			string search_string;

			getline(cin, search_string);
			auto result = bool_search::final_result_of_query(search_string, &mymap);
			cout << "Count of matches: " << result->main_object_if_object->size() << endl << endl;
		}
	}
	void test_of_string_to_result()
	{
		file myfile("Data/AppData/index.txt", 0);
		myfile.StartWork();
		map<string, struct index_output::index_row> mymap = index_output::str_deserializer(myfile.content);
		cout << mymap.size() << endl;
		cout << "Please Enter string without )(" << endl;
		string search_string;
		
		getline(cin, search_string);
		auto result = bool_search::search_statement_to_result(search_string, &mymap, NULL);
		cout << "Count of matches: " << result->main_object_if_object->size() << endl;
	}
	void test()
	{
		file myfile("Data/AppData/index.txt", 0);
		myfile.StartWork();
		map<string, struct index_output::index_row> mymap = index_output::str_deserializer(myfile.content);
		cout << mymap.size() << endl;
		string first_str = "hello";
		auto first = new bool_search::object_to_compare(first_str);
		string second_str = "help";
		auto second = new bool_search::object_to_compare(second_str);
		auto test = new bool_search::compare_doer(0
			, &mymap, first, second);
		test->calculate_result();
		string third_str = "point";
		auto new_second = new bool_search::object_to_compare(third_str);
		cout << "second and" << endl;
		auto test2 = new bool_search::compare_doer(1, &mymap, test->result, new_second);
		test2->calculate_result();
		string salam;
	}
}
namespace phase2{
	void index()
	{
		index_output::structured_data s;

		data_to_work d;
		d.save_file_ids();
		cout << endl << "Processing..." << endl;
		string current_content = "";
		
		working_with_file::file stop_words_file("Data/AppData/stop_words.txt", 0);
		stop_words_file.StartWork();

		string stop_words_content = stop_words_file.content;
		vector<string> stop_words = indexing::normalize::spliter(stop_words_content);
		string console_output = "";
		for (int i = 0; i < d.files.size(); i++)
		{
			d.files[i].StartWork();
			current_content = d.files[i].content;
			/*while (d.files[i].content.size() > 0)
			{
				int end_index = d.files[i].content.find('\n');
				if (end_index == -1)
				{
					current_content = d.files[i].content.substr(0, d.files[i].content.size());
				}
				else
				{
					current_content = d.files[i].content.substr(0, end_index + 1);
				}*/

				//current_content += d.files[i].content
				indexing::normalize n(current_content);
				s.process_inputs(n.word, i + 1);
				//d.files[i].content = d.files[i].content.substr(current_content.size(), d.files[i].content.size() - current_content.size());
				console_output += "File index process completed with id: " + (to_string(i + 1)) + "\n";
				if ((i % 5 == 0) || i == d.files.size() - 1)
				{
					cout << console_output;
					console_output = "";
				}
				
		}
		cout << "Now, Removing stopwords from hole index..." << endl;
		s.remove_stop_words(&stop_words);
		cout << "Saving generated index..." << endl;
		string file_output = "";
		file_output = index_output::str_serializer(s.index_table2);
		working_with_file::file index_output_file("Data/AppData/index.txt", 0);
		index_output_file.write(file_output);
		cout << "Indexing process has been completed successfully" << endl;
		
		cout << endl << "Index Operation has been ended";
		string t;
		cin >> t;
		

	}
}
namespace phase1
{
	void count()
	{
		data_to_work d;
		
		cout<<"Please enter the statement that you want to find:"<<endl;
		string statement;
		ws(cin);
		getline(cin, statement);
		
			
		cout<<"Processing..."<<endl;
		
		
		
		searching_tools::search_work search_doer;
		search_doer.input_data = &d.files;
		search_doer.statement_list.push_back(statement);
		search_doer.do_it();
		search_doer.cal_for_each_file();
		cout<<endl<<"Count of this statement usage in default files is: "<<search_doer.result_list.size()<<endl;
		
	}
	void replace()
	{
		//data_to_work d;
		cout<<"Please enter full file path:"<<endl;
		
		string file_path;// = "E:/New Projects/SharifSearch/Data/Source/23/60912";
		ws(cin);
		getline(cin, file_path);
		
		
		cout<<endl<<"Please enter the statement that you want to find:"<<endl;
		string statement;
		ws(cin);
		getline(cin, statement);
		cout<<endl<<"Please enter a term to replace with:"<<endl;
		
		string to;
		ws(cin);
		getline(cin, to);
		
		cout<<endl<<"Processing..."<<endl;
		
		
		vector<file> files;
		file the_only_file(file_path, 0);
		the_only_file.StartWork();
		//cout<<endl<<"Size of file:"<<the_only_file.size<<endl;
		files.push_back(the_only_file);
		
		searching_tools::search_work search_doer;
		search_doer.input_data = &files;
		search_doer.statement_list.push_back(statement);
		search_doer.do_it();
		if (search_doer.result_list.size() > 0)
			cout<<"Found "<<search_doer.result_list.size()<<" cases. Now replacing..."<<endl;
		else
			cout<<"No items found"<<endl;
		
		searching_tools::replace_work replace_doer(statement, to);
		replace_doer.do_replace(&files, search_doer);
		cout<<"Replacing completed.";
	}
	
	void report_index()
	{
		data_to_work d;
		
		cout<<"Please enter the statement that you want to find:"<<endl;
		string statement;
		
		ws(cin);
		getline(cin, statement);
		
			
		cout<<"Processing..."<<endl;
		
		
		
		searching_tools::search_work search_doer;
		search_doer.statement_list.push_back(statement);
		
		search_doer.input_data = &(d.files);
		search_doer.do_it();
		
		search_doer.print_results();
	}
}
