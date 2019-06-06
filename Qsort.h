#ifndef _QSORT_H_
#define _QSORT_H_

#include <iostream>
#include <string>

#include "Csr.h"

class Qsort {
public:
    Qsort ();
    Qsort (double * uvec, int left, int right);
    ~Qsort ();
    void startSort (double * uvec, int left, int right);
    double getArr(int i);
    void setArr(int i, double val);
    size_t getIndex(int i);
    void setIndex(int i, size_t val);
    size_t getSize();
    void setSize(size_t i);
    void printArr();

protected:
    size_t * index_;
    double * arr_;
    size_t size_;

private:
    void quickSort (int left, int right);
    int partition (int left, int right);
    void swap(int left, int right);
};

#include "Qsort.inl"

#endif   // !defined _QSORT_H