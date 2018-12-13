#include <iostream>
#include <vector>
#include <ctype.h>
#include "../header/connector.h"
#include "../header/_reader.h"
#include <stack>
#include <algorithm>
#include "../header/cmd.h"
#include "../header/process.h"
#include <stdio.h>

//Constructor 
Process::Process(){
    token_temp = "";
}

//Copy Constructor 
Process::Process(string insert_me){
    token_temp = insert_me;
    _tokenizer.parse_me(token_temp);
    process_me = _tokenizer.show_container();
    token_num_order = _tokenizer.show_Token_num();
    bash_script.set_temp(process_me,token_num_order);
}

//Assignment operator
Process& Process::operator=(const Process &RHS){
    if(this != &RHS){
        token_temp = RHS.token_temp;
        process_me = RHS.process_me;
        token_num_order = RHS.token_num_order;
        _tokenizer = RHS._tokenizer;
        bash_script = RHS.bash_script;

    }
    return *this;
}

//Destructor
Process::~Process(){
    token_temp = "";
    process_me.clear();
    token_num_order.clear();
    
}
//Count the number of parenthesis 
bool Process::check_correct_num_parentheses(string temp){
    size_t n = count(temp.begin(),temp.end(),')');
    size_t n2 = count(temp.begin(),temp.end(),'(');
    if(n == n2)
        return true;
    return false;
}
//Check if it has a parenthesiss
bool Process::check_parentheses(string temp){
    bool _found = false;
    string str1("(");
    string str2(")");
    size_t founded = temp.find(str1);
    if(founded != string::npos){
        size_t founded2 = temp.find(str2);
        if(founded2 != string::npos){
            _found = true;
        }
    }
    return _found;
}
//Insertion
void Process::insert_me(string temp){
    token_temp = temp;
    

    //Clear Vectors if not empty
    process_me.clear();
    token_num_order.clear();
    _tokenizer.clear_me();

    //Parse the String
    _tokenizer.parse_me(temp);

    process_me = _tokenizer.show_container();
    token_num_order = _tokenizer.show_Token_num();
    
    bash_script.set_temp(process_me,token_num_order);
    bash_script.run_all();
}
//Parenthesis insertion
void Process::insert_me2(string temp){
    token_temp = temp;

    //Clear the vectors if not empty
    process_me.clear();
    token_num_order.clear();
    _tokenizer.clear_me();

    //Parse the String
    _tokenizer.parse_me(temp);
    process_me = _tokenizer.show_container();
    token_num_order = _tokenizer.show_Token_num();

    //print_iterator(process_me,token_num_order);
    new_parenthesis_insert();
}
//Clearing stack of integers and strings 
void Process::clear_stack_int(stack<int> &_popper){
    while(!_popper.empty()){
        _popper.pop();
    }
}
void Process::clear_stack(stack<string> &_popper){
    while(!_popper.empty()){
        _popper.pop();
    }
}
//Parenthesis insert
void Process::new_parenthesis_insert(){
    //Check if the user has entered the correct number of parenthesis
    if(check_correct_num_parentheses(token_temp) == true){

        string parenthesis_ = find_parenthesis_type(token_temp);

        stack<string> token_stack;
        stack<int> token_num_stack;

        //Read in the Commands
        for(vector<string>::reverse_iterator it = process_me.rbegin(); it != process_me.rend(); it++){
            token_stack.push(*it);
        }
        for(vector<int>::reverse_iterator its = token_num_order.rbegin(); its != token_num_order.rend();its++){
            token_num_stack.push(*its);
        }

        // initial pop
        vector<string> token_stack_vec;
        vector<int> token_num_stack_vec;

        token_stack_vec.push_back(token_stack.top());
        token_stack.pop();

        string right_str(")");
        string big_right_str = "";
        string xyz = token_stack.top();

        //Get the number of parenthesis
        bool big_group_found = false;
        for(int i = 0; i < strlen(parenthesis_.c_str()) ; i++){
            big_right_str += ")";
        }
        //Values that show the current state and whether initial run as becgun
        bool started_initial = false;
        bool current_state;
        int op_value;

        //Keep running until both stacks are empty
        while((!token_stack.empty()) && (!token_num_stack.empty())){
            //found is set to true if a parenthesis is found on the string
            size_t found = xyz.find(right_str);

            //Found is set to false if a big parenthesis is found on the string
            size_t found_big = xyz.find(big_right_str);

            //Until you have found a big parenthesis or small one, keep inputting the strings in to a vector n pop
            while((found == string::npos) && (found_big == string::npos)){

                token_stack_vec.push_back(xyz);
                token_num_stack_vec.push_back(token_num_stack.top());
                token_num_stack.pop();
                token_stack.pop();
                xyz = token_stack.top();

                found = xyz.find(right_str);
                found_big = xyz.find(big_right_str);
            }
            //If the Token stack vector is empty such that its only one string inside the parenthesis
            if(token_num_stack_vec.empty()){
                token_num_stack_vec.push_back(token_num_stack.top());
                token_num_stack.pop();
            }

            //Add the parenthesis string command and pop it from the stack
            token_stack_vec.push_back(xyz);
            token_stack.pop();

            //If there are strings store in the stack, set the xyz value to the top of the stack
            if(!token_stack.empty())
                xyz = token_stack.top();

            //If the big parenthesis is not the same as the parenthesis
            if(big_right_str.compare(right_str) != 0){
                //If you have found a big parenthesis on the string, set the big group to true
                if(found_big != string::npos){
                    big_group_found = true;
                }
            }

            //Clean up the vector such that there are parenthesis on it
            token_stack_vec = clean_up_parenthesis(token_stack_vec);
            bash_script.set_succeed();

            //Initial State
            if(started_initial == false){
                //Run the command and get the next connector value and pop it from the stack
                run_command(token_stack_vec,token_num_stack_vec);
                started_initial = true;
                op_value = token_num_stack.top();
                token_num_stack.pop();
            }else{
                //Case ;
                if(op_value == 1){
                    run_command(token_stack_vec,token_num_stack_vec);
                    op_value = token_num_stack.top();

                    //Case &&
                }else if(op_value == 2){
                    if(current_state == true){
                        run_command(token_stack_vec,token_num_stack_vec);
                    }else{
                        if(big_group_found){
                            big_group_found = false;
                            break;
                        }
                    }

                    //Case ||
                }else if(op_value == 3){
                    if(current_state == false){
                        run_command(token_stack_vec,token_num_stack_vec);
                    }else{
                        if(big_group_found)
                            break;
                    }
                }
                if(!token_num_stack.empty()){
                    op_value = token_num_stack.top();
                    token_num_stack.pop();
                }

            }
            current_state = bash_script.return_current_state();
            //cout << current_state << endl;
            token_stack_vec.clear();
            token_num_stack_vec.clear();
            //cout << "Next string: " << xyz << endl;
        }
    }else{
        perror("Not current num parenthesis");
        return;
    }
}

