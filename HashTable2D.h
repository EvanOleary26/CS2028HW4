#ifndef __HashTable2D__
#define __HashTable2D__

#include <iostream>
#include <climits>
#include "Exceptions.h"

const int MAXSIZE2 = 100;
const int ARRAYSIZE = 5;

class HashTable2D {
    private:
        int data[MAXSIZE2][ARRAYSIZE];
        bool deletedF[MAXSIZE2][ARRAYSIZE];
    public:

        HashTable2D() {
            for (int i{}; i < MAXSIZE2; i++) {
                for (int j{}; j < ARRAYSIZE; j++) {
                    data[i][j] = INT_MIN;
                    deletedF[i][j] = false;
                }
            }
        };

        ~HashTable2D();

        int Insert(int inVal);
        int Remove(int inVal);
        int Find(int inVal);
        int Hash(int inVal);
        void Print();

        bool isFull();
        bool isEmpty();


};


#endif