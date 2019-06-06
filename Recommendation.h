#ifndef _RECOMMENDATION_H_
#define _RECOMMENDATION_H_

#include <iostream>
#include <string>

#include "Csr.h"

class Recommendation {
public:
    Recommendation ();
    ~Recommendation ();
    double * calVecMatrix (Csr * M, int u, Csr * S);
    double * dense(Csr * M, int u);
};

#endif   // !defined _RECOMMENDATION_H