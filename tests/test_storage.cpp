// tests/test_storage.cpp
#include "adaptq/storage_backend.h"
#include <cassert>
#include <iostream>
#include <memory>

void test_contiguous_storage() {
    const size_t test_capacity = 1024; // 1KB test allocation
    
    std::unique_ptr<adaptq::IStorageBackend> storage = 
        std::make_unique<adaptq::ContiguousStorageBackend>(test_capacity);
    
    // Verify capacity behavior
    assert(storage->get_capacity() == test_capacity && "Capacity mismatch");
    assert(storage->get_size() == 0 && "Initial size should be 0");
    
    // Verify memory allocation exists
    assert(storage->get_data_ptr() != nullptr && "Data pointer should not be null");
    
    std::cout << "test_contiguous_storage: PASS\n";
}

int main() {
    std::cout << "Running Storage Backend Unit Tests...\n";
    
    test_contiguous_storage();
    
    std::cout << "All storage tests passed.\n";
    return 0;
}
