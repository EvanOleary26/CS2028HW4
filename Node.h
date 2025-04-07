#ifndef __NODE__H
#define __NODE__H

template<class T>
class Node {
    public:
        T data;
        Node<T> *left;
        Node<T> *right;
    
        //Constructors
        Node() : data(T()), left(nullptr), right(nullptr) {};
        Node(T inVal) : data(inVal), left(nullptr), right(nullptr) {};

        //Deconstructor
        ~Node() {
            delete left;
            delete right;
        }
};

#endif