#include <iostream>
#include <string>
#include <random>

#include"Node.h"
#include"Exceptions.h"
#include"BinaryTree.h"
#include"2DHashTable.h"
#include"HashTable1D.h"

BinaryTree<int> TestNums;
HashTable2D TwoDHash;


int main() {
	//generate 100 random unique intergers

	int randomSeed = 0;
	srand(randomSeed);
	for (int i = 0; i < 100; i++) {
		int newNum = rand();
		if (TestNums.Find(newNum, TestNums.getRoot()) == -1) {
			//if the number isnt in the list
			//insert the number into the list
			TestNums.Insert(newNum, TestNums.getRoot());
		}
		else {
			//if the number is in the list
			//do nothing
			while (TestNums.Find(newNum, TestNums.getRoot()) != -1) {
				newNum = rand(); //generate a new number
			}
			TestNums.Insert(newNum, TestNums.getRoot());
		}
	}
		
	//insert the first 50 value in both structures. 
	//	KEEP TRACK of how many slots you have to check--then record this value (how?)
	
	//REmove all items from the data structure where the index of the value in the main function % 7 = 0.
	//	KEEP TRACK of how many slots you have to check--then record this value (how?)
	
	//Insert the remaining 50 values from both data structures. record the running number of spots checked to remove


	return 0;
}
