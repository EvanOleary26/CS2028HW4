#ifndef __HashTable2D__
#define __HashTable2D__

#include <climits>
#include "Exceptions.h"

const int MAXSIZE = 100;
const int ARRAYSIZE = 5;

class HashTable2D {
    private:
        int data[MAXSIZE][ARRAYSIZE];
        bool deletedF[MAXSIZE][ARRAYSIZE];
    public:

        HashTable2D() {
            for (int i{}; i < MAXSIZE; i++) {
                for (int j{}; j < ARRAYSIZE; j++) {
                    data[i][j] = INT_MIN;
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