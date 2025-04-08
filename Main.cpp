#include <iostream>
#include <string>
#include <random>

#include"Node.h"
#include"Exceptions.h"
#include"BinaryTree.h"
#include"HashTable2D.h"
#include"HashTable1D.h"

BinaryTree<int> TestNums;
HashTable2D TwoDHash;
HashTable1D OneDHash; //placeholder


int main() {
	//generate 100 random unique intergers
	std::string placeholder = "This is a placeholder for now";

	int randomSeed = 0;
	srand(randomSeed);
	int numCount = 0;
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
		numCount++;
	}
	//randnum unit test:
	int arrCounter = 0;
	int TestNumsArr[100];
	int *AscendPointer = TestNums.GetAllAscending(TestNums.getRoot(), arrCounter, TestNumsArr);
	
	for (int i = 0; i < TestNums.getSize(); i++) {
		TestNumsArr[i] = AscendPointer[i];
		std::cout << TestNumsArr[i] << std::endl;
	}
	std::cout << "Numbers generated: "<< numCount << std::endl;

	//insert the first 50 value in both structures. 
	//	KEEP TRACK of how many slots you have to check--then record this value (how?)
	for (int i = 0; i < 50; i++) {
		TwoDHash.Insert(TestNumsArr[i]);
		OneDHash.Insert(TestNumsArr[i]);
		std::cout << "Added " << TestNumsArr[i] << " to the data structure." << std::endl;
		//This is all kinda a placeholder for now. I am not quite sure if having i as a parameter for find will work
	}
	std::cout << "Number of slots checked to insert: " << placeholder << std::endl;
	
    OneDHash.Print();
    TwoDHash.Print();
	//Remove all items from the data structure where the index of the value in the main function % 7 = 0.
	//	KEEP TRACK of how many slots you have to check--then record this value (how?)
	for (int i = 0; i < 50; i++) {
		if (i % 7 == 0) {
			TwoDHash.Remove(TestNumsArr[i]);
			OneDHash.Remove(TestNumsArr[i]);
			std::cout << "Removed " << TestNumsArr[i] << " from the data structure." << std::endl;
		}
	}
	std::cout << "Number of slots checked to delete: " << placeholder << std::endl;

	//Insert the remaining 50 values from both data structures. record the running number of spots checked to remove
	for (int i = 50; i < 100; i++) {
		TwoDHash.Insert(TestNumsArr[i]);
		OneDHash.Insert(TestNumsArr[i]);
		std::cout << "Added " << TestNumsArr[i] << " to the data structure." << std::endl;
	}
	std::cout << "Number of slots checked to insert: " << placeholder << std::endl;

    
	return 0;
}
