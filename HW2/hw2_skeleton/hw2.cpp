////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 2: Source file
// 1. Complete the implementation of VariableList
// 2. You can add your implementation only in "IMPLEMENT HERE" & "CHANGE HERE"
//    Do not touch other lines; but you can change main() for testing
////////////////////////////////////////////////////////////////////////////////
#include "hw2.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// You may also want to have additional functions, 
// e.g., static functions or forward declaration of functions, Then
//
// IMPLEMENT HERE
//
// NOTE: DO NOT USE global, static variables
////////////////////////////////////////////////////////////////////////////////

// Constructors
VariableList::VariableList() {
    Vl_len = { 0 };
    iary = new int[1000]{};
    fary = new float[1000]{};
    sary = new std::string[1000]{};
}
VariableList::VariableList(const int* initialArray, const int size) {
    Vl_len = size;
    iary = new int[1000]{};
    fary = new float[1000]{};
    sary = new std::string[1000]{};
    for (int i = 0; i < size; i++) {
        iary[i] = initialArray[i];
    }
    iary[size] = '/0';
}
VariableList::VariableList(const float* initialArray, const int size) {
    Vl_len = size;
    iary = new int[1000]{};
    fary = new float[1000]{};
    sary = new std::string[1000]{};
    for (int i = 0; i < size; i++) {
        fary[i]=initialArray[i];
    }
    fary[size] = '/0';
}
VariableList::VariableList(const std::string* initialArray, const int size) {
    Vl_len = size;
    iary = new int[1000]{};
    fary = new float[1000]{};
    sary = new std::string[1000]{};
    for (int i = 0; i < size; i++) {
        sary[i] = initialArray[i];   
    }
    fary[size] = '/0';
}

// Destructor
// Note: Please delete(free) the memory you allocated 
VariableList::~VariableList() {
    delete[] sary;
    delete[] iary;
    delete[] fary;
    // IMPLEMENT HERE
}

// Member functions
// add: Add the value at the end of the list
void VariableList::add(const int val) {
    this->iary[Vl_len]=val;
    Vl_len += 1;
    // IMPLEMENT HERE
}
void VariableList::add(const float val) {
    this->fary[Vl_len] = val;
    Vl_len += 1;
    // IMPLEMENT HERE
}
void VariableList::add(const std::string& val) {
    this->sary[Vl_len] = val;
    Vl_len += 1;
    // IMPLEMENT HERE
}

// append: Copy all values of varList and append them at the end of the list
void VariableList::append(const VariableList& varList) {
    int varlen=varList.getSize(); 
    for (int i{ 0 }; i < varlen; i++) {
        if (varList.getType(i) == DataType::Integer) {
            int integ;
            varList.getValue(i, integ);
            this->add(integ);
        }
        if (varList.getType(i) == DataType::Float) {
            float floa;
            varList.getValue(i, floa);
            this->add(floa);
        }
        if (varList.getType(i) == DataType::Str) {
            std::string st;
            varList.getValue(i, st);
            this->add(st);
        }
        if (varList.getType(i) == DataType::NotAvailable) {
            break;
        }
    }
 }


    // IMPLEMENT HERE

// replace: replace the value at the given index in the list
bool VariableList::replace(const int idx, const int val) {
    // IMPLEMENT HERE
    if (idx > Vl_len - 1) {
        return false;
    }
    switch (getType(idx)) {
        case DataType::Integer:
            iary[idx] = val;
            break;
        case DataType::Float:
            fary[idx] = NULL;
            iary[idx] = val;
            break;
        case DataType::Str:
            sary[idx] = '\n';
            iary[idx] = val;
            break;
    }
    return true; // CHANGE HERE
}
bool VariableList::replace(const int idx, const float val) {
    // IMPLEMENT HERE
    if (idx > Vl_len - 1) {
        return false;
    }
    switch (getType(idx)) {
    case DataType::Integer:
        fary[idx] = val;
        iary[idx] = NULL;
        break;
    case DataType::Float:
        fary[idx] = val;
        break;
    case DataType::Str:
        sary[idx] = '\n';
        fary[idx] = val;
        break;
    }
    return true; // CHANGE HERE
}
bool VariableList::replace(const int idx, const std::string& val) {
    // IMPLEMENT HERE
    if (idx > Vl_len-1) {
        return false;
    }
    switch (getType(idx)) {
    case DataType::Integer:
        iary[idx] = NULL;
        sary[idx] = val;
        break;
    case DataType::Float:
        fary[idx] = NULL;
        sary[idx] = val;
        break;
    case DataType::Str:
        sary[idx] = val;
        break;
    }
    return true; // CHANGE HERE
}

// remove: remove the item at the given index in the list
bool VariableList::remove(const int idx) {
    // IMPLEMENT HERE
    if (idx > Vl_len - 1) {
        return false;
    }
    switch (getType(idx)) {
    case DataType::Integer:
        iary[idx] = NULL;
    case DataType::Float:
        fary[idx] = NULL;
    }
    for (int i = 0; this->getType(i + 1) != DataType::NotAvailable; i++) {
        iary[i + idx] = iary[i + idx + 1];
        fary[i + idx] = fary[i + idx + 1];
        sary[i + idx] = sary[i + idx + 1];
    }
    iary[Vl_len-1] = NULL;
    fary[Vl_len-1] = NULL;
    sary[Vl_len-1] = '\n';
    this->Vl_len -= 1;
    return true; // CHANGE HERE
}

// getSize: return the number of elements of the List
unsigned int VariableList::getSize() const {
    // IMPLEMENT HERE
    return this->Vl_len; // CHANGE HERE
}

// getType: return the data type for the value at the given index
DataType VariableList::getType(const int idx) const {
    // IMPLEMENT HERE
    if (idx > Vl_len-1) {
        return DataType::NotAvailable;
    }
    if (this->iary[idx] != NULL) {
        return DataType::Integer;
    }
    if (this->fary[idx] != NULL) {
        return DataType::Float;
    }   
    else {
        return DataType::Str;
        }
     // CHANGE HERE
}

// getValue: copy the value to the variable
bool VariableList::getValue(const int idx, int& val) const {
    // IMPLEMENT HERE
    if (this->getType(idx) != DataType::Integer) {
        return false;
    }
    val = this->iary[idx];
    return true; // CHANGE HERE
}
bool VariableList::getValue(const int idx, float& val) const {
    // IMPLEMENT HERE
    if (this->getType(idx) != DataType::Float) {
        return false;
    }
    val = this->fary[idx];
    return true; // CHANGE HERE
}
bool VariableList::getValue(const int idx, std::string& val) const {
    // IMPLEMENT HERE
    if (this->getType(idx) != DataType::Str) {
        return false;
    }
    val = this->sary[idx];
    return true; // CHANGE HERE
}

////////////////////////////////////////////////////////////////////////////////
// You may also want to implement additional, private member functions here
// NOTE: DO NOT USE global, static variables
//
// IMPLEMENT HERE
//
////////////////////////////////////////////////////////////////////////////////
