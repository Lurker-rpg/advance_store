/**
 * @file mini_real_world.cpp
 * @brief Ví dụ thực tế - Quản lý danh sách với Store Mini
 */

#include <iostream>
#include <string>
#include "advance/store/include/advance_store_mini.hpp"

struct Student {
    std::string name;
    int score;
    
    Student(std::string n, int s) : name(n), score(s) {}
    
    // For printing
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << s.name << "(" << s.score << ")";
        return os;
    }
    
    // For comparison
    bool operator>(const Student& other) const { return score > other.score; }
    bool operator<(const Student& other) const { return score < other.score; }
};

int main() {
    std::cout << "=== STORE MINI - REAL WORLD EXAMPLE ===\n\n";
    
    // 1. QUẢN LÝ ĐIỂM SINH VIÊN
    adv::Store<Student> students = {
        Student("Alice", 85),
        Student("Bob", 92),
        Student("Charlie", 78),
        Student("Diana", 95)
    };
    
    std::cout << "1. STUDENT MANAGEMENT:\n";
    std::cout << "   All students: ";
    students.print(true);
    
    // Thêm sinh viên mới - ƯU ÁI push_front
    students.push_front(Student("Eve", 88));
    std::cout << "   After adding Eve at front: ";
    students.print(true);
    
    // 2. PHÂN TÍCH ĐIỂM
    std::cout << "\n2. SCORE ANALYSIS:\n";
    
    // Tìm highest/lowest score
    auto highest = students.max();
    auto lowest = students.min();
    std::cout << "   Highest score: " << highest.name << " - " << highest.score << "\n";
    std::cout << "   Lowest score: " << lowest.name << " - " << lowest.score << "\n";
    
    // Sắp xếp theo điểm
    students.sort(false); // descending by score
    std::cout << "   Rank by score (desc): ";
    students.print(true);
    
    // 3. QUẢN LÝ CÔNG VIỆC (TODO LIST)
    adv::Store<std::string> todo_list;
    
    // Thêm task - push_front cho task mới nhất lên đầu
    todo_list.push_front("Code review");
    todo_list.push_front("Write documentation");
    todo_list.push_front("Fix bug #123");
    todo_list.push_back("Meeting with team"); // push_back cho task ít quan trọng
    
    std::cout << "\n3. TODO LIST:\n";
    std::cout << "   Current tasks: ";
    todo_list.print(true);
    
    // Hoàn thành task - xóa từ đầu
    std::cout << "   Completing front task: " << todo_list.front() << "\n";
    todo_list.pop_front();
    std::cout << "   Remaining tasks: ";
    todo_list.print(true);
    
    // 4. QUẢN LÝ SẢN PHẨM
    adv::Store<double> prices = {19.99, 29.99, 15.50, 45.75, 12.25};
    
    std::cout << "\n4. PRICE MANAGEMENT:\n";
    std::cout << "   Original prices: ";
    prices.print(true);
    
    std::cout << "   Price stats:\n";
    std::cout << "   Highest price: $" << prices.max() << "\n";
    std::cout << "   Lowest price: $" << prices.min() << "\n";
    std::cout << "   Average price: $" << prices.average() << "\n";
    std::cout << "   Total value: $" << prices.sum() << "\n";
    
    // Giảm giá 10% cho tất cả sản phẩm
    for (size_t i = 0; i < prices.size(); ++i) {
        prices[i] *= 0.9; // 10% discount
    }
    
    std::cout << "   After 10% discount: ";
    prices.print(true);
    
    // 5. LỊCH SỬ TRUY CẬP (Recent items)
    adv::Store<std::string> recent_items;
    
    // Thêm item mới vào đầu (push_front)
    recent_items.push_front("Homepage");
    recent_items.push_front("Settings");
    recent_items.push_front("Profile");
    recent_items.push_front("Dashboard");
    
    std::cout << "\n5. RECENT ITEMS (push_front demo):\n";
    std::cout << "   Recent items (newest first): ";
    recent_items.print(true);
    
    // Giới hạn lịch sử - xóa item cũ nhất (pop_back)
    while (recent_items.size() > 3) {
        recent_items.pop_back();
    }
    std::cout << "   After limiting to 3 items: ";
    recent_items.print(true);
    
    return 0;
}