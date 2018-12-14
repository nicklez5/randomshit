#include <iostream>
//#include "tokenizer.h"
#include "../header/connector.h"
#include <vector>
#include "../header/cmd.h"
#include "../header/_reader.h"
#include "../header/process.h"
#include <string>	
using namespace std;
void testing_tokenizer();
void test_cmd();
void test_process();
void test_pipe();
int main(int argc,char* argv[])
{
	//testing_tokenizer();
	//test_cmd();
	test_process();
	//test_pipe();
	return 0;
	
}
void test_pipe(){
	Connector* bash = new Connector();
	string copy_me = "cat < existingInputFile | tr A-Z a-z | tee newOutputFile1 | tr a- A-Z > newOutputFile1";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	
	cout << "Printing Token Strings" << endl << endl;
	for(vector<string>::iterator it = check_me.begin(); it != check_me.end(); it++){
		cout << *it << endl;
	}
	cout << "Printing Token Types" << endl << endl;
	for(vector<int>::iterator its = check_num.begin(); its != check_num.end(); its++){
		cout << *its << endl;
	}
	
}
//Test the Process
void test_process(){
	Process start_new;
	start_new.start_me();
	//string _inputs;
	//string _exit("exit;");	
	//cout << "Enter exit to quit" << endl;
	//while(_inputs.compare(_exit) != 0){
	//while(1){
		//cout << "$ ";
		//getline(cin,_inputs);
		//start_new.insert_me(_inputs);
	//}
	
	
			
			
}
//Test the Command
void test_cmd(){
	CMD* _cmd = new CMD("echo hello");
	_cmd->run_output();
}
//Test the Tokenizer
void testing_tokenizer(){

	Connector* bash = new Connector();
	//std::string copy_me = "ls # -lR;";

        std::string copy_me = "lss -l; echo hello && mkdir test || echo world && git status";
        bash->parse_me(copy_me);

        std::vector<std::string> check_me = bash->show_container();
        std::vector<int> check_num = bash->show_Token_num();

        //Test for printing strings
        std::cout << "Printing Token Strings" << endl;
        std::cout << "---------------------------------" << endl;
        for(std::vector<std::string>::iterator it = check_me.begin(); it != check_me.end(); ++it){
        	std::cout << *it << endl;
        }

        std::cout << endl << endl;                                             
	//Test for Printing Token Number types                                                              
	std::cout << "Printing Token Number Sequences" << endl;
        std::cout << "------------------------------------" << endl;
        for(std::vector<int>::iterator it = check_num.begin(); it != check_num.end(); ++it){
        	std::cout << *it << endl;
        }
	
	_reader* mega_man = new _reader(check_me,check_num);
	mega_man->run_all();
}
	
