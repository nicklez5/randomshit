#ifndef PROCESS_H
#define PROCESS_H
#include <iostream>
#include <vector>
#include <ctype.h>

#include "_reader.h"
#include <stack>
using namespace std;

class Connector;
class CMD;
class Process{
public:
    //Constructor
    Process();

    //Constructor with a string
    Process(string insert_me);

    //Assignment Operator
    Process& operator=(const Process &RHS);

    //Copy Constructor
    Process(const Process &other);

    //Destructor
    ~Process();

    bool check_correct_num_parentheses(string temp);

    bool check_parentheses(string temp);

    //Insert a Token into interface
    void insert_me(string temp);

    void insert_me2(string temp);

    //Clearing a stack of integers
    void clear_stack_int(stack<int> &_popper);


    //Clearing a stack of strings
    void clear_stack(stack<string> &_popper);


    //Inserting into the Paranthesis by stack but hella ugly
    void new_parenthesis_insert();

    void print_iterator(vector<string> token_boiz, vector<int> token_num_boiz);

    //Removing parenthesis from a string
    vector<string> clean_up_parenthesis(vector<string> clean_me);

    //Running a command with token string as vectors and token integers as vectors
    void run_command(vector<string>token_strz , vector<int> token_typez);

    //Find the maximum amount of parenthesis starting from the first string until one meets a character
    string find_parenthesis_type(string temp);

    //Start
    void start_me();

    bool end_me();

protected:

    //Current command
    string token_temp;
    //Vector for Token Strings, Token Num Strings
    vector<string> process_me;
    vector<int> token_num_order;
    Connector _tokenizer;
    _reader bash_script;
};
#endif
