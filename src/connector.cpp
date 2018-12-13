#include "../header/connector.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../header/tokenizer.h"

using namespace std;
//Constructorr
Connector::Connector():Tokenizer(){
    full_string = _token;
}
//Assignment operator
Connector& Connector::operator=(const Connector& RHS){
    if(this != &RHS){
        full_string = RHS.full_string;
        Token_Str = RHS.Token_Str;
        Token_Num = RHS.Token_Num;
    }
    return *this;
}
//Copy constructor
Connector::Connector(const Connector& other):Tokenizer(){
    full_string = other.full_string;
    Token_Str = other.Token_Str;
    Token_Num = other.Token_Num;
}
//Destructor
Connector::~Connector(){
    full_string = "";
    Token_Str.clear();
    Token_Num.clear();
}
//Trim out the white spaces 
string Connector::trim(const string& str){
    size_t first = str.find_first_not_of(' ');
    if(string::npos == first){
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first,(last-first+1));
}
//Parse in the string 
void Connector::parse_me(string temp_token){
    char *xyz = strdup(temp_token.c_str());
    char *pch;
    pch = strtok(xyz,";&&||");

    //Adds Tokens to Vector
    while (pch != NULL){
        //cout << pch << endl;
        Token_Str.push_back(trim(pch));
        pch = strtok(NULL,";&&||");
    }

    //Adds in Token Number Sequence
    for(int i = 0; i < strlen(temp_token.c_str()); i++){

        //Case ;
        if (temp_token[i] == ';'){
            if(i+1 != strlen(temp_token.c_str()))
                Token_Num.push_back(1);

            //Case &&
        }else if (i+1 != strlen(temp_token.c_str()) && (temp_token[i] == '&' && temp_token[i+1] == '&')){
            Token_Num.push_back(2);

            //Case ||
        }else if (i+1 != strlen(temp_token.c_str()) && (temp_token[i] == '|' && temp_token[i+1] == '|')){
            Token_Num.push_back(3);

            //If it doesnt have any thing and it is the last command. execute
        }else if (i+1 != strlen(temp_token.c_str()) && (temp_token[i] == '|' && temp_token[i+1] == ' ')){
            Token_Num.push_back(4);
        }
    }
    if(Token_Num.empty()){
        Token_Num.push_back(1);
    }
    free(xyz);
}

//Clear the Vectors 
void Connector::clear_me(){
    Token_Num.clear();
    Token_Str.clear();
}

//Return the vector containing token numbers 
vector<int> Connector::show_Token_num(){
    return Token_Num;
}
//Return the vector containing strings 
vector<string> Connector::show_container(){
    return Token_Str;
}
