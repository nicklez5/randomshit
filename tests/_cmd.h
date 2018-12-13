#include <iostream>
#include "../header/cmd.h"
#include <vector>
using namespace std;

vector<string> _cmd(int length,char ** chars){
	string xyz = "";
	CMD cmd_test;
	for(int i = 1; i < length;i++){
		xyz += chars[i];
		if(i != length-1){
			xyz += " ";
		}
	}
	cmd_test.set_string(xyz);
	cmd_test.run_output();
	cout << endl;
	vector<string> token_cmd = cmd_test.return_string_vec();
	return token_cmd;
}

