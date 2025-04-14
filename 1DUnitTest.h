#ifndef __1DUNITTEST__
#define __1DUNITTEST__


#include "HashTable1D.h"

void Test1DInsert() {
    std::cout << "\n----- Testing Insert Function -----" << std::endl;
    HashTable1D table;
    int checksCount;
    
    // Test 1: Insert into empty table
    try {
        checksCount = table.Insert(42);
        std::cout << "Test 1 PASSED: Inserted 42, checks: " << checksCount << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Couldn't insert into empty table: ";
        e.displayError();
    }
    
    // Test 2: Insert at collision location
    try {
        // Insert a value that will hash to the same location as 42
        int collidingValue = 42 + MAXSIZE1;
        checksCount = table.Insert(collidingValue);
        std::cout << "Test 2 PASSED: Inserted " << collidingValue << " with collision, checks: " << checksCount << std::endl;
        if (checksCount > 1) {
            std::cout << "   Collision handling confirmed (checks > 1)" << std::endl;
        }
    } catch(Exception &e) {
        std::cout << "Test 2 FAILED: Couldn't handle collision: ";
        e.displayError();
    }
    
    // Test 3: Insert many values to test distribution
    try {
        int totalChecks = 0;
        for (int i = 1; i <= 50; i++) {
            totalChecks += table.Insert(i * 100);
        }
        std::cout << "Test 3 PASSED: Inserted 50 values, avg checks: " << (totalChecks/50.0) << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 3 FAILED: Error during bulk insertion: ";
        e.displayError();
    }
    
    // Test 4: Try to insert when table is full
	try {
		// Create a new table for this test
		HashTable1D fullTable;
		
		std::cout << "   Test 4: Filling table to capacity..." << std::endl;
		int insertedCount = 0;
		
		// Fill the table completely (MAXSIZE1 unique values)
		for (int i = 0; i < MAXSIZE1; i++) {
			try {
				// Use values that hash to different indices to avoid excessive collisions
				fullTable.Insert(i);
				insertedCount++;
			} catch(Exception &e) {
				std::cout << "   Unexpected error after " << insertedCount << " insertions: ";
				e.displayError();
				break;
			}
		}
		
		std::cout << "   Successfully inserted " << insertedCount << " values" << std::endl;
		
		// Now try to insert one more value - this should fail
		try {
			fullTable.Insert(MAXSIZE1 + 1);
			std::cout << "   Test 4 FAILED: Was able to insert into a full table" << std::endl;
		} catch(Exception &e) {
			std::cout << "   Test 4 PASSED: Correctly rejected insertion into full table: ";
			e.displayError();
		}
		
	} catch(Exception &e) {
		std::cout << "   Test 4 FAILED: Unexpected error: ";
		e.displayError();
	}
}

void Test1DFind() {
    std::cout << "\n----- Testing Find Function -----" << std::endl;
    HashTable1D table;
    int checksCount;
    
    // Prepare table with some values
    table.Insert(100);
    table.Insert(200);
    table.Insert(300);
    table.Insert(100 + MAXSIZE1); // Will cause collision with 100
    
    // Test 1: Find existing value
    try {
        checksCount = table.Find(200);
        std::cout << "Test 1 PASSED: Found 200, checks: " << checksCount << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Couldn't find existing value: ";
        e.displayError();
    }
    
    // Test 2: Find value after collision
    try {
        checksCount = table.Find(100 + MAXSIZE1);
        std::cout << "Test 2 PASSED: Found colliding value, checks: " << checksCount << std::endl;
        if (checksCount > 1) {
            std::cout << "   Collision handling confirmed (checks > 1)" << std::endl;
        }
    } catch(Exception &e) {
        std::cout << "Test 2 FAILED: Couldn't find value after collision: ";
        e.displayError();
    }
    
    // Test 3: Try to find a non-existent value
    try {
        checksCount = table.Find(999);
        std::cout << "Test 3 FAILED: Found non-existent value" << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 3 PASSED: Correctly threw exception for non-existent value" << std::endl;
    }
}

void Test1DRemove() {
    std::cout << "\n----- Testing Remove Function -----" << std::endl;
    HashTable1D table;
    int checksCount;
    
    // Prepare table with some values
    table.Insert(100);
    table.Insert(200);
    table.Insert(300);
    table.Insert(100 + MAXSIZE1); // Will cause collision with 100
    
    // Test 1: Remove existing value
    try {
        checksCount = table.Remove(200);
        std::cout << "Test 1 PASSED: Removed 200, checks: " << checksCount << std::endl;
        
        // Verify it's actually removed
        try {
            table.Find(200);
            std::cout << "   FAILED: Value still found after removal" << std::endl;
        } catch(Exception &e) {
            std::cout << "   Removal confirmed: Value not found after removal" << std::endl;
        }
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Couldn't remove existing value: ";
        e.displayError();
    }
    
    // Test 2: Remove value after collision
    try {
        checksCount = table.Remove(100 + MAXSIZE1);
        std::cout << "Test 2 PASSED: Removed colliding value, checks: " << checksCount << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 2 FAILED: Couldn't remove value after collision: ";
        e.displayError();
    }
    
    // Test 3: Try to remove a non-existent value
    try {
        checksCount = table.Remove(999);
        std::cout << "Test 3 FAILED: Removed non-existent value" << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 3 PASSED: Correctly threw exception for non-existent value" << std::endl;
    }
}

void Test1DCombinedOperations() {
    std::cout << "\n----- Testing Combined Operations -----" << std::endl;
    HashTable1D table;
    
    // Test sequence: Insert, Remove, Insert at same location
    try {
        int value = 123;
        table.Insert(value);
        table.Remove(value);
        table.Insert(value);
        std::cout << "Test 1 PASSED: Could re-insert after deletion" << std::endl;
        
        // Make sure we can find it
        try {
            table.Find(value);
            std::cout << "   Confirmed: Re-inserted value is findable" << std::endl;
        } catch(Exception &e) {
            std::cout << "   FAILED: Re-inserted value not found" << std::endl;
        }
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Error during insert-remove-insert sequence: ";
        e.displayError();
    }
    
    // Test sequence: Insert at collision locations, remove middle one, find last one
    try {
        int base = 456;
        table.Insert(base);
        table.Insert(base + MAXSIZE1);
        table.Insert(base + 2*MAXSIZE1);
        
        table.Remove(base + MAXSIZE1);
        
        try {
            table.Find(base + 2*MAXSIZE1);
            std::cout << "Test 2 PASSED: Found value after collision chain with deletion" << std::endl;
        } catch(Exception &e) {
            std::cout << "Test 2 FAILED: Couldn't find value after collision chain with deletion: ";
            e.displayError();
        }
    } catch(Exception &e) {
        std::cout << "Test 2 FAILED: Error during collision chain test: ";
        e.displayError();
    }
}

#endif