//This file contains the implementation for the RPNCalc class
//Author : Garv Bahl
//Assignment : CalcYouLater
//Date : 10/23/2024
//Help received : TAs

// These includes are necessary for got_int( )
#include <string>
#include <cstdio>
#include <cstring>


#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "DatumStack.h"
#include "RPNCalc.h"
#include "parser.h"
#include "fstream"
#include <ciso646>

using namespace std;

/*
 * Name: got_int 
 * Purpose: determines if a string contains an integer and loads said
 *           integer into an integer variable whose address has been
 *           passed to this function
 * Parameters: a string to check if it contains an integer as well as 
 *              a pointer to an integer to load in the event an 
 *              integer can be parsed from said string
 * Returns: a boolean where true indicates an integer was successfully
 *           parsed from the provided string (and therefore the
 *           addressed integer has been loaded) and false indicates 
 *           an integer could not be read 
 * Effects: the integer pointed to by the passed pointer will be updated
 *           with the integer parsed from the string in the event true
 *           is returned (otherwise nothing happens)
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
bool got_int(string s, int *resultp) {
    /* Holds the first non-whitespace character after the integer */
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}



RPNCalc::RPNCalc(){}

//name : run()
//purpose : call the processCommand function and use the cin stream as input.
//arguments : none
//returns : n/a
//effects : n/a
void RPNCalc::run(){
    processCommand(cin);
}

//name : exec()
//purpose : execute the operations stored within the rstring
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
// if the top element of the stack is not an rstring an error is thrown. 
void RPNCalc::exec(){
    try{
        if (stack.isEmpty()){
        std::cerr << "Error: empty_stack" 
        << std::endl;
        return;
        }
        Datum top = stack.top();
        stack.pop();
        if (not top.isRString()){
            std::cerr<<"Error: cannot execute non rstring\n";
            return;
        }
        std::string rstring = top.getRString();
        int i = 0;
        if (int(rstring.size() == 3)){
            while (i < int(rstring.size())) {
                if (rstring[i] == '{' or rstring[i] == '}' ) {
                    rstring.erase(i,1);
                    i++;
                } else {
                    i++;
                }
            }
            std::istringstream commands(rstring);
            processCommand(commands);
        }else{
            std::string temp = rstring.substr(2,rstring.size()-4);
            std::istringstream commands(temp);
            processCommand(commands);
        }
        
    } catch (const std::runtime_error& e){
        std::cerr << "Error: \n";
        return;
    }
    
}

//name : file()
//purpose : execute the operations stored within the file in the rstring.
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
// if the top element of the stack is not an rstring an error is thrown.
// if the file cannot be opened an error message is thrown.
void RPNCalc::file(){
    if (stack.isEmpty()){
        std::cerr << "Error: empty_stack" 
        << std::endl;
        return;
    }
    Datum top = stack.top();
    stack.pop();
    if (not top.isRString()){
        std::cerr<<"Error: file operand not rstring \n";
        return;
    }
    std::string rstring = top.getRString();
    int i = 0;
     if (int(rstring.size() == 3)){
            while (i < int(rstring.size())) {
                if (rstring[i] == '{' or rstring[i] == '}' ) {
                    rstring.erase(i,1);
                    i++;
                } else {
                    i++;
                }
            }
            std::string filename = rstring;
            std::ifstream fileStream(filename);
            if(not fileStream){
        std::cerr<< "Unable to read " << filename << std::endl;
        return;
    }
    try{
        processCommand(fileStream);
    }catch(const std::runtime_error& e){
        std::cerr<< "Error: empty_stack" <<std::endl;
        return;
    }
     }
     else{
        std::string filename = rstring.substr(2,rstring.size()-4);
        std::ifstream fileStream(filename);
        if(not fileStream){
        std::cerr<< "Unable to read " << filename << std::endl;
        return;
    }
    try{
        processCommand(fileStream);
    }catch(const std::runtime_error& e){
        std::cerr<< "Error: empty_stack" <<std::endl;
        return;
    }
    }
}

