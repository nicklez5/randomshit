#include "../header/cmd.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "../header/connector.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
//#include "../header/token_arrays.h"
using namespace std;

//Constructor
CMD::CMD(): Connector(){
    curr_string = "";
    curr_Token_Str = Token_Str;
    Token_Num = curr_Token_Num;
    _passed = 1;
}

//Assignment operator
CMD& CMD::operator=(const CMD& RHS){
    if(this != &RHS){
        curr_string = RHS.curr_string;
        curr_Token_Str = RHS.curr_Token_Str;
        curr_Token_Num = RHS.curr_Token_Num;
        _passed = RHS._passed;
        pipe_tokens = RHS.pipe_tokens;
        pipe_found = RHS.pipe_found;
    }
    return *this;
}
//Copy Constructor
CMD::CMD(const CMD& other):Connector(){
    curr_string = other.curr_string;
    curr_Token_Str = other.curr_Token_Str;
    curr_Token_Num = other.curr_Token_Num;
    _passed = other._passed;
    pipe_tokens = other.pipe_tokens;
    pipe_found = other.pipe_found;
}
CMD::CMD(vector<string> container_tokens): Connector(){
    pipe_tokens = container_tokens;
    _passed = 1;
}
//String Constructor
CMD::CMD(const string temp_token):Connector(){
    curr_string = temp_token;
    _passed = 1;
}

//Destructor
CMD::~CMD(){
    curr_string = "";
    curr_Token_Str.clear();
    curr_Token_Num.clear();
    _passed = 1;
    pipe_tokens.clear();
    pipe_found = false;
}
void CMD::set_pipe_tokens(vector<string> container_tokens){
    pipe_tokens = container_tokens;
}
//Return success state
bool CMD::return_pass_state(){
    if(_passed == 1){
        return true;
    }else
        return false;
}

