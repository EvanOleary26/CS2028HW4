#include "BinaryTree.h"
#include <cmath>

template<class T>
BinaryTree<T>::~BinaryTree() { //Calls ~Node which recurively will delete all elements in the tree
    delete root;
}

template<class T>
void BinaryTree<T>::rotateLeft(Node<T> *parent, Node<T> *child) {
    // turning "a->b->c" into "a<-b->c"
    // where parent is b (since its the new parent) and child is a (since it is the new child)
    //there is a case where the parent and child are not equal to each other. This is where we are trying to rotate the root
    if (root == child) {
        root = child->right;
        child->right = root->left;
        root->left = child;
    }
    else if (parent->right == child) { //if new parent is to the right (like "a->b")
        parent->right = child->right; //"a->c"
        child->right = parent->right->left;
        parent->right->left = child;
    }
    else { 
        parent->left = child->right;
        child->right = parent->left->left;
        parent->left->left = child;
    }
}

template<class T>
void BinaryTree<T>::rotateRight(Node<T> *parent, Node<T> *child) {
    // turning "a<-b<-c" into "a<-b->c"
    // where parent is b (since its the new parent) and child is c (since it is the new child)
    if (root == child) {
        root = child->left;
        child->left = root->right;
        root->right = child;
    }
    else if (parent->right == child) { //if new parent is to the left (like "a<-b")
        parent->right = child->left; //"a<-c"
        child->left = parent->right->right;
        parent->right->right = child;
    }
    else {
        parent->left = child->left;
        child->left = parent->left->right;	
        parent->left->right = child;
    }
}

template<class T>
void BinaryTree<T>::rotateLR(Node<T> *parent, Node<T> *child) {
    //turning A right -> C left -> B into A -> B -> C into A <- B -> C
    Node<T>* B = child->left->right;  
    Node<T>* A = child;               
    Node<T>* C = child->left; 
    if (root == child) {
        root = B;                 // B becomes the new root
        A->left = B->right;       // A's left points to B's right
        C->right = B->left;       // C's right points to B's left
        B->right = A;             // B's right points to A
        B->left = C;              // B's left points to C  
    } else if (parent->right == child){
        parent->right = B;        // Parent's right points to B
        A->left = B->right;       // A's left points to B's right
        C->right = B->left;       // C's right points to B's left
        B->right = A;             // B's right points to A
        B->left = C;              // B's left points to C  
    } else {
        parent->left = B;         // Parent's left points to B
        A->left = B->right;       // A's left points to B's right
        C->right = B->left;       // C's right points to B's left
        B->right = A;             // B's right points to A
        B->left = C;              // B's left points to C  
    }
}

template<class T>
void BinaryTree<T>::rotateRL(Node<T> *parent, Node<T> *child) {
    //turning A left -> C right -> B into C <- B <- A into C <- B -> A
    Node<T>* B = child->right->left;  
    Node<T>* A = child;               
    Node<T>* C = child->right; 
    if (root == child) {
        root = B;                 // B becomes the new root
        A->right = B->left;       // A's right points to B's left
        C->left = B->right;       // C's left points to B's right
        B->left = A;              // B's left points to A
        B->right = C;             // B's right points to C
    } else if (parent->right == child){
        parent->right = B;        // Parent's right points to B
        A->right = B->left;       // A's right points to B's left
        C->left = B->right;       // C's left points to B's right
        B->left = A;              // B's left points to A
        B->right = C;             // B's right points to C
    } else {
        parent->left = B;         // Parent's left points to B
        A->right = B->left;       // A's right points to B's left
        C->left = B->right;       // C's left points to B's right
        B->left = A;              // B's left points to A
        B->right = C;             // B's right points to C
    }
}

template<class T>
void BinaryTree<T>::Insert(T inVal, Node<T> *parent) {  //Need to add Tree Balancing to this function
    if (root == nullptr) {
        Node<T>* newNode = new Node<T>(inVal);
        root = newNode;
        size++;
        return;
    }
    if (inVal < parent->data) { //add to left
        if (parent->left == nullptr) {
            parent->left = new Node<T>(inVal);
            size++;
            Balance(nullptr, root);
        }
        else {
            Insert(inVal, parent->left);
        }
    }
    else if (inVal > parent->data) { //add to right
        if (parent->right == nullptr) {
            parent->right = new Node<T>(inVal);
            size++;
            Balance(nullptr, root);
        }
        else {
            Insert(inVal, parent->right);
        }
    }
    else {  //duplicate
        parent->data++;
    }
    
}

template<class T>
T BinaryTree<T>::Find(T target, Node<T> *parent) {
    if (parent == nullptr) {
        throw Exception(-1, "Cannot find item");
    }
    if (target == parent->data) {
        return parent->data;
    }
    if (target < parent->data) {
        return Find(target, parent->left);
    }
    else {
        return Find(target, parent->right);
    }
}