//name : If()
//purpose : complete the requirement of the If function
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
// if the test condition of the stack is not a bool an error is thrown. 
// if the true and false case are not rstrings an error is thrown.
void RPNCalc::If(){
    if (stack.size() < 3) {
        std::cerr << "Error: empty_stack" << std::endl;
        return;
    }
    Datum falseCase = stack.top(); 
    stack.pop();
    Datum trueCase = stack.top(); 
    stack.pop();
    Datum testCondition = stack.top(); 
    stack.pop();

    if (not testCondition.isBool()) {
        std::cerr << "Error: expected boolean in if test\n";
        return;
    }
    if (not trueCase.isRString() or not falseCase.isRString()) {
        std::cerr << "Error: expected rstring in if branch\n";
        return;
    }
    std::string rstring;
    int i = 0;
   
    if(testCondition.getBool()){
        rstring = trueCase.getRString();
    }
    else{
        rstring = falseCase.getRString();
    }

    if (int(rstring.size() == 3)){
            while (i < int(rstring.size())) {
                if (rstring[i] == '{' or rstring[i] == '}' ) {
                    rstring.erase(i,1);
                    i++;
                } else {
                    i++;
                }
            }
            std::istringstream commands(rstring);
            processCommand(commands);
    }else{
        std::string temp = rstring.substr(2,rstring.size()-4);
    std::istringstream commands(temp);
    processCommand(commands);
    }
    
}

//name : exec()
//purpose : reads and pops the top element off the stack, a boolean, and causes
//a Datum with the opposite boolean value of the popped element to be 
//pushed on the stack.
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
// if the top element of the stack is not an rstring an error is thrown. 
void RPNCalc::Not(){
    if (stack.isEmpty()){
        std::cerr << "Error: empty_stack" 
        << std::endl;
        return;
    }
    Datum top = stack.top();
    stack.pop();
    if (not top.isBool()){
        std::cerr << "Error: datum_not_bool" << std::endl;
        return;
    }
    else{
        if (top.getBool()){
            stack.push(Datum(false));
        }
        else{
            stack.push(Datum(true));
        }
    }
}

//name : quit()
//purpose : ends the program if "quit" is read in the input stream.
//arguments : none
//returns : n/a
//effects : n/a
void RPNCalc::quit(){
    std::cerr<<"Thank you for using CalcYouLater.\n";
    
}

//name : print()
//purpose : prints the value on the top of the stack to std::cout 
//(without popping it) followed by a new line.
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.

void RPNCalc::print(){
    if (stack.isEmpty()){
                std::cerr<<"Error: empty_stack"<<std::endl;
                return;
            }
            if (stack.top().isInt()){
                std::cout << stack.top().getInt() << std::endl;
            }
            else if(stack.top().isBool()){
                if (stack.top().getBool()){
                    std::cout<< "#t" << std::endl;
                }
                else{
                    std::cout<< "#f" << std::endl;
                }  
            }
            else{
                cout << stack.top().getRString() << endl;
            }
}

//name : swap()
//purpose : swaps the top two elements of the stack.
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
void RPNCalc::swap(){
     if (stack.isEmpty()){
        std::cerr<<"Error: empty_stack"<<std::endl;
        return;
    }
    Datum top = stack.top();
    stack.pop();
    Datum second = stack.top();
    stack.pop();
    stack.push(top);
    stack.push(second);
}

//name : drop()
//purpose : the top element is removed from the stack
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
void RPNCalc::drop(){
    if (stack.isEmpty()){
                std::cerr<<"Error: empty_stack"<<std::endl;
                return;
            }
    stack.pop();
}

