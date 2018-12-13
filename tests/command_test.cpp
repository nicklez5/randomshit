#include <iostream>
#include "../header/cmd.h"
//#include "../src/cmd.cpp"
using namespace std;

void test_single_command(){
	CMD* _cmd = new CMD("echo hello world");
	_cmd->run_output();
	
}