template <class T>
int BinaryTree<T>::getHeight(Node<T> *child){
    if (child == nullptr) {
        return 0;
        }

    int leftHeight = getHeight(child->left);
    int rightHeight = getHeight(child->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

template<class T>
T* BinaryTree<T>::GetAllAscending(Node<T> *parent, int &arrSpotCounter, T* ascendArr) {   //Return a pointer to an array
    if (parent->left != nullptr) {
        GetAllAscending(parent->left, arrSpotCounter, ascendArr);
    }
    ascendArr[arrSpotCounter] = parent->data;
	arrSpotCounter++;
    if (parent->right != nullptr) {
		GetAllAscending(parent->right, arrSpotCounter, ascendArr);
	}
    return ascendArr;
}

template<class T>
T* BinaryTree<T>::GetAllDescending(Node<T>* parent, int& arrSpotCounter, T* ascendArr) {  //Return a pointer to an array
    if (parent->right != nullptr) {
        GetAllDescending(parent->right, arrSpotCounter, ascendArr);
    }
    ascendArr[arrSpotCounter] = parent->data;
    arrSpotCounter++;
    if (parent->left != nullptr) {
        GetAllDescending(parent->left, arrSpotCounter, ascendArr);
    }
    
    return ascendArr;
}

template<class T>
void BinaryTree<T>::EmptyTree() {   //Clear out the tree leaving a nullptr root node at the end
    delete root->right;
    delete root->left;
    root = nullptr;
    size = 0;
}

/*
template<class T>
T BinaryTree<T>::Remove(T inVal) { //recursive remove – NEEDS inOrderPred FUNCTION TO WORK
	Node<T>* temp = root;
	T retVal;
	while (temp->data != inVal) {
		if (temp->data > inVal) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	if (temp->left == nullptr && temp->right == nullptr) { //leaf case
		retVal = temp->data;
		delete temp;
		return retVal;
	}
	else if (temp->left != nullptr && temp->right == nullptr) {//left child
		retVal = temp->data;
		Node<T>* replacement = temp->left;
		Remove(replacement->data);
		temp = replacement;
		return retVal;
	}
	else if (temp->left == nullptr && temp->right != nullptr) {//right child
		retVal = temp->data;
		Node<T>* replacement = temp->right;
		Remove(replacement->data);
		temp = replacement;
		return retVal;
	}
	else if (temp->left != nullptr && temp->right != nullptr) { //two children
		retVal = temp->data;
		Node<T>* replacement = inOrderPred(temp->data);
		Remove(replacement->data);
		return retVal;
	}
	else {
        throw Exception(0, "Item not found");
	}
    Balance(nullptr, root);
}
*/

template <class T>
Node<T>* BinaryTree<T>::Remove(T inVal, Node<T> *parent) {
    if (parent == nullptr) {
        return parent;
    }
    
    if (inVal < parent->data) { //Move left if inVal is less than parent->data
        parent->left = Remove(inVal, parent->left);
    } else if (inVal > parent->data) {  //Move right if inVal is more than parent->data
        parent->right = Remove(inVal, parent->right);
    } else {    //parent->data == inVal
        if (parent->left == nullptr) {  //Remove right node
            Node<T> *temp = parent->right;
            parent = nullptr;
            delete parent;
            size--;
            Balance(nullptr, root);
            return temp;
        } else if (parent->right == nullptr) {  //Remove left node
            Node<T> *temp = parent->left;
            parent = nullptr;
            delete parent;
            size--;
            Balance(nullptr, root);
            return temp;
        }

        //if neither is null
        parent->data = inOrderSuccessor(parent->right); //find lowest value in right subtree
        parent->right = Remove(parent->data, parent->right);  
        
    }
    
    return parent;
}

template <class T>
T BinaryTree<T>::inOrderSuccessor(Node<T> *inNode) {
    T minimum = inNode->data;
    while (inNode->left != nullptr) {
        minimum = inNode->left->data;
        inNode = inNode->left;
    }
    return minimum;
}


template <class T>
Node<T>* BinaryTree<T>::inOrderPred(T inVal) {
	Node<T>* temp = root;
	while (temp->data != inVal) {
		if (temp->data > inVal) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
	temp = temp->left; //gets left subtree
	while (temp->right != nullptr) { //finds greatest value in left subtree
		temp = temp->right;
	}
	return temp;
}


template <class T>
int BinaryTree<T>::Balance(Node<T> *parent, Node<T> *child) {
    if (child == nullptr) {
        return 0;
    }

    int leftHeight = getHeight(child->left);
    int rightHeight = getHeight(child->right);

    if (leftHeight - rightHeight > 1) {
        if (child->left != nullptr) {
            if ( getHeight(child->left->left) >= getHeight(child->left->right) ) {
                rotateRight(parent, child);
            } else {
                rotateLR(parent, child);
            }
        }
    } else if (rightHeight - leftHeight > 1) {
        if (child-> right != nullptr) {
            if (getHeight(child->right->right) >= getHeight(child->right->left)) {
                rotateLeft(parent, child);
            } else {
                rotateRL(parent, child);
            }
        }
    }

    if (child->left != nullptr) {
        Balance(child, child->left);
    }
    if (child->right != nullptr) {
        Balance(child, child->right);
    }

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}


//Print all Nodes, showing children
template <class T>
void BinaryTree<T>::displayTree(Node<T> *place) {
    if (place == nullptr) {
        //Check if root is null
        return;
    }

    std::cout << place->data << "(";

    if (place->left == nullptr) {
        //Check if left child is null
        std::cout << "-";
    } else {
        std::cout << place->left->data;
    }

    std::cout << ",";

    if (place->right == nullptr) {
        //Check if right child is null
        std::cout << "-";
    } else {
        std::cout << place->right->data;
    }

    std::cout << ")" << std::endl;

    displayTree(place->left);
    displayTree(place->right);
}

template<class T>
int BinaryTree<T>::getBF(Node<T>* parent) {
	return (getHeight(parent->left) - getHeight(parent->right));
}

//Base Template
//template class BinaryTree<Int>;