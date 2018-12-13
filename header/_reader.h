#ifndef _READER_H
#define _READER_H
#include <iostream>
#include "connector.h"
#include "cmd.h"
#include <stack>
#include <vector>
#include "string"
using namespace std;

class _reader : public Connector{
protected:

    //A stack for token strings, a stack for token types

    stack<string> _reader_Tokens;
    stack<int> _reader_Tokens_Nums;
	
    // Last pass success state 
    bool last_pass_state;
public:
    //Constructor
    _reader();

    //Assignment Operator
    _reader& operator=(const _reader& RHS);

    //Copy constructor
    _reader(const _reader& other);

    //Destructor
    ~_reader();

    //Clear the stack
    void clear();

    void pipe_run();

    //Set the success state to fail/succeed
    void set_succeed();

    void set_fail();

    //Return the success state 
    bool return_current_state();

    //Constructor with vectors
    _reader(vector<string> temp_Tokens,vector<int> temp_Token_Num);


    //Setter for vectors
    void set_temp(vector<string> temp_Tokens,vector<int> temp_Token_Num);

    void print_stack(stack<int> c);

    //Run the Tokens and executing based on the order
    void run_all();


};
#endif // _READER_H