//Find a test from the vectors or [
bool CMD::found_test(vector<string> vect){
    if(find(vect.begin(),vect.end(),"test") != vect.end()){
        return true;
    }
    if(find(vect.begin(),vect.end(),"[") != vect.end()){
        return true;
    }
    return false;
}
//Check if the path of the filename can be opened
bool CMD::file_exists(const char *fileName){
    ifstream infile(fileName);
    return infile.good();
}
//Check if the path is a file or directory
void CMD::check_file_and_dir(string test_pathz,string test_argz){
    struct stat info;

    //If the path is a file, set to true
    if(file_exists(test_pathz.c_str())){
        cout << "(True)" << endl;
        set_success();
    }else{
        //If the path is not a directory , set to false
        if( stat( test_pathz.c_str(), &info) != 0){
            cout << "(False)" << endl;
            set_fail();
            //If the path is a directory, set to true
        }else if(info.st_mode & S_IFDIR){
            cout << "(True)" << endl;
            set_success();
        }
        else{
            cout << "(False)" << endl;
            set_fail();
        }
    }
}
void CMD::set_fail(){
    _passed = 0;
}
void CMD::set_success(){
    _passed = 1;
}
//Running test output
void CMD::run_test_output(vector<string> vect){

    string test_arg = "";
    string test_path = "";
    // 0    1  2         0  1  2
    //test -e path ..... [ -e path
    if(vect.size() >= 3){
        test_path = vect.at(2);
        test_arg = vect.at(1);
    }else{
        test_path = vect.at(1);
        test_arg = "-e";
    }
    string token_1("-e");
    string token_2("-f");
    string token_3("-d");
    struct stat sb;

    //Checking if the file exists
    if(test_arg.compare(token_1) == 0){
        check_file_and_dir(test_path, test_arg);

        //Check if file/dir exists along with checking that its a regular file
    }else if(test_arg.compare(token_2) == 0){
        check_file_and_dir(test_path, test_arg);
        if( stat( test_path.c_str(), & sb) != -1){
            //If its a regular file, set the success state as true
            if(S_ISREG( sb.st_mode ) != 0){
                cout << "(True)" << endl;
                set_success();
                //IF its not a regular file, set the success state as false
            }else{
                cout << "(False)" << endl;
                set_fail();
            }}else
            perror("stat");
        //Check if file/dir exists along with checking that its a directory
    }else{

        check_file_and_dir(test_path, test_arg);

        if( stat(test_path.c_str(), & sb) != -1){
            //If its a directory, set the success state as true
            if(S_ISDIR( sb.st_mode ) != 0){
                cout << "(True)" << endl;
                set_success();
                //If its not a directory ,set the success state as false
            }else{
                cout << "(False)" << endl;
                set_fail();
            }}else
            perror("stat");
    }
}
bool CMD::found_output_direct(string temp){
    string find_me = ">";
    if(temp.compare(find_me) == 0)
        return true;
    return false;
}
bool CMD::found_input_direct(string temp){
    string find_me = "<";
    if(temp.compare(find_me) == 0)
        return true;
    return false;
}
bool CMD::found_append_direct(string temp){
    string find_me = ">>";
    if(temp.compare(find_me) == 0)
        return true;
    return false;
}
void CMD::pipe_is_found(){
    pipe_found = true;
}
void CMD::run_pipe_output(){
    vector<token_arrays*> vec_list_arg;
    for(vector<string>::iterator itz = pipe_tokens.begin(); itz != pipe_tokens.end(); itz++){
        token_arrays* List_arg = new token_arrays();
        bool output_direct = false;
        bool input_direct = false;
        bool append_direct = false;

        vector<string> temp_container;
        string random_str = *itz;
        char *xyz = strdup(random_str.c_str());
        char *pch;
        pch = strtok(xyz," ");

        while(pch != NULL){
            temp_container.push_back(pch);
            pch = strtok(NULL," ");
        }

        curr_Token_Str = temp_container;
        char* _args[temp_container.size() + 1];
        int word_count = 0;
        for(vector<string>::iterator it = temp_container.begin(); it != temp_container.end(); it++){
            string kfc = *it;
            if(found_append_direct(kfc)){
                append_direct = true;
            }else if(found_input_direct(kfc)){
                input_direct = true;
            }else if(found_output_direct(kfc)){
                output_direct = true;
            }
            _args[word_count] = (char*)kfc.c_str();
            word_count++;

        }
        _args[temp_container.size()] = NULL;
        //List arg is a vector that holds strings:
        //Current vector: "ls" "-l"
        for(int i = 0 ; i < word_count ; i++){
            string cStr(_args[i]);
            List_arg->arguments.push_back(cStr);
        }
        if(input_direct){
            List_arg->input_status = true;
        }else if(output_direct){
            List_arg->output_status = true;
        }else if(append_direct){
            List_arg->append_status = true;
        }
        vec_list_arg.push_back(List_arg);
    }
    _passed = 1;
    pid_t pid = fork();

    //Pipe
    int _p[2];
    pipe(_p);

    //int _input_counter = 0;
    //Do the last command as later.
    for(unsigned int xyz = 0; xyz < vec_list_arg.size() -1; xyz++){
        //pid = fork();

        token_arrays* cmd_1 = vec_list_arg.at(xyz);
        token_arrays* cmd_2 = vec_list_arg.at(xyz+1);

        char* new_args[cmd_1->arguments.size()+1];
        char* new_args1[cmd_2->arguments.size()+1];

        int random_index = 0;


        //Command 1
        for(vector<string>::iterator its = cmd_1->arguments.begin(); its != cmd_1->arguments.end(); its++){
            string temp_str = *its;
            //cout << "Argument 1 cmd: " << temp_str << endl;
            new_args[random_index] = (char*)temp_str.c_str();
            random_index++;
        }

        //Command 2
        new_args[cmd_1->arguments.size()] = NULL;
        random_index = 0;

        for(vector<string>::iterator itz = cmd_2->arguments.begin(); itz != cmd_2->arguments.end(); itz++){
            string temp_strs = *itz;
            //cout << "Argument 2 cmd: " << temp_strs << endl;
            new_args1[random_index] = (char*)temp_strs.c_str();
            random_index++;
        }
        new_args1[cmd_2->arguments.size()] = NULL;

        //Child process
        if(pid == 0){

            //Redirecting stdout to a file
            //cat > main.cpp
            if(cmd_1->output_status){

                const char* destPtr = (const char*)new_args[cmd_1->arguments.size() -1];
                int file_handle = open(destPtr,O_WRONLY,O_CREAT);

                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }

                close(1);
                dup(file_handle);

                close(0);
                dup(_p[0]);
                close(_p[1]);

                char* new_array[cmd_1->arguments.size()-1];
                int random_index = 0;
                while(1){
                    string char_output = ">";
                    if(strcmp(cmd_1->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_1->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
                new_array[cmd_1->arguments.size()-2] = NULL;

                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

                //cat < ExistingFile ; READING
            }else if(cmd_1->input_status){

                const char* destPtr = (const char*)new_args[cmd_1->arguments.size()-1];
                //cout << "File name: " << destPtr << endl;
                //Check if the file has been opened successfully
                int file_handle = open(destPtr,O_RDONLY);
                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }

                //Close the stdin
		int dup_out = dup(1);
		close(1);
		dup(_p[1]);
		close(_p[0]);
			
                //close(0);
                //dup(file_handle);

                //close(1);
                //dup(_p[0]);
                //close(_p[1]);
                //close(_p[0]);
                //dup(dup_out);


                //Replace the stdout with the pipe write

                char* new_array[cmd_1->arguments.size()];
                int random_index = 0;
                while(1){
                    string char_output = "<";
                    if(strcmp(cmd_1->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_1->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
		new_array[cmd_1->arguments.size()-2] = (char*)destPtr;
                new_array[cmd_1->arguments.size()-1] = NULL;

                //Close the pipe read end


                //Executing which will be printed out to pipe write end.
                execvp(new_array[0],new_array);

            }else if(cmd_1->append_status){
                const char* destPtr = (const char*)new_args[cmd_1->arguments.size()-1];
                int file_handle = open(destPtr,O_WRONLY,O_APPEND,O_CREAT);
                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }
                close(1);
                dup(file_handle);
                close(0);
                dup(_p[0]);
                close(_p[1]);

                char* new_array[cmd_1->arguments.size()-1];
                int random_index = 0;
                while(1){
                    string char_output = "<<";
                    if(strcmp(cmd_1->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_1->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
                new_array[cmd_1->arguments.size()-2] = NULL;


                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

            }else{
                //Close the std out
                close(1);

                //Replace the std out with the write end of pipe
                dup(_p[1]);

                //Close the read end of the pipe
                close(_p[0]);

                //Execute will go into write end of pipe
                execvp(new_args[0],new_args);
                _passed = 0;
                perror("error executing");

            }


        }

        //Parent process
        else{

            //Case > - Redirecting stdout to file name
            if(cmd_2->output_status){

                const char* destPtr2 = (const char*)new_args1[cmd_2->arguments.size()-1];
                int file_handle = open(destPtr2,O_WRONLY,O_CREAT);

                if(file_handle < 0 ){
                    perror("Error handling the file");
                    exit(0);
                }

                close(1);
                dup(file_handle);
                close(0);
                dup(_p[0]);
                close(_p[1]);

                char* new_array[cmd_2->arguments.size()-1];
                int random_index = 0;
                while(1){
                    string char_output = ">";
                    if(strcmp(cmd_2->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_2->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
                new_array[cmd_2->arguments.size()-2] = NULL;

                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

                //Case <
                //Accepting input from a file
            }else if(cmd_2->input_status){

                const char* destPtr2 = (const char*)new_args1[cmd_2->arguments.size()-1];
                int file_handle = open(destPtr2,O_RDONLY);

                if(file_handle < 0 ){
                    perror("Error handling the file");
                    exit(0);
                }
                close(0);
                dup(file_handle);

                int dupout = dup(1);
                close(1);

                dup(_p[1]);
                close(_p[1]);
                close(_p[0]);
                dup(dupout);

                char* new_array[cmd_2->arguments.size()-1];
                int random_index = 0;
                while(1){
                    string char_output = ">";
                    if(strcmp(cmd_2->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_2->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
                new_array[cmd_2->arguments.size()-2] = NULL;

                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

                //Redirecting the Stdout to a file and appends on the file as well
            }else if(cmd_2->append_status){
                const char* destPtr2 = (const char*)new_args1[cmd_2->arguments.size()-1];
                int file_handle = open(destPtr2,O_WRONLY,O_APPEND,O_CREAT);

                if(file_handle < 0){
                    perror("Error handling the file");
                    exit(0);
                }
                close(1);
                dup(file_handle);
                close(0);
                dup(_p[0]);
                close(_p[1]);

                char* new_array[cmd_2->arguments.size()-1];
                int random_index = 0;
                while(1){
                    string char_output = ">";
                    if(strcmp(cmd_2->arguments.at(random_index).c_str(),char_output.c_str()) != 0){
                        string str = cmd_2->arguments.at(random_index);
                        char* chr = const_cast<char*>(str.c_str());
                        new_array[random_index] = chr;
                        random_index++;
                    }else{
                        break;
                    }
                }
                new_array[cmd_2->arguments.size()-2] = NULL;

                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");
            }else{

                //Closing the std in
                close(0);

                //Replacing stdin fd with READING pipe
                dup(_p[0]);

                //Make writing file available

                //cout << "I was here " << endl;
                //Close the writing reference
                close(_p[1]);

                //Executing it into stdout of the input of stdin
                execvp(new_args1[0],new_args1);
                _passed = 0;
                perror("exec");

            }
            int returnStatus;
            waitpid(pid,&returnStatus,0);
            close(_p[0]);
            close(_p[1]);

        }

    }

    //freeing all the token arrays we created
    for(unsigned int j = 0 ; j < vec_list_arg.size();j++){
        delete vec_list_arg.at(j);
    }
}
//Need to implement redirect and indirect
void CMD::run_output(){

    //Get the current string and seperate it with delimiters of whitespaces, insert into vector
    vector<string> temp_container;
    bool append_direct = false;
    bool input_direct = false;
    bool output_direct = false;
    char *xyz = strdup(curr_string.c_str());
    char *pch;
    pch = strtok(xyz," ");

    //Break down the tokens with delimiters of whitespaces
    while (pch != NULL){
        string break_cmt = "#";
        string cmt_compare(pch);
        size_t found = cmt_compare.find(break_cmt);

        //IF you have found a comment, break
        if(found != string::npos){
            break;
        }

        temp_container.push_back(pch);
        pch = strtok(NULL," ");
    }
    curr_Token_Str = temp_container;

    //If the vector found a test go to run test output
    if(found_test(temp_container)){
        run_test_output(temp_container);

        free(xyz);
        return;
    }

    //Emptying out the white spaces in the string and placing the tokens into a char array
    char* _args[temp_container.size() + 1];
    int word_count = 0;

    //Set the string as a char*
    for(vector<string>::iterator it = temp_container.begin(); it != temp_container.end(); it++){
        string kfc = *it;
        if(found_append_direct(kfc)){
            append_direct = true;
        }else if(found_output_direct(kfc)){
            output_direct = true;
        }else if(found_input_direct(kfc)){
            input_direct = true;
        }
        _args[word_count] = (char*)kfc.c_str();
        word_count++;

    }
    _passed = 1;

    //Executing the command found in args
    _args[temp_container.size()] = NULL;

    int _pipe[2];
    pipe(_pipe);
    pid_t pid = fork();
    string exit_str = string(_args[0]);
    //Child
    int _status;

    // Child Process
    if( pid == 0){

        //If you have not made it here passed execvn , you failed
        //execvp(_args[0],_args);
        if(exit_str.compare("exit") == 0){
            int status_;
            kill(pid,SIGKILL);
            perror("exit");
            exit(0);
        }else{

            //Case 1:
            //Cat > catfish.cpp
            if(output_direct){
                string file_str = temp_container.back();
                const char* destPtr = file_str.c_str();
                int file_handle = open(destPtr,O_WRONLY,O_CREAT);
                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }
                //Duplicating the std out incase we are bored of reading it
                //int dupout = dup(1);

                //Closing the std out
                close(1);

                //Replacing the std out with the file handle
                dup(file_handle);

                //Accounting for the commands only before the > symbol
                char* new_array[temp_container.size()-1];
                int random_index = 0;
                int x = 0;
                while(1){
                    string char_output = ">";
                    if(strcmp(_args[x],char_output.c_str()) != 0){
                        new_array[random_index] = _args[x];
                        random_index++;
                    }else{
                        break;
                    }
                    x++;
                }
                new_array[temp_container.size()-2] = NULL;

                //We are now playing with the file and every input to the file will be outputted to the file
                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");
            }
            //Case 2
            //Cat < catfish.cpp
            else if(input_direct){

                //Open the file
                const char* destPtr = (const char*)_args[temp_container.size()-1];
                cout << "File name: " << _args[temp_container.size()-1] << endl;
                //Get the file descriptor
                int file_handle = open(destPtr,O_RDONLY);

                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }
                //Store the stdin into dupin
                int dupin = dup(0);

                //Close the stdin
                close(0);

                //Replace the standard in into this
                dup(file_handle);

                //Get the command erasing the <
                char* new_array[temp_container.size()-1];
                int random_index = 0;
                int x = 0;

                while(1){
                    string char_input = "<";
                    if(strcmp(_args[x],char_input.c_str()) != 0){
                        new_array[random_index] = _args[x];
                        random_index++;
                    }else{
                        break;
                    }
                    x++;
                }
                new_array[temp_container.size() - 2] = NULL;

                //dup(_pipe[0]);

                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

                //Case 3
                //Cat >> catfish.cpp
            }else if(append_direct){

                //Get the destination pointer
                const char* destPtr = (const char*)_args[temp_container.size()-1];

                //open the handle
                int file_handle = open(destPtr,O_APPEND,O_WRONLY,O_CREAT);
                if(file_handle < 0){
                    perror("File not found");
                    exit(0);
                }

                int dupout = dup(1);
                close(1);
                dup(file_handle);
                char* new_array[temp_container.size()-1];

                int random_index = 0;
                int x = 0;
                while(1){
                    string char_output = ">>";
                    if(strcmp(_args[x],char_output.c_str()) != 0){
                        new_array[random_index] = _args[x];
                        random_index++;
                    }else{
                        break;
                    }
                    x++;
                }
                new_array[temp_container.size() - 2] = NULL;
                execvp(new_array[0],new_array);
                _passed = 0;
                perror("exec");

            }else{
                execvp(_args[0],_args);
                _passed = 0;
                perror("exec");
            }
        }}else{

        int returnStatus;
        waitpid(pid,&returnStatus,0);

    }


    //Free up the dynamic memory
    free(xyz);
}

//Clear the string
void CMD::clear_cmd(){
    curr_string = "";
}

//Set the string to temp str
void CMD::set_string(string temp_str){
    curr_string = temp_str;
}

//Get the string for this command
string CMD::get_string(){
    return curr_string;
}

//Return the string vector
vector<string> CMD::return_string_vec(){
    return curr_Token_Str;
}
