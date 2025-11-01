/**
 * @file basic_usage.cpp
 * @brief Ví dụ cơ bản - Làm quen với Store container
 */

#include <iostream>
#include "advance/store/include/advance_store.hpp"

int main() {
    std::cout << "=== BASIC STORE USAGE ===\n\n";
    
    // 1. Khởi tạo cơ bản
    adv::Store<int> numbers = {5, 2, 8, 1, 9, 2, 5};
    std::cout << "1. Original numbers: ";
    numbers.print(true);
    
    // 2. Truy cập phần tử
    std::cout << "2. Element access:\n";
    std::cout << "   First: " << numbers.front() << "\n";
    std::cout << "   Middle: " << numbers.mid() << "\n"; 
    std::cout << "   Last: " << numbers.back() << "\n";
    std::cout << "   Max: " << numbers.max() << "\n";
    std::cout << "   Min: " << numbers.min() << "\n";
    
    // 3. Thêm/xóa phần tử
    numbers.push_back(10);
    numbers.push_front(0);
    std::cout << "3. After adding 0 front, 10 back: ";
    numbers.print(true);
    
    numbers.pop_front();
    numbers.remove_at(2);
    std::cout << "4. After pop_front & remove_at(2): ";
    numbers.print(true);
    
    // 4. Tìm kiếm
    std::cout << "5. Search operations:\n";
    std::cout << "   Contains 8: " << std::boolalpha << numbers.contains(8) << "\n";
    std::cout << "   Contains 99: " << numbers.contains(99) << "\n";
    
    auto positions = numbers.find_all(2);
    std::cout << "   Positions of '2': ";
    for (auto pos : positions) std::cout << pos << " ";
    std::cout << "\n";
    
    // 5. Sắp xếp và unique
    numbers.sort(true); // ascending
    std::cout << "6. Sorted ascending: ";
    numbers.print(true);
    
    numbers.unique();
    std::cout << "7. After removing duplicates: ";
    numbers.print(true);
    
    // 6. Kiểm tra điều kiện
    std::cout << "8. Condition checks:\n";
    std::cout << "   Any > 5: " << numbers.any_of([](int x) { return x > 5; }) << "\n";
    std::cout << "   All > 0: " << numbers.all_of([](int x) { return x > 0; }) << "\n";
    std::cout << "   None < 0: " << numbers.none_of([](int x) { return x < 0; }) << "\n";
    
    return 0;
}