#include <iostream>
#include "../header/_reader.h"
#include "../header/connector.h"
#include "../header/cmd.h"
#include <stack>
using namespace std;

_reader::_reader():Connector(){
    last_pass_state = true;
}

//Assignment Operator
_reader& _reader::operator=(const _reader& RHS){
    if(this != &RHS){
        _reader_Tokens = RHS._reader_Tokens;
        _reader_Tokens_Nums = RHS._reader_Tokens_Nums;
        last_pass_state = RHS.last_pass_state;
    }
    return *this;
}

//Copy constructor
_reader::_reader(const _reader& other){
    _reader_Tokens = other._reader_Tokens;
    _reader_Tokens_Nums = other._reader_Tokens_Nums;
    last_pass_state = other.last_pass_state;
}

//Destructor
_reader::~_reader(){
    last_pass_state = false;
    clear();

}
void _reader::clear(){
    while(_reader_Tokens.size() > 0){
        _reader_Tokens.pop();
    }
    while(_reader_Tokens_Nums.size() > 0){
        _reader_Tokens_Nums.pop();
    }
}
void _reader::set_succeed(){
    last_pass_state = true;
}
void _reader::set_fail(){
    last_pass_state = false;
}
bool _reader::return_current_state(){
    return last_pass_state;
}
//Constructor with vectors
_reader::_reader(vector<string> temp_Tokens,vector<int> temp_Token_Num):Connector(){
    last_pass_state = true;
    set_temp(temp_Tokens,temp_Token_Num);


}

//Setter for vectors
void _reader::set_temp(vector<string> temp_Tokens,vector<int> temp_Token_Num){
    clear();
    for(vector<string>::reverse_iterator i = temp_Tokens.rbegin(); i != temp_Tokens.rend(); ++i){
        _reader_Tokens.push(*i);
    }
    for(vector<int>::reverse_iterator i = temp_Token_Num.rbegin(); i != temp_Token_Num.rend(); ++i){
        _reader_Tokens_Nums.push(*i);
    }
}

void _reader::print_stack(stack<int> c){
    while(!c.empty()){
        cout << c.top() << endl;
        c.pop();
    }
}

//Run the Tokens and executing based on the order
void _reader::run_all(){

    int _counter = 0;

    //First Entry


    //If its only one command such as (echo A & echo B), return
    //if((_reader_Tokens.size() == 1) || _reader_Tokens_Nums.size() == 1)
    // _reader_Tokens_Nums.push(1);
    //}
    //Iterate until there are no more tokens to pop from the stack
    while(_reader_Tokens.size() > 0){
        string first_cmd = _reader_Tokens.top();
        CMD* temp_me = new CMD(first_cmd);
        int op_value;
        //Get the Operator value of the Token and the Token String
        if(!_reader_Tokens_Nums.empty()){
            op_value = _reader_Tokens_Nums.top();
        }
        if((_counter == 0) && (op_value != 4)){
            temp_me->run_output();
            if(temp_me->return_pass_state() != true){
                last_pass_state = false;
            }
            _reader_Tokens.pop();
        }else{
            //Popping the first Token since we are going to not need it anymor

            //Case ;
            if((op_value == 1) || (op_value == 4)){

                if(op_value == 4){
                    vector<string> pipe_tokens;
                    pipe_tokens.push_back(first_cmd);
                    _reader_Tokens.pop();
                    while(_reader_Tokens_Nums.size() > 0){
                        if(_reader_Tokens_Nums.top() == 4){
                            _reader_Tokens_Nums.pop();
                            first_cmd = _reader_Tokens.top();
                            pipe_tokens.push_back(first_cmd);
                            _reader_Tokens.pop();
                        }else{
                            break;
                        }
                    }
                    CMD* pipe_cmd = new CMD(pipe_tokens);
                    pipe_cmd->run_pipe_output();
                    if(pipe_cmd->return_pass_state() != true){
                        last_pass_state = false;
                    }else{
                        last_pass_state = true;
                    }
                    delete pipe_cmd;
                }
                else{
                    temp_me->run_output();
                    if(temp_me->return_pass_state() != true){
                        last_pass_state = false;
                    }else{
                        last_pass_state = true;
                    }
                    _reader_Tokens_Nums.pop();
                    _reader_Tokens.pop();
                }
                //Run output,if it fails, update last pass state
                //temp_me->run_output();
                //Case &&
            }else if(op_value == 2){

                //Only run if the last pass state was successful
                if(last_pass_state == true){
                    temp_me->run_output();

                    //If it was not successful , set last pass state to false
                    if(temp_me->return_pass_state() != true){
                        last_pass_state = false;
                    }
                }
                _reader_Tokens_Nums.pop();
                _reader_Tokens.pop();
                //Case ||
            }else if(op_value == 3){
                //Only run if the last past state was a failure
                if(last_pass_state != true){
                    temp_me->run_output();
                    if(temp_me->return_pass_state() == true){
                        last_pass_state = true;
                    }
                }
                _reader_Tokens_Nums.pop();
                _reader_Tokens.pop();
            }
        }

        //cout << "Current Vector Size: " << _reader_Tokens_Nums.size() << endl;
        //Pop the operators
        delete temp_me;
        _counter++;
    }


}
