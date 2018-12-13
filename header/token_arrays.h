#ifndef TOKEN_ARRAYS_H
#define TOKEN_ARRAYS_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct token_arrayz{
    vector<string> arguments;
    bool output_status = false;
    bool input_status = false;
    bool append_status = false;
};
#endif // TOKEN_ARRAYS_H
