#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h> // fout
#include <time.h>

#include "Csr.h"
#include "Recommendation.h"
#include "Qsort.h"


Csr * fileIn (char * input);
void matrixOut (std::string file, Csr * outMatrix);
void filteringOut (char * training, char * test, char * N, char * output);
void printHitRates (double hitCounter, int totalTesting, double arHitRank, int filterNum);

static double startTime;
static double endTime;
static double elapsedTime;

/* user should input in this order: train1.txt, test1.txt, N, output.txt */
int main(int argc, char * argv[]){
    startTime = clock();

    filteringOut (argv[1], argv[2], argv[3], argv[4]);
    
    endTime = clock();
    elapsedTime += endTime - startTime;
    elapsedTime = (elapsedTime / 1000);
    std::cout << "Time: " << elapsedTime << " ms" << std::endl;
    std::cout << "Program completed." << std::endl;

    return 0;
} // end main

Csr * fileIn (char * input){
    std::ifstream inFile;
    inFile.open(input);

    //Read and store first line of file
    std::string line;
    getline(inFile, line);

    //store line as streamstring
    std::stringstream ssline;
    ssline << line;    
    int token;

    //Parse matrix details
    ssline >> token;
    int rows = token;
    ssline >> token;
    int col = token;
    ssline >> token;
    int nnz = token;
    Csr * inMatrix = new Csr(rows, col, nnz);

    /* Import CSR into appropriate arrays */
    inMatrix->setRow_ptr (0,0);
    int nnzIndex = 0;
    for (int i = 0; i < inMatrix->getRows(); i ++){
        getline(inFile, line);
        ssline.str("");
        ssline.clear();
        ssline << line;
        while (ssline >> token){
            // int values in document are in pairs
            inMatrix->setCol_ind(nnzIndex, token);
            ssline >> token;
            inMatrix->setVal(nnzIndex, token);
            nnzIndex ++;
        } //end while
        inMatrix->setRow_ptr(i + 1, nnzIndex);     // Keep track of how many non zero entries in each row
    } //end for
    inFile.close();

    return inMatrix;
}

void matrixOut (std::string file, Csr * outMatrix){
    int rows = outMatrix->getRows();
    int cols = outMatrix->getColumns();
    int nnz = outMatrix->getNnz();
    int nnzIndex = 0;
    std::ofstream outFile;  

    //output matrix
    outFile.open(file);
    outFile << rows << " " << cols << " " << nnz << std::endl;
    for (int i = 0; i < rows; i ++){
        for (int j = outMatrix->getRow_ptr(i); j < outMatrix->getRow_ptr(i+1); j ++){
            outFile << outMatrix->getCol_ind(nnzIndex) << " " << outMatrix->getVal(nnzIndex) << " ";
            nnzIndex ++;
            if (j + 1 == outMatrix->getRow_ptr(i+1) && i + 1 != rows){
                outFile << std::endl;
            } 
        } //end for
    } //end for
    outFile.close();
}

void filteringOut (char * training, char * test, char * N, char * output) {
    
    Csr * M;    // training data
    Csr * T;    // test data
    Csr * S;    // similarity matrix
    
    /* Times are static */
    endTime = clock();
    elapsedTime = endTime - startTime;
    
    /* File import */
    M = fileIn(training);
    T = fileIn(test);

    /* Create similarity matrix */
    startTime = clock();
    M->transposeCsr();
    S = M->returnSimilarityMatrix();

    /* Create user recommendations, sort, and output */
    int filterNum = std::strtod(N, NULL);
    M->transposeCsr();
    int mrows = M->getRows(), mcols = M->getColumns();
    double hitCounter = 0, arHitRank = 0;
    std::ofstream outFile;
    outFile.open(output);
    /* Calculate recommendations for each user */
    for (size_t user = 0; user < mrows; user++){
        Recommendation rec;
        double * r_u = rec.calVecMatrix(M, user, S);
        Qsort sorted(r_u, 0, mcols-1);   //quicksort takes n-1
        size_t counter = 0;
            /* recommend all items */
        if (filterNum >= mcols){
            filterNum = mcols;  //adjust for accurate hitRank
            for (size_t i = 0; i < mcols; i++){
                if(M->getElement(user,sorted.getIndex(i)) != 1){
                    endTime = clock();
                    elapsedTime += endTime - startTime;
                    outFile << "Item" << sorted.getIndex(i)+1 << " " << sorted.getArr(i) << " ";
                    startTime = clock();
                }
                counter++;
                if (T->getElement(user,sorted.getIndex(i))!= 0) {
                    hitCounter++;
                    arHitRank += (1.0 / (counter));
                }
            }
        endTime = clock();
        elapsedTime += endTime - startTime;
        outFile << std::endl;
        startTime = clock();
        } else {
                /* recommend N number of items */
            for (size_t i = 0; i < mrows; i ++){
                if(counter < filterNum){
                    if(M->getElement(user,sorted.getIndex(i)) != 1){
                        endTime = clock();
                        elapsedTime += endTime - startTime;
                        outFile << "Item" << sorted.getIndex(i)+1 << " " << sorted.getArr(i) << " ";
                        startTime = clock();
                        counter++;
                        if (T->getElement(user,sorted.getIndex(i))!= 0) {
                            hitCounter++;
                            arHitRank += (1.0 / (counter));
                        }       
                    }
                }
            } //end for
            if (N != 0){
                endTime = clock();
                elapsedTime += endTime - startTime;
                outFile << std::endl;
                startTime = clock();
            }
        }
        delete [] r_u;
    }
    /* After all users have recommendations, print HR and ARHR */
    printHitRates(hitCounter, mrows, arHitRank, filterNum);

    delete M;
    delete T;
    delete S;
}

void printHitRates (double hitCounter, int mrows, double arHitRank, int filterNum) {
    //Calculate and output HR & ARHR
    double hitRate = hitCounter / (double)mrows;
    arHitRank = (arHitRank / (double)mrows);
    std::cout << "HR = "<< hitRate << std::endl;
    std::cout << "ARHR = " << arHitRank << std::endl;
}