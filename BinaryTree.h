#ifndef __BINARYTREE__H
#define __BINARYTREE__H

#include "Node.h"
#include "Exceptions.h"
 
template <class T>
class BinaryTree {
    private:
        Node<T> *root;
        int size;

        void rotateLeft(Node<T> *parent, Node<T> *child);
        void rotateRight(Node<T> *parent, Node<T> *child);
        void rotateLR(Node<T> *parent, Node<T> *child);
        void rotateRL(Node<T> *parent, Node<T> *child);
    public:
        //Constructor
        BinaryTree() : root(nullptr), size(0) {}

        //Deconstructor
        ~BinaryTree();

        //Getter
        Node<T> *getRoot() { return root; }

        //Functions
        void Insert(T inVal, Node<T> *parent);
        T Find(T target, Node<T> *parent);
        int getSize() { return size; }
        int getHeight(Node<T> *child);
        T* GetAllAscending(Node<T> *parent, int &arrSpotCounter, T* ascendArr);       //Returns a pointer to an array
        T* GetAllDescending(Node<T>* parent, int& arrSpotCounter, T* ascendArr);      //Returns a pointer to an array
        void EmptyTree();
        //T Remove(T inVal);
        Node<T>* Remove(T inVal, Node<T> *parent);
        T inOrderSuccessor(Node<T> *inNode);
        Node<T>* inOrderPred(T inVal);
        void displayTree(Node<T> *place);
        int Balance(Node<T> *parent, Node<T> *child);
        int getBF(Node<T> *parent);
};

#endif
