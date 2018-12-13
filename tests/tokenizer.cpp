#include <iostream>
#include "../header/connector.h"
#include <vector>
using namespace std;
	
int main(int argv, char** argc){
	string xyz;
	Connector* bash = new Connector();
	for(int i = 1;i < argv;i++){
		xyz += argc[i];
		if(i != argv-1){
			xyz += " ";
		}
	}
	bash->parse_me(xyz);
	vector<string> check_me = bash->show_container();
	vector<int> check_num = bash->show_Token_num();
	//cout << "Printing Token Strings" << endl;
	//cout << "--------------------------------------------" << endl;
	for(vector<string>::iterator it = check_me.begin(); it != check_me.end(); ++it){
		cout << *it << endl;
	}
	//cout << endl << endl;
	//cout << "Printing Token Number Sequences" << endl;
	//cout << "--------------------------------------------" << endl;
	//for(vector<int>::iterator it = check_num.begin();it != check_num.end(); ++it){
	//	cout << *it << endl;
	//}
}
