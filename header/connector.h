#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "tokenizer.h"
using namespace std;

class Connector : public Tokenizer{
protected:
    //Vector for Token Types, Token Strings
    //Full String is the input the user has set
    string full_string;
    vector<string> Token_Str;
    vector<int> Token_Num;
public:
    //Constructor
    Connector();

    //Assignment Operator
    Connector& operator=(const Connector& RHS);

    //Copy Constructor
    Connector(const Connector& other);

    //Destructor
    ~Connector();

    //Trim the String from White Spaces
    string trim(const string& str);

    //Parse the string and read in to the Vector of Token Strings and Token Types
    void parse_me(string temp_token);

    //Clear the vectors
    void clear_me();

    //Return Vector of Token Types
    vector<int> show_Token_num();

    //Return Vector of Token Strings
    vector<string> show_container();
};
#endif
