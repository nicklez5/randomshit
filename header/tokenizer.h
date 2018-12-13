#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//Base
class Tokenizer{
public:
    //Constructor
    Tokenizer();

    //Assignment Operator
    Tokenizer& operator=(const Tokenizer& RHS);

    //Copy Constructor
    Tokenizer(const Tokenizer& other);

    //Constructor
    Tokenizer(string temp_token);

    //Setter of for Tokenizer
    void set_token(string temp_token);

    //Destructor
    ~Tokenizer();

    //Getter
    string get_token();

    virtual void parse_me(string temp_token) = 0;
    virtual vector<string> show_container() = 0;
    virtual vector<int> show_Token_num() = 0;
protected:
    string _token;
};
#endif
