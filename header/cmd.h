#ifndef CMD_H
#define CMD_H
#include <iostream>
#include "connector.h"
#include <string>
#include <vector>

using namespace std;

class CMD : public Connector{
protected:

    //Token String
    string curr_string;

    //Vectors of Token Strings, Vectors of Token Integers
    vector<string> curr_Token_Str;
    vector<int> curr_Token_Num;
    vector<string> pipe_tokens;
    int _passed; //Our success state from command
    bool pipe_found = false;
public:
    //Constructor
    CMD();

    //Assignment Operator
    CMD& operator=(const CMD& RHS);

    //Copy Constructor
    CMD(const CMD& other);

    //Constructor
    CMD(const string temp_token);

    //Destructor
    ~CMD();

    CMD(vector<string> container_tokens);

    //Check whether this command has been passed succesfully
    bool return_pass_state();
    void set_pipe_tokens(vector<string> container_tokens);
    void pipe_is_found();
    //Check if we have found a test command
    bool found_test(vector<string> vect);

    //Check if the file exists
    bool file_exists(const char *fileName);

    void check_file_and_dir(string test_pathz, string test_argz);

    //Set the success state(_passed to fail)
    void set_fail();

    //Set the success state(_passed to success)
    void set_success();

    //Run the test output
    void run_test_output(vector<string> vect);

    bool found_output_direct(string temp);
    bool found_input_direct(string temp);
    bool found_append_direct(string temp);
    void run_pipe_output();

    //Run the Output CMD
    void run_output();

    //Clear Command String
    void clear_cmd();

    //Setter for String
    void set_string(string temp_str);

    string get_string();

    //Return Vector of Token Strings
    vector<string> return_string_vec();

    //Return Vector of Token Numbers
    vector<int> return_token_type_vec();
};

#endif // CMD_H
