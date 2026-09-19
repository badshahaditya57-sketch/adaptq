// tests/test_policy.cpp
#include "adaptq/policy.h"
#include <cassert>
#include <iostream>
#include <memory>

void test_default_policy() {
    // Verify allocation and interface resolution
    std::unique_ptr<adaptq::IPolicy> policy = std::make_unique<adaptq::DefaultPolicy>();
    
    // Verify baseline fixed-bit behavior remains unchanged
    assert(policy->get_bit_width() == 8 && "DefaultPolicy must preserve 8-bit baseline");
    
    std::cout << "test_default_policy: PASS\n";
}

int main() {
    std::cout << "Running Policy Unit Tests...\n";
    
    test_default_policy();
    
    std::cout << "All policy tests passed.\n";
    return 0;
}
