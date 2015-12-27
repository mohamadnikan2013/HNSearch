#include<iostream>
#include<string>
#include "infrastructure.h"

using namespace std;
//using namespace searching_tools;
using namespace working_with_file;
namespace phase2{
	void index()
	{
		index_output::structured_data s;

		data_to_work d;
		cout << endl << "Processing..." << endl;
		string current_content = "";
		
		working_with_file::file stop_words_file("Data/AppData/stop_words.txt", 0);
		stop_words_file.StartWork();

		string stop_words_content = stop_words_file.content;
		vector<string> stop_words = indexing::normalize::spliter(stop_words_content);
		for (int i = 0; i < 100; i++)
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

				//current_content += d.files[i].content;


				indexing::normalize n(current_content, &stop_words);
				s.process_inputs(n.word, i + 1);
				//d.files[i].content = d.files[i].content.substr(current_content.size(), d.files[i].content.size() - current_content.size());
			
			cout << "File index process completed with id: " << (i + 1) << endl;
		}
		cout << "Now, Removing stopwords from hole index..." << endl;
		s.remove_stop_words(&stop_words);
		cout << "Indexing process has been completed successfully.";
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
