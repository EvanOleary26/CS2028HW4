#include "HashTable1D.h"

HashTable1D::~HashTable1D() {

}

int HashTable1D::Insert(int inVal) {
    if (isFull()) {
        Exception(-1, "Hash Table is full");
    }

    //If location you want add at is taken add move up a space
    int index = Hash(inVal);
    int start = index;
    while(data[index] != INT_MIN) { //INT_MIN in place of NULL
        index = (index + 1) % MAXSIZE1;
    }
    data[index] = inVal;
    return (index - start) + 1;
}

int HashTable1D::Remove(int target) {
    Find(target);
    int index = Hash(target);
    int start = index;

    while(data[index] != target) {
        index = (index + 1) % MAXSIZE1;
    }
    deletedF[index] = true;
    data[index] = INT_MIN;  //INT_MIN in place of NULL
    return (index - start) + 1;
}

int HashTable1D::Find(int target) {
    int index = Hash(target);
    int start = index;

    while(data[index] != target && (data[index] == INT_MIN && deletedF[index] == false) ) { //INT_MIN in place of NULL
        index = (index + 1) % MAXSIZE1;
    }
    if (data[index] == INT_MIN) {   //INT_MIN in place of NULL
        Exception(-1, "Unable to find value in Hash Table");
    }
    return (index - start) + 1;
}

int HashTable1D::Hash(int inVal) {
    return inVal % MAXSIZE1;
}

void HashTable1D::Print() {
    std::cout << "\tIndex\t\tValue" << std::endl;
    for (int i{}; i < MAXSIZE1; i++) {
        if (data[i] != INT_MIN) {
            std::cout << "\t  " << i << "\t\t" << data[i] << std::endl;
        }
        if (i > 0 && i < MAXSIZE1) {
            if (data[i] == INT_MIN && data[i-1] != INT_MIN) {
                std::cout << "\t" << i << "-";
            }
            if (data[i] == INT_MIN && data[i+1] != INT_MIN) {
                std::cout << i << "\t\tEmpty Values" << std::endl;
            }
        } else {
            if (data[i] == INT_MIN && i == 0) {
                std::cout << "  \t" << i << "-";
            }
            if (data[i] == INT_MIN && i == MAXSIZE1) {
                std::cout << i << "\t\tEmpty Values" << std::endl;
            }
        }
    }
}

bool HashTable1D::isFull() {
    for (int i{}; i < MAXSIZE1; i++) {
        if (data[i] == INT_MIN) {   //Check for a value that isnt filled
            return false;
        }
    }
    return true;
}

bool HashTable1D::isEmpty() {
    for (int i{}; i < MAXSIZE1; i++) {
        if (data[i] != INT_MIN) {   //Check for a value that is filled
            return false;
        }
    }
    return true;
}