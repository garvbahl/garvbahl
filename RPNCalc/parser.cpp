/*
*   this file contains the implementation of the parser.h class.
*/
//Author : Garv Bahl
//Assignment : CalcYouLater
//Date : 10/16/2024
//Help received : TAs

#include "parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <ciso646>

//name : parseRString
//purpose : parse the RPN string.
//arguments : a reference to the input stream from which we receive the string
//to be parsed.
//returns : the resultant parsed R string.


std::string parseRString(std::istream& input) {
    std::string result;
    char value;
    int braces = 1;
    result = "{ ";
    bool last_space = true;

    while (input.get(value) and braces > 0) {
        if (braces!=0){
            if (std::isspace(value)){
                if (not last_space){
                    result += " ";
                    last_space = true;
                }
            }
            else{
                last_space = false;
                if (braces!=0) {
                    if (value == '}') {
                        result.push_back(value); 
                        braces = braces - 1; 
                }else if(value == '{'){
                    braces++;
                    result.push_back(value);
                }
                else {
                    result.push_back(value); 
                }
            }
        }
        
    }
}
    if (braces!=0 and result.back() != '}') {
        throw std::runtime_error("Unmatched braces in input");
    }
    return result;
}
