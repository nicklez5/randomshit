#include <iostream>
#include "../header/process.h"
#include "../src/process.cpp"
#include <vector>
using namespace std;

int main(int argv,char** argc){
	string xyz;
	for(int i = 1 ;i < argv;i++){
		xyz += argc[i];
		if(i != argv -1){
			xyz += " ";
		}
	}
	Process* bash = new Process();
	bash->insert_me2(xyz);
		
}	
	