//Print , to check the vectors 
void Process::print_iterator(vector<string> token_boiz , vector<int> token_num_boiz){
    for(vector<string>::iterator it = token_boiz.begin(); it != token_boiz.end(); it++){
        cout << *it << endl;
    }
    for(vector<int>::iterator its = token_num_boiz.begin(); its != token_num_boiz.end(); its++){
        cout << *its << endl;
    }
}
//Take out the parenthesis from this vector 
vector<string> Process::clean_up_parenthesis(vector<string> clean_me){
    vector<string> new_vec;
    for(vector<string>::iterator its = clean_me.begin(); its != clean_me.end(); its++){
        string xyz = *its;
        xyz.erase(remove(xyz.begin(),xyz.end(),')'),xyz.end());
        xyz.erase(remove(xyz.begin(),xyz.end(),'('),xyz.end());
        new_vec.push_back(xyz);
    }
    return new_vec;
}

//Run the command 
void Process::run_command(vector<string> token_strz, vector<int> token_typez){
    bash_script.set_temp(token_strz,token_typez);
    bash_script.run_all();
}

//Find the parenthesis type 
string Process::find_parenthesis_type(string temp){
    int i = 0;
    string xyz = "";
    //While the char of this string is not a A-Z yet and instead a ( keep adding a ( to the xyz until u meet a A-Z char
    while(isalpha(temp.at(i)) == 0){
        xyz += "(";
        i++;
    }
    return xyz;
}
//Start me
void Process::start_me(){
    string _inputs;
    
    while(1){
        cout << "$ ";
        getline(cin,_inputs);

        //If user has entered a parenthesis, go to different insert
        if(check_parentheses(_inputs) == true){
            insert_me2(_inputs);
        }else{
            insert_me(_inputs);
        }
    }
}
//Check if user has enter exit
bool Process::end_me(){
    if(find(process_me.begin(),process_me.end(),"exit") != process_me.end()){
        return true;
    }
    return false;
}
