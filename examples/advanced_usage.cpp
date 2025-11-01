/**
 * @file advanced_usage.cpp
 * @brief Ví dụ nâng cao - Performance, move semantics, và complex scenarios
 */

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "advance/store/include/advance_store.hpp"

// Performance measurement helper
class Timer {
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}
    
    double elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end - start).count();
    }
};

class Product {
    std::string m_name;
    double m_price;
    int m_quantity;
    
public:
    Product(std::string name, double price, int qty) 
        : m_name(std::move(name)), m_price(price), m_quantity(qty) {}
    
    // Move constructor
    Product(Product&& other) noexcept 
        : m_name(std::move(other.m_name)), m_price(other.m_price), m_quantity(other.m_quantity) {}
    
    // Getters
    const std::string& name() const { return m_name; }
    double price() const { return m_price; }
    int quantity() const { return m_quantity; }
    double value() const { return m_price * m_quantity; }
    
    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << p.m_name << "[$" << p.m_price << " x " << p.m_quantity << " = $" << p.value() << "]";
        return os;
    }
};

int main() {
    std::cout << "=== ADVANCED STORE USAGE ===\n\n";
    
    // 1. PERFORMANCE COMPARISON: Store vs Vector
    std::cout << "1. PERFORMANCE COMPARISON:\n";
    
    const size_t DATA_SIZE = 100000;
    
    // Test with std::vector
    {
        Timer t;
        std::vector<int> vec;
        for (size_t i = 0; i < DATA_SIZE; ++i) {
            vec.push_back(i % 100);
        }
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        std::cout << "   Vector time: " << t.elapsed() << " ms\n";
    }
    
    // Test with Store
    {
        Timer t;
        adv::Store<int> store;
        for (size_t i = 0; i < DATA_SIZE; ++i) {
            store.push_back(i % 100);
        }
        store.sort().unique();
        std::cout << "   Store time: " << t.elapsed() << " ms\n";
    }
    
    // 2. COMPLEX DATA PROCESSING PIPELINE
    std::cout << "\n2. INVENTORY MANAGEMENT SYSTEM:\n";
    
    adv::Store<Product> inventory = {
        Product("Laptop", 999.99, 10),
        Product("Mouse", 25.50, 50),
        Product("Keyboard", 75.00, 30),
        Product("Monitor", 299.99, 15),
        Product("Headphones", 149.99, 25),
        Product("Tablet", 399.99, 8)
    };
    
    std::cout << "   Full inventory:\n   ";
    inventory.print(true);
    
    // Complex pipeline: filter, transform, sort
    auto valuable_stock = inventory.filter([](const Product& p) {
                            return p.value() > 2000; // High value items
                         })
                         .sort([](const Product& a, const Product& b) {
                            return a.value() > b.value(); // Sort by total value desc
                         });
    
    std::cout << "   High-value items (value > $2000):\n   ";
    valuable_stock.print(true);
    
    // 3. MOVE SEMANTICS AND EFFICIENCY
    std::cout << "\n3. MOVE SEMANTICS DEMONSTRATION:\n";
    
    // Create large store
    adv::Store<std::string> large_data;
    for (int i = 0; i < 1000; ++i) {
        large_data.emplace_back("String_" + std::to_string(i));
    }
    
    std::cout << "   Original size: " << large_data.size() << "\n";
    
    // Move construction - efficient
    adv::Store<std::string> moved_data = std::move(large_data);
    std::cout << "   After move:\n";
    std::cout << "   Original size: " << large_data.size() << "\n";
    std::cout << "   Moved size: " << moved_data.size() << "\n";
    
    // 4. ADVANCED ITERATOR USAGE
    std::cout << "\n4. ADVANCED ITERATOR PATTERNS:\n";
    
    adv::Store<int> complex_data = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    // Using const iterators for read-only access
    std::cout << "   Reverse iteration: ";
    for (auto it = complex_data.rbegin(); it != complex_data.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // STL algorithm compatibility
    auto sum = std::accumulate(complex_data.begin(), complex_data.end(), 0);
    auto count_above_50 = std::count_if(complex_data.begin(), complex_data.end(), 
                                       [](int x) { return x > 50; });
    
    std::cout << "   STL algorithms:\n";
    std::cout << "   Sum: " << sum << "\n";
    std::cout << "   Count > 50: " << count_above_50 << "\n";
    
    // 5. ERROR HANDLING AND SAFETY
    std::cout << "\n5. ERROR HANDLING:\n";
    
    adv::Store<int> empty_store;
    
    try {
        // This should throw
        auto front = empty_store.front();
        std::cout << "   Front: " << front << "\n";
    } catch (const std::exception& e) {
        std::cout << "   Caught exception: " << e.what() << "\n";
    }
    
    // Safe access with bounds checking
    try {
        auto value = empty_store.at(5); // Out of bounds
    } catch (const std::out_of_range& e) {
        std::cout << "   Bounds check: " << e.what() << "\n";
    }
    
    // 6. MEMORY MANAGEMENT
    std::cout << "\n6. MEMORY MANAGEMENT:\n";
    
    adv::Store<int> memory_demo;
    std::cout << "   Initial - Size: " << memory_demo.size() 
              << ", Capacity: " << memory_demo.capacity() << "\n";
    
    memory_demo.reserve(100);
    std::cout << "   After reserve(100) - Size: " << memory_demo.size()
              << ", Capacity: " << memory_demo.capacity() << "\n";
    
    for (int i = 0; i < 50; ++i) {
        memory_demo.push_back(i);
    }
    std::cout << "   After adding 50 elements - Size: " << memory_demo.size()
              << ", Capacity: " << memory_demo.capacity() << "\n";
    
    memory_demo.shrink_to_fit();
    std::cout << "   After shrink_to_fit - Size: " << memory_demo.size()
              << ", Capacity: " << memory_demo.capacity() << "\n";
    
    return 0;
}