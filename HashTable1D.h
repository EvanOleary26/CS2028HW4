#ifndef __HashTable1D__
#define __HashTable1D__

#include <iostream>
#include <climits>
#include "Exceptions.h"

const int MAXSIZE1 = 500;

class HashTable1D {
    private:
        int data[MAXSIZE1];
        bool deletedF[MAXSIZE1];
    public:

        HashTable1D() {
            for (int i{}; i < MAXSIZE1; i++) {
                data[i] = INT_MIN;
            }
        };

        ~HashTable1D();

        int Insert(int inVal);
        int Remove(int inVal);
        int Find(int inVal);
        int Hash(int inVal);
        void Print();

        bool isFull();
        bool isEmpty();


};


#endif