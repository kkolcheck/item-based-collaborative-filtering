#include <iostream>
#include <string>

#include "Qsort.h"
#include "Csr.h"

Qsort::Qsort () : index_ (0), arr_ (0), size_ (0) { }

Qsort::Qsort (double * r_u, int left, int right) : index_(0), arr_(0), size_ (0)
{
    setSize(right+1);
    index_ = new size_t [getSize()]();
    arr_ = new double [getSize()]();
    for (int i = 0; i < getSize(); i++){
        setIndex(i, i);
        setArr(i, r_u[i]);
    }
    quickSort(left, right);
}

Qsort::~Qsort ()
{
    delete [] index_;
    delete [] arr_;
}

void Qsort::startSort (double * r_u, int left, int right){
    delete [] index_;
    delete [] arr_;
    setSize(right+1);
    index_ = new size_t [getSize()]();
    arr_ = new double [getSize()]();
    for (int i = 0; i < getSize(); i++){
        setIndex(i, i);
        setArr(i, r_u[i]);
    }
    quickSort(left, right);
}

void Qsort::printArr (){
    for (size_t i = 0; i < getSize(); i++)
        std::cout << getIndex(i) << ": " << getArr(i) << std::endl; 
}