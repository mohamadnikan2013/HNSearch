//In the name of ALLAH
//
//Va ma ramayta ez ramayt valakenn a ALLAH a rama

#include <iostream>
#include <cstdio>
#include <string>
//#include "stdafx.h"
#include "infrastructure.h"
#include "interface.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace working_with_file;
using namespace std;
string beautiful_find(string statement, string data)
{
	string result = "";
	int start_index = data.find(statement);

	cout << endl << "start_index = " << start_index << endl;
	result = data.substr(start_index, 30);
	return result;
}
int main(int argc, char** argv) {
	//YOU HAVE TO TEST THE CODE IN DEV-C++ BEFORE SENDING TO QUERA
	phase3::test_of_final_query_resolver();
	//phase2::index();
	return 0;
	/*cout << "In the name of God \nWelcome to SharfSearch Project-Phase1 Developed by Mohammad Nikan Ghorbani and Mohammad Haghighat." << endl;
	cout << "Please select one of these options:" << endl << "1.Count of search statement in each file using default data (statement as input)";
	cout << endl << "2.Replace in file (File path, statement, replace term as input)" << endl << "3.Index of search statement using default data (statement as input)";
	cout << endl << endl << "0.Exit";
	cout << endl << endl << "Enter number of operation: ";
	short input;
	cin >> input;

	if (input == 0)

		exit(0);

	if (input == 1)
		phase1::count();

	if (input == 2)
		phase1::replace();

	if (input == 3)
		phase1::report_index();

	cout << endl << "----------------------------------" << endl << endl;
	return 0;*/
}
