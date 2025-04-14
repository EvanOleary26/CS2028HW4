#ifndef __2DUNITTEST__
#define __2DUNITTEST__

#include "HashTable2D.h"

void Test2DInsert() {
    std::cout << "\n----- Testing 2D Hash Insert Function -----" << std::endl;
    HashTable2D table;
    int checksCount;
    
    // Test 1: Insert into empty table
    try {
        checksCount = table.Insert(42);
        std::cout << "Test 1 PASSED: Inserted 42, checks: " << checksCount << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Couldn't insert into empty table: ";
        e.displayError();
    }
    
    // Test 2: Insert at collision location (same row)
    try {
        // Insert a value that will hash to the same row as 42
        int collidingValue = 42 + MAXSIZE2;
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
        int successfulInserts = 0;
        
        for (int i = 1; i <= 50; i++) {
            try {
                totalChecks += table.Insert(i);  // These hash to rows 1-50
                successfulInserts++;
            } catch(Exception &e) {
                // Handle individual insertion errors if needed
            }
        }
        
        if (successfulInserts > 0) {
            std::cout << "Test 3 PASSED: Inserted " << successfulInserts << " values, avg checks: " 
                      << (totalChecks/(double)successfulInserts) << std::endl;
        } else {
            std::cout << "Test 3 FAILED: Couldn't insert any values" << std::endl;
        }
    } catch(Exception &e) {
        std::cout << "Test 3 FAILED: Unexpected error during bulk insertion: ";
        e.displayError();
    }
    
    // Test 4: Try to fill a row to capacity
    try {
        // Create a new table for this test
        HashTable2D rowFullTable;
        
        std::cout << "   Test 4: Filling a single row to capacity..." << std::endl;
        int targetRow = 7; // Pick a specific row to fill
        int insertedCount = 0;
        
        // Fill the row completely (ARRAYSIZE values)
        for (int i = 0; i < ARRAYSIZE; i++) {
            try {
                // Create values that all hash to the target row
                int value = targetRow + (i * MAXSIZE2);
                rowFullTable.Insert(value);
                insertedCount++;
            } catch(Exception &e) {
                std::cout << "   Unexpected error after " << insertedCount << " insertions: ";
                e.displayError();
                break;
            }
        }
        
        std::cout << "   Successfully inserted " << insertedCount << " values into row " << targetRow << std::endl;
        
        // Now try to insert one more value in the same row - this should fail
        try {
            int oneMoreValue = targetRow + (ARRAYSIZE * MAXSIZE2);
            rowFullTable.Insert(oneMoreValue);
            std::cout << "   Test 4 FAILED: Was able to insert into a full row" << std::endl;
        } catch(Exception &e) {
            std::cout << "   Test 4 PASSED: Correctly rejected insertion into full row: ";
            e.displayError();
        }
        
    } catch(Exception &e) {
        std::cout << "   Test 4 FAILED: Unexpected error: ";
        e.displayError();
    }
}

void Test2DFind() {
    std::cout << "\n----- Testing 2D Hash Find Function -----" << std::endl;
    HashTable2D table;
    int checksCount;
    
    // Prepare table with some values
    int row1 = 25;
    int value1 = row1; // Will hash to row 25
    table.Insert(value1);
    
    int value2 = 50; // Will hash to row 50
    table.Insert(value2);
    
    int value3 = value1 + MAXSIZE2; // Will hash to same row as value1 (row 25)
    table.Insert(value3);
    
    // Test 1: Find existing value
    try {
        checksCount = table.Find(value2);
        std::cout << "Test 1 PASSED: Found " << value2 << ", checks: " << checksCount << std::endl;
    } catch(Exception &e) {
        std::cout << "Test 1 FAILED: Couldn't find existing value: ";
        e.displayError();
    }
    
    // Test 2: Find value after collision
    try {
        checksCount = table.Find(value3);
        std::cout << "Test 2 PASSED: Found colliding value " << value3 << ", checks: " << checksCount << std::endl;
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

void Test2DRemove() {
    std::cout << "\n----- Testing 2D Hash Remove Function -----" << std::endl;
    HashTable2D table;
    int checksCount;
    
    // Prepare table with some values
    int value1 = 100;
    table.Insert(value1);
    
    int value2 = 200;
    table.Insert(value2);
    
    int value3 = value1 + MAXSIZE2; // Will hash to same row as value1
    table.Insert(value3);
    
    // Test 1: Remove existing value
    try {
        checksCount = table.Remove(value2);
        std::cout << "Test 1 PASSED: Removed " << value2 << ", checks: " << checksCount << std::endl;
        
        // Verify it's actually removed
        try {
            table.Find(value2);
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
        checksCount = table.Remove(value3);
        std::cout << "Test 2 PASSED: Removed colliding value " << value3 << ", checks: " << checksCount << std::endl;
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

void Test2DCombinedOperations() {
    std::cout << "\n----- Testing 2D Hash Combined Operations -----" << std::endl;
    HashTable2D table;
    
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
        int baseValue = 456;
        int row = baseValue % MAXSIZE2;
        int value1 = baseValue;
        int value2 = row + MAXSIZE2; // Same row, next column
        int value3 = row + (2 * MAXSIZE2); // Same row, third column
        
        table.Insert(value1);
        table.Insert(value2);
        table.Insert(value3);
        
        table.Remove(value2); // Remove the middle one
        
        try {
            table.Find(value3); // Should still be able to find the last one
            std::cout << "Test 2 PASSED: Found value after collision chain with deletion" << std::endl;
        } catch(Exception &e) {
            std::cout << "Test 2 FAILED: Couldn't find value after collision chain with deletion: ";
            e.displayError();
        }
    } catch(Exception &e) {
        std::cout << "Test 2 FAILED: Error during collision chain test: ";
        e.displayError();
    }
    
    // Test 3: The performance difference between edge placement and center placement
    try {
        HashTable2D performanceTable;
        int centerRow = MAXSIZE2 / 2;
        int edgeRow = 0;
        int checksCenter = 0;
        int checksEdge = 0;
        
        // Fill half of center row
        for (int i = 0; i < ARRAYSIZE / 2; i++) {
            performanceTable.Insert(centerRow + (i * MAXSIZE2));
        }
        
        // Fill half of edge row
        for (int i = 0; i < ARRAYSIZE / 2; i++) {
            performanceTable.Insert(edgeRow + (i * MAXSIZE2));
        }
        
        // Insert one more in each row
        checksCenter = performanceTable.Insert(centerRow + ((ARRAYSIZE / 2) * MAXSIZE2));
        checksEdge = performanceTable.Insert(edgeRow + ((ARRAYSIZE / 2) * MAXSIZE2));
        
        std::cout << "Test 3 INFO: Center row insertion checks: " << checksCenter << std::endl;
        std::cout << "Test 3 INFO: Edge row insertion checks: " << checksEdge << std::endl;
        
    } catch(Exception &e) {
        std::cout << "Test 3 FAILED: Error during performance test: ";
        e.displayError();
    }
}

#endif