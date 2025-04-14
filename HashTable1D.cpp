#include "HashTable1D.h"

HashTable1D::~HashTable1D() {
    for (int i{}; i < MAXSIZE1; i++) {
        data[i] = INT_MIN;
        deletedF[i] = false;
    }
}

int HashTable1D::Insert(int inVal) {
    if (isFull()) {
        throw Exception(-1, "Hash Table is full");
    }

    //If location you want add at is taken add move up a space
    int index = Hash(inVal);
    int start = index;
    int count = 0;  // To prevent infinite loops
    
    // Look for an empty slot or a deleted slot
    while (count < MAXSIZE1 && data[index] != INT_MIN) {
        index = (index + 1) % MAXSIZE1;
        count++;
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

    int count{};

    while (data[index] != target && count < MAXSIZE1) {
        // If we find an empty, never-used slot, the item isn't in the table
        if (data[index] == INT_MIN && !deletedF[index]) {
            throw Exception(-1, "Unable to find value in Hash Table");
        }
        index = (index + 1) % MAXSIZE1;
        count++;
    }
    if (data[index] == INT_MIN || count == MAXSIZE1) {
        throw Exception(-1, "Unable to find value in Hash Table");
    }

    return (index - start) + 1;
}

int HashTable1D::Hash(int inVal) {
    return inVal % MAXSIZE1;
}

void HashTable1D::Print() {
    std::cout << "\nOne Dimensional Hash" << std::endl;
    std::cout << "\tIndex\tValue" << std::endl;
    for (int i{}; i < MAXSIZE1; i++) {
        if (data[i] != INT_MIN) {
            std::cout << "\t  " << i << "\t" << data[i] << std::endl;
        }
        if (i > 0 && i < MAXSIZE1) {
            if (data[i] == INT_MIN && data[i-1] != INT_MIN) {
                std::cout << "\t" << i << "-";
            }
            if (data[i] == INT_MIN && data[i+1] != INT_MIN) {
                std::cout << i << "\tEmpty" << std::endl;
            }
        } else {
            if (data[i] == INT_MIN && i == 0) {
                std::cout << "  \t" << i << "-";
            }
            if (data[i] == INT_MIN && i == MAXSIZE1) {
                std::cout << i << "\tEmpty" << std::endl;
            }
        }
    }
}

bool HashTable1D::isFull() {
    for (int i{}; i < MAXSIZE1; i++) {
        if (data[i] == INT_MIN && !deletedF[i]) {   //Check for a value that isnt filled
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