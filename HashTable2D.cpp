#include "HashTable2D.h"

HashTable2D::~HashTable2D() {
    for (int i{}; i < MAXSIZE2; i++) {
        for(int j{}; j < ARRAYSIZE; j++) {
        data[i][j] = INT_MIN;
        deletedF[i][j] = false;
        }
    }
}

int HashTable2D::Insert(int inVal) {
    if (isFull()) {
        throw Exception(-1, "Hash Table is full");
    }

    int row = Hash(inVal);
    int col = 0;
    int start = col;
    
    while(data[row][col] != INT_MIN && col < ARRAYSIZE) { //INT_MIN in place of NULL
        col++;
    }
    if (col == ARRAYSIZE) {
        throw Exception(-1, "No space to add value");
    }
    data[row][col] = inVal;
    return (col - start) + 1;
}

int HashTable2D::Remove(int target) {
    Find(target);
    int row = Hash(target);
    int col = 0;
    int start = col;

    while(col < ARRAYSIZE && data[row][col] != target) {
        col++;
    }

    deletedF[row][col] = true;
    data[row][col] = INT_MIN;  //INT_MIN in place of NULL
    return (col - start) + 1;
}

int HashTable2D::Find(int target) {
    int row = Hash(target);
    int col = 0;
    int start = col;

    while(col < ARRAYSIZE && (data[row][col] != target || deletedF[row][col]) ) { //INT_MIN in place of NULL
        if (data[row][col] == INT_MIN && !deletedF[row][col]) {
            throw Exception(-1, "Unable to find value in Hash Table");
        }
        col++;
    }
    if (col >= ARRAYSIZE || (data[row][col] != target || deletedF[row][col]) ) {
        throw Exception(-1, "Unable to find value in Hash Table");
    }
    return (col - start) + 1;
}

int HashTable2D::Hash(int inVal) {
    return inVal % MAXSIZE2;
}

void HashTable2D::Print() {
    std::cout << "\nTwo Dimensional Hash" << std::endl;
    std::cout << "\tIndex\tValues" << std::endl;
    for (int i{}; i < MAXSIZE2; i++) {
        std::cout << "\t  " << i << "\t";
        if ((data[i][0] == INT_MIN) && 
            (data[i][1] == INT_MIN) && 
            (data[i][2] == INT_MIN) && 
            (data[i][3] == INT_MIN) && 
            (data[i][4] == INT_MIN)) {
                std::cout << "Empty Values" << std::endl;
        } else {
            for (int j{}; j < ARRAYSIZE; j++) {
                if (data[i][j] != INT_MIN) {
                    std::cout << j << ": " << data[i][j] << "  ";
                } else {
                    std::cout << j << ": Empty  ";
                }
            }
            std::cout << std::endl;
        }
    }

}

bool HashTable2D::isFull() {
    for (int i{}; i < MAXSIZE2; i++) {
        for (int j{}; j < ARRAYSIZE; j++) {
            if (data[i][j] == INT_MIN) {
                return false;
            }
        }
    }
    return true;
}

bool HashTable2D::isEmpty() {
    for (int i{}; i < MAXSIZE2; i++) {
        for (int j{}; j < ARRAYSIZE; j++) {
            if (data[i][j] != INT_MIN) {
                return false;
            }
        }
    }
    return true;
}