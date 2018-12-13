#include <iostream>
#include "../header/connector.h"
#include <vector>
#include <sstream>
#include "../header/cmd.h"
#include "../header/_reader.h"
#include "../header/process.h"
#include "../header/tokenizer.h"
#include "gtest/gtest.h"
#include "../header/cmd.h"
using namespace std;


//Test for Command
TEST(CMDTest, HelloWorld){
	CMD* _cmd = new CMD("echo hello world;");
	_cmd->run_output();
	vector<string> test_tokens = _cmd->return_string_vec();
	EXPECT_EQ("echo",test_tokens.at(0));
	EXPECT_EQ("hello",test_tokens.at(1));
	EXPECT_EQ("world;",test_tokens.at(2));
	delete _cmd;
	
}
//Test for Execute with no ; at the end
TEST(Auto_execute, helloworld){
	Connector* bash = new Connector();
	string copy_me = "echo hello world";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	EXPECT_EQ("echo hello world", check_me.at(0));
	_reader* mega_man = new _reader(check_me,check_num);
	mega_man->run_all();
	delete bash;
	delete mega_man;
}	
//Test For commenting
TEST(CommentTest, Comment){
	Connector* bash = new Connector();
	string copy_me = "ls # -lR;";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	EXPECT_EQ("ls # -lR",check_me.at(0));
	//EXPECT_EQ(NULL,check_me.at(1));
	_reader* mega_man = new _reader(check_me,check_num);
	mega_man->run_all();
	delete bash;
	delete mega_man;
}
//Test for Multiple Commands
TEST(MultipleCommands, Tokenizer){
	Connector* bash = new Connector();
	string copy_me = "ls -l; echo hello && mkdir test || echo world && git status";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	EXPECT_EQ("ls -l",check_me.at(0));
	EXPECT_EQ("echo hello",check_me.at(1));
	EXPECT_EQ("mkdir test",check_me.at(2));
	EXPECT_EQ("echo world",check_me.at(3));
	EXPECT_EQ("git status",check_me.at(4));
	_reader* mega_man = new _reader(check_me,check_num);
	mega_man->run_all();
	delete bash;
	delete mega_man;
}
//Testing for Exit Command
TEST(FileDirectory, File_Dir){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "test -e header";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	//EXPECT_EQ("test -e ../header",check_me
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	//assert(oss && oss.str() == "(True)\n";
	EXPECT_EQ("test -e header\n(True)\n",oss.str());
	cout << oss.str();
	oss.str("");
	delete bash;
	delete mega_man;
}
TEST(FileDirectory, RegularFile){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "test -f README.md";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	EXPECT_EQ("test -f README.md\n(True)\n(True)\n",oss.str());
	cout << oss.str();
	oss.str("");
	delete bash;
	delete mega_man;
}
TEST(FileDirectory, Directory_Test){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "test -d tests";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	EXPECT_EQ("test -d tests\n(True)\n(True)\n",oss.str());
	cout << oss.str();
	oss.str("");
	delete mega_man;
	delete bash;
}
TEST(PartB_File, File){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "[ -e header ]";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	EXPECT_EQ("[ -e header ]\n(True)\n",oss.str());
	cout << oss.str();
	oss.str("");
	delete bash;
	delete mega_man;
}
TEST(PartB_File, RegularFile){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "[ -f README.md ]";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	EXPECT_EQ("[ -f README.md ]\n(True)\n(True)\n",oss.str());
	cout << oss.str(); 
	oss.str("");
	delete bash;
	delete mega_man;
}
TEST(PartB_File, Directory){
	ostringstream oss;
	streambuf* p_cout_streambuf = cout.rdbuf();
	cout.rdbuf(oss.rdbuf());
	Connector* bash = new Connector();
	string copy_me = "[ -d tests ]";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	_reader* mega_man = new _reader(check_me,check_num);
	cout << copy_me << endl;
	mega_man->run_all();
	cout.rdbuf(p_cout_streambuf);
	EXPECT_EQ("[ -d tests ]\n(True)\n(True)\n",oss.str());
	cout << oss.str();
	oss.str("");
	delete mega_man;
	delete bash;
}
//Could not take the output therefore had to reimplement
TEST(ParenthesisTest,CaseA){
	Process* bash = new Process();
	string copy_me = "(echo A && echo B) || (echo C && echo D)";
	cout << copy_me << endl;
	bash->insert_me2(copy_me);
	delete bash;
}
TEST(Parenthesis_SubTest,CaseB){
	Process* bash0 = new Process();
	string copy_me0 = "((echo A && echo B) && (echo C && echo D)) || ((echo E && echo F) && (echo G && echo H))";
	cout << copy_me0 << endl;
	bash0->insert_me2(copy_me0);
	delete bash0;
}
TEST(Parenthesis_SubTest,CaseC){
	Process* bash1 = new Process();
	string copy_me1 = "((echo A && echo B) || (echo C && echo D)) && ((echo E && echo F) && (echo G && echo H))";
	cout << copy_me1 << endl;
	bash1->insert_me2(copy_me1);
	delete bash1;
}



TEST(ExitCommand, Exit){
	Connector* bash = new Connector();
	string copy_me = "echo hello && exit";
	bash->parse_me(copy_me);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	EXPECT_EQ("echo hello", check_me.at(0));
	EXPECT_EQ("exit",check_me.at(1));
	_reader* mega_man = new _reader(check_me,check_num);
	mega_man->run_all();
}
int main(int argc,char **argv){
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}	
