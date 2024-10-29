//this file contains the implementation of the DatumStack class
//Author : Garv Bahl
//Assignment : CalcYouLater
//Date : 10/16/2024
//Help received : TAs

#include "DatumStack.h"
#include "Datum.h"

//creates an empty constructor 
DatumStack::DatumStack(){}

//creates a constructor for the DatumStack that has the parameters data
//and size.
DatumStack::DatumStack(Datum data[], int size){
    for (int i = 0; i < size; i++){
        stack_data.push_back(data[i]);
    }
}

//an empty destructor
DatumStack::~DatumStack(){}

//name : isEmpty()
//purpose : check if the stack is empty.
//arguments : none
//returns : boolean result for if the stack is empty
bool DatumStack::isEmpty() const{
    return stack_data.empty();
}

//name : clear()
//purpose : clears the stack
//arguments : none
//returns : none
void DatumStack::clear() {
    stack_data.clear();
}

//name : size()
//purpose : provides the size of stack(number of elements)
//arguments : none
//returns : int value of the size of the stack.
int DatumStack::size() const{
    return stack_data.size();
}

//name : top()
//purpose : retreive the value at the top of the stack
//arguments : none
//returns : the top value of the stack
//effects : if the stack is empty a runtime_error is thrown appropriately.
Datum DatumStack::top() const{
    if (isEmpty()){
        throw std::runtime_error("empty_stack");
    }
    return stack_data.back();
}

//name : pop()
//purpose : remove the top value of the stack.
//arguments : none
//returns : none
//effects : if the stack is empty a runtime_error is thrown appropriately.
void DatumStack::pop(){
    if (isEmpty()){
        throw std::runtime_error("empty_stack");
    }
    stack_data.pop_back();
}

//name : push()
//purpose : add a datum object to the top of the stack
//arguments : a reference to a Datum object
//returns : none
void DatumStack::push(const Datum& datum){
    stack_data.push_back(datum);
}