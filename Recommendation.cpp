#include <iostream>
#include <string>

#include "Recommendation.h"

Recommendation::Recommendation () { }

Recommendation::~Recommendation () { }

double * Recommendation::calVecMatrix(Csr * M, int user, Csr * S) {
    double * uvec = dense(M, user); // make a dense vector for the u-th row in M
    double * x = new double[M->getColumns()](); // make a dense vector, initialized to 0, for the final results

    for (size_t i = 0; i < S->getRows(); i ++) { // go over each row of S
        for (size_t k = S->getRow_ptr(i); k < S->getRow_ptr(i+1); k ++) { // go over each non-zero value in row i

            int j = S->getCol_ind(k); // the column index of a non-zero value
            double val = S->getVal(k);   // the non-zero value
            
            x[j-1] += val * uvec[i]; // accumulate results
        }
    }
    delete [] uvec;
    return (x);  
}

double * Recommendation::dense(Csr * M, int user) {
    double * uvec = new double[M->getColumns()]();

    for (size_t i = 0; i < M->getColumns(); i ++){
        uvec[i] = M->getElement(user, i);
    }

    return (uvec);
}