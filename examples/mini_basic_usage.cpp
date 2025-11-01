/**
 * @file mini_basic_usage.cpp 
 * @brief Ví dụ cơ bản - Store Mini như vector nâng cao
 */

#include <iostream>
#include <string>
#include "advance/store/include/advance_store_mini.hpp"

int main() {
    std::cout << "=== STORE MINI - BASIC USAGE ===\n\n";
    
    // 1. Khởi tạo
    adv::Store<int> numbers = {10, 20, 30};
    std::cout << "1. Initial: ";
    numbers.print(true);
    
    // 2. SỰ ƯU ÁI - push_front/pop_front (vector thường không có)
    std::cout << "2. Using push_front/pop_front:\n";
    numbers.push_front(5);    // Thêm đầu
    numbers.push_front(1);    // Thêm đầu  
    std::cout << "   After push_front(5), push_front(1): ";
    numbers.print(true);
    
    numbers.pop_front();      // Xóa đầu
    std::cout << "   After pop_front(): ";
    numbers.print(true);
    
    numbers.push_back(40);    // Thêm cuối
    std::cout << "   After push_back(40): ";
    numbers.print(true);
    
    // 3. Utility functions
    std::cout << "3. Utility functions:\n";
    std::cout << "   Max: " << numbers.max() << "\n";
    std::cout << "   Min: " << numbers.min() << "\n"; 
    std::cout << "   Mid: " << numbers.mid() << "\n";
    std::cout << "   Sum: " << numbers.sum() << "\n";
    std::cout << "   Average: " << numbers.average() << "\n";
    
    // 4. Tìm kiếm và đếm
    std::cout << "4. Search operations:\n";
    std::cout << "   Contains 20: " << std::boolalpha << numbers.contains(20) << "\n";
    std::cout << "   Contains 99: " << numbers.contains(99) << "\n";
    std::cout << "   Position of 20: " << numbers.find(20) << "\n";
    std::cout << "   Count of 20: " << numbers.count(20) << "\n";
    
    // 5. Sắp xếp và thao tác
    std::cout << "5. Sorting and manipulation:\n";
    numbers.sort(false); // descending
    std::cout << "   Sorted descending: ";
    numbers.print(true);
    
    numbers.reverse();
    std::cout << "   After reverse: ";
    numbers.print(true);
    
    numbers.fill(100);
    std::cout << "   After fill(100): ";
    numbers.print(true);
    
    return 0;
}