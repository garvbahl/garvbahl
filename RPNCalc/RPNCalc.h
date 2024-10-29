//This file contains the class for RPNCalc which contains the functionality
//for the RPN calculator allowing logical and arithmetic functions to be
//carried out on strings written in reverse polish notation.
//A stack ADT is used to handle the elements in this assignment.
//Author : Garv Bahl
//Assignment : CalcYouLater
//Date : 10/23/2024
//Help received : TAs

#ifndef RPNCALC_H
#define RPNCALC_H

#include "DatumStack.h"

class RPNCalc {
public:
    RPNCalc();            
    void run();   
    
private:
    void processCommand(std::istream &cmd); 
    void performArithmetic(const std::string& operation);  
    DatumStack stack;
    void exec();
    void file();
    void If();
    void Not();        
    void quit();
    void print();
    void swap();
    void drop();
    void dup();
    void unimplemented(const std::string& entry);
};

#endif 
