//This file contains the class for DatumStack which stores a vector of Datum
//objects which are stored in a vector and allows us to move and pop
//the Datum objects in a way that is similar to that of a stack.
//Author : Garv Bahl
//Assignment : CalcYouLater
//Date : 10/16/2024
//Help received : TAs

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include "Datum.h"
#include <vector>
#include <stdexcept>

class DatumStack{
    public:
    DatumStack();
    DatumStack(Datum data[], int size);
    ~DatumStack();

    bool isEmpty() const;
    void clear();
    int size() const;
    Datum top() const;
    void pop();
    void push(const Datum& datum);

    private:
    std::vector<Datum> stack_data;
};

#endif