//name : dup()
//purpose : the top element is duplicated and added to the stack.
//arguments : none
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
void RPNCalc::dup(){
    if (stack.isEmpty()){
                std::cerr<<"Error: empty_stack"<<std::endl;
                return;
            }
    Datum top = stack.top();
    Datum duplicate = top;
    stack.push(duplicate);
}

void RPNCalc::unimplemented(const string &entry){
    std::cerr<<entry + ": unimplemented"<<std::endl;
    return;
}

//name : processCommand()
//purpose : connects the entry being read with the required functions. 
//arguments : the reference to an input stream
//returns : n/a
//effects : n/a
void RPNCalc::processCommand(istream &cmd){
    
    std::string entry;
    int value;

    while (cmd >> entry){
        if (entry == "{"){
            std::string temp = parseRString(cmd);
            stack.push(Datum(temp));
        }
        else if (got_int(entry,&value)){
            stack.push(Datum(value));
        }
        else if (entry == "print"){
            print();
        }
        else if(entry == "not"){
            Not();
        }else if(entry == "clear"){
            stack.clear();
        }
        else if(entry[0] == '#'){
            if (entry == "#f"){
                stack.push(Datum(false));
            }else if (entry == "#t"){
                stack.push(Datum(true));
            }else{
                std::cerr << "Error: invalid boolean " << entry << std::endl;
                continue;
            }

        }else if (entry == "drop"){
            drop();
        }
        else if (entry == "dup"){
            dup();
        }
        else if (entry == "swap"){
            swap();
        }
        else if(entry == "exec"){
            exec();
        }else if(entry == "file"){
            file();
        }
        else if (entry == "if"){
            If();
        }
        else if(entry == "-"){
            performArithmetic(entry);
        }else if(entry == "+"){
            performArithmetic(entry);
        }else if(entry == "-"){
            performArithmetic(entry);
        }else if(entry == "*"){
            performArithmetic(entry);
        }else if(entry == "/"){
            performArithmetic(entry);
        }else if(entry == "mod"){
            performArithmetic(entry);
        }else if(entry == "<"){
            performArithmetic(entry);
        }else if(entry == "<="){
            performArithmetic(entry);
        }else if(entry == ">"){
            performArithmetic(entry);
        }else if(entry == ">="){
            performArithmetic(entry);
        }else if(entry == "=="){
            performArithmetic(entry);
        }else if(entry == "quit"){
        quit();
        return;
        }
        else{
        unimplemented(entry);
        }
    }
}

//name : performArithmetic()
//purpose : computes certain arithmetic operations depending on the 
//required input entered.
//arguments : a constant reference to a string input.
//returns : n/a
//effects : if the stack is empty an error message is printed to cerr.
//if the user attempts to divide by zero an error is thrown
void RPNCalc::performArithmetic(const string& operation){
    if (stack.size() < 2){
        std::cerr <<"Error: empty_stack\n";
        return;
    }
    try{
        int right = stack.top().getInt();
        stack.pop();
        int left = stack.top().getInt();
        stack.pop();

        if (operation == "+"){
            stack.push(Datum(left+right));
        }else if(operation == "-"){
            stack.push(Datum(left-right));
        }else if(operation == "*"){
            stack.push(Datum(left*right));
        }else if (operation == "/"){
            if (right == 0){
                std::cerr<<"division by 0\n";
            }
            else{
                stack.push(Datum(left/right));
            }
        }else if(operation == "mod"){
            stack.push(Datum(left % right));
        }else if (operation == "<") {
            stack.push(Datum(left < right));
        } else if (operation == ">") {
            stack.push(Datum(left > right));
        } else if (operation == "<=") {
            stack.push(Datum(left <= right));
        } else if (operation == ">=") {
            stack.push(Datum(left >= right));
        } else if (operation == "==") {
            stack.push(Datum(left == right));
        }
    }catch(const std::runtime_error& e){
        std::cerr << "Error: datum_not_int\n";
        stack.pop();
        stack.pop();
    }
}
