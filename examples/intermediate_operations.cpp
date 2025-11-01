/**
 * @file intermediate_operations.cpp  
 * @brief Ví dụ trung bình - Chuỗi operations và data processing
 */

#include <iostream>
#include <string>
#include "advance/store/include/advance_store.hpp"

struct Person {
    std::string name;
    int age;
    double salary;
    
    Person(std::string n, int a, double s) : name(n), age(a), salary(s) {}
    
    // For printing
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << p.name << "(" << p.age << ", $" << p.salary << ")";
        return os;
    }
    
    // For comparison
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

int main() {
    std::cout << "=== INTERMEDIATE STORE OPERATIONS ===\n\n";
    
    // 1. Data Processing Pipeline với numbers
    adv::Store<double> sales = {1200.5, 800.2, 1500.8, 900.1, 2000.5, 750.3};
    
    std::cout << "1. SALES DATA PROCESSING:\n";
    std::cout << "   Original: ";
    sales.print(true);
    
    auto high_sales = sales.filter([](double s) { return s > 1000; })
                          .transform([](double s) { return s * 1.1; }) // 10% increase
                          .sort(false); // descending
    
    std::cout << "   High sales (>1000) +10% desc: ";
    high_sales.print(true);
    
    // 2. String manipulations
    adv::Store<std::string> words = {"hello", "world", "programming", "cpp", "library", "algorithm"};
    
    std::cout << "\n2. TEXT PROCESSING:\n";
    auto processed_text = words.filter([](const std::string& s) { return s.length() > 4; })
                              .transform([](const std::string& s) {
                                  std::string result;
                                  for (char c : s) result += std::toupper(c);
                                  return result;
                              })
                              .sort();
    
    std::cout << "   Long words uppercase sorted: ";
    processed_text.print(true);
    
    // 3. Working with custom objects
    adv::Store<Person> employees = {
        Person("Alice", 25, 50000),
        Person("Bob", 30, 60000), 
        Person("Charlie", 35, 75000),
        Person("Diana", 28, 55000),
        Person("Eve", 40, 80000)
    };
    
    std::cout << "\n3. EMPLOYEE MANAGEMENT:\n";
    std::cout << "   All employees: ";
    employees.print(true);
    
    // Filter senior employees with good salary
    auto seniors = employees.filter([](const Person& p) { 
        return p.age > 30 && p.salary > 60000; 
    });
    
    std::cout << "   Seniors (age>30, salary>60k): ";
    seniors.print(true);
    
    // 4. Type conversions
    std::cout << "\n4. TYPE CONVERSIONS:\n";
    adv::Store<int> integers = {65, 66, 67, 97, 98, 99};
    
    std::cout << "   Integers: ";
    integers.print(true);
    
    std::cout << "   As chars: ";
    auto as_chars = integers.to_char();
    as_chars.print(true);
    
    std::cout << "   As strings: ";
    auto as_strings = integers.to_string();
    as_strings.print(true);
    
    // 5. Batch operations
    std::cout << "\n5. BATCH OPERATIONS:\n";
    adv::Store<int> data = {1, 2, 3, 4, 5};
    
    // Replace all 3s with 30s
    data.replace_all(3, 30);
    std::cout << "   After replace 3->30: ";
    data.print(true);
    
    // Fill with specific value
    data.fill(99);
    std::cout << "   After fill with 99: ";
    data.print(true);
    
    // Reverse
    data.reverse();
    std::cout << "   After reverse: ";
    data.print(true);
    
    return 0;
}