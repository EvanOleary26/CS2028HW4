#include "HashTable1D.h"

HashTable1D::~HashTable1D() {
    
}

int HashTable1D::Insert(int inVal) {   //Need to update to return the number of locations it moved before placing its value
    if (isFull()) {
        Exception(-1, "Hash Table is full");
    }

    //If location you want add at is taken add move up a space
    int index = Hash(inVal);
    int start = index;
    while(data[index] != INT_MIN) { //INT_MIN in place of NULL
        index = (index + 1) % MAXSIZE;
    }
    data[index] = inVal;
    return (index - start) + 1;
}

int HashTable1D::Remove(int target) {
    Find(target);
    int index = Hash(target);
    int start = index;

    while(data[index] != target) {
        index = (index + 1) % MAXSIZE;
    }
    deletedF[index] = true;
    data[index] = INT_MIN;  //INT_MIN in place of NULL
    return (index - start) + 1;
}

int HashTable1D::Find(int target) { //Need to return the number of spots it moved before finding value or not
    int index = Hash(target);
    int start = index;

    while(data[index] != target && (data[index] == INT_MIN && deletedF[index] == false) ) { //INT_MIN in place of NULL
        index = (index + 1) % MAXSIZE;
    }
    if (data[index] == INT_MIN) {   //INT_MIN in place of NULL
        Exception(-1, "Unable to find value in Hash Table");
    }
    return (index - start) + 1;
}

int HashTable1D::Hash(int inVal) {
    return inVal % MAXSIZE;
}

void HashTable1D::Print() {

}

bool HashTable1D::isFull() {
    for (int i{}; i < MAXSIZE; i++) {
        if (data[i] == INT_MIN) {   //Check for a value that isnt filled
            return false;
        }
    }
    return true;
}

bool HashTable1D::isEmpty() {
    for (int i{}; i < MAXSIZE; i++) {
        if (data[i] != INT_MIN) {   //Check for a value that is filled
            return false;
        }
    }
    return true;
}

