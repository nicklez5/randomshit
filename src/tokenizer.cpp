#include "../header/tokenizer.h"
#include <string>
#include <vector>

using namespace std;

//Constructor
Tokenizer::Tokenizer(){
    _token = "";
}

//Assignment operator
Tokenizer& Tokenizer::operator=(const Tokenizer& RHS){
    if ( this != &RHS){
        _token = RHS._token;
    }
    return *this;
}

//Copy Constructor
Tokenizer::Tokenizer(const Tokenizer& other){
    _token = other._token;
}
//Constructor with a string
Tokenizer::Tokenizer(string temp_token){
    _token = temp_token;
}

//Setter
void Tokenizer::set_token(string temp_token){
    _token = temp_token;
}

//Destructor
Tokenizer::~Tokenizer(){
    _token = "";
}

string Tokenizer::get_token(){
    return _token;
}
