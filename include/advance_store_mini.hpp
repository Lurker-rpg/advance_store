#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

namespace adv {

template <typename T>
class Store {
private:
    std::vector<T> m_data;

public:
    // =======================
    // Constructors
    // =======================
    Store() = default;
    
    explicit Store(size_t size) : m_data(size) {}
    
    Store(std::initializer_list<T> list) : m_data(list) {}
    
    template <typename Iterator>
    Store(Iterator begin, Iterator end) : m_data(begin, end) {}
    
    template <typename Container>
    explicit Store(const Container& container) : m_data(container.begin(), container.end()) {}

    // =======================
    // Element Access
    // =======================
    T& operator[](size_t pos) { return m_data[pos]; }
    const T& operator[](size_t pos) const { return m_data[pos]; }
    
    T& at(size_t pos) { return m_data.at(pos); }
    const T& at(size_t pos) const { return m_data.at(pos); }
    
    T& front() { return m_data.front(); }
    const T& front() const { return m_data.front(); }
    
    T& back() { return m_data.back(); }
    const T& back() const { return m_data.back(); }
    
    T* data() { return m_data.data(); }
    const T* data() const { return m_data.data(); }

    // =======================
    // Capacity
    // =======================
    size_t size() const { return m_data.size(); }
    bool empty() const { return m_data.empty(); }
    size_t capacity() const { return m_data.capacity(); }
    
    void reserve(size_t new_capacity) { m_data.reserve(new_capacity); }
    void resize(size_t new_size) { m_data.resize(new_size); }
    void shrink_to_fit() { m_data.shrink_to_fit(); }

    // =======================
    // Modifiers - Basic
    // =======================
    void clear() { m_data.clear(); }
    
    // *** SỰ ƯU ÁI - CÓ push_front/pop_front ***
    void push_front(const T& value) { 
        m_data.insert(m_data.begin(), value); 
    }
    
    void push_front(T&& value) { 
        m_data.insert(m_data.begin(), std::move(value)); 
    }
    
    void pop_front() { 
        if (!m_data.empty()) {
            m_data.erase(m_data.begin()); 
        }
    }
    
    void push_back(const T& value) { m_data.push_back(value); }
    void push_back(T&& value) { m_data.push_back(std::move(value)); }
    
    void pop_back() { m_data.pop_back(); }
    
    template <typename... Args>
    void emplace_back(Args&&... args) {
        m_data.emplace_back(std::forward<Args>(args)...);
    }
    
    template <typename... Args>
    void emplace_front(Args&&... args) {
        m_data.emplace(m_data.begin(), std::forward<Args>(args)...);
    }

    // =======================
    // Utility Functions
    // =======================
    
    /// @brief Get maximum element
    const T& max() const {
        return *std::max_element(m_data.begin(), m_data.end());
    }
    
    /// @brief Get minimum element  
    const T& min() const {
        return *std::min_element(m_data.begin(), m_data.end());
    }
    
    /// @brief Get middle element
    const T& mid() const {
        return m_data[m_data.size() / 2];
    }
    
    /// @brief Check if contains value
    bool contains(const T& value) const {
        return std::find(m_data.begin(), m_data.end(), value) != m_data.end();
    }
    
    /// @brief Fill with value
    void fill(const T& value) {
        std::fill(m_data.begin(), m_data.end(), value);
    }
    
    /// @brief Reverse elements
    void reverse() {
        std::reverse(m_data.begin(), m_data.end());
    }
    
    /// @brief Sort elements
    void sort(bool ascending = true) {
        if (ascending) {
            std::sort(m_data.begin(), m_data.end());
        } else {
            std::sort(m_data.begin(), m_data.end(), std::greater<T>());
        }
    }
    
    /// @brief Sort with custom comparator
    template <typename Compare>
    void sort(Compare comp) {
        std::sort(m_data.begin(), m_data.end(), comp);
    }
    
    /// @brief Remove duplicates (requires sorted)
    void unique() {
        auto it = std::unique(m_data.begin(), m_data.end());
        m_data.erase(it, m_data.end());
    }
    
    /// @brief Remove element at position
    void remove_at(size_t pos) {
        if (pos < m_data.size()) {
            m_data.erase(m_data.begin() + pos);
        }
    }
    
    /// @brief Insert element at position
    void insert(size_t pos, const T& value) {
        if (pos <= m_data.size()) {
            m_data.insert(m_data.begin() + pos, value);
        }
    }
    
    /// @brief Replace all occurrences
    void replace_all(const T& old_value, const T& new_value) {
        std::replace(m_data.begin(), m_data.end(), old_value, new_value);
    }
    
    /// @brief Calculate sum of elements
    T sum() const {
        return std::accumulate(m_data.begin(), m_data.end(), T{});
    }
    
    /// @brief Calculate average
    double average() const {
        if (m_data.empty()) return 0.0;
        return static_cast<double>(sum()) / m_data.size();
    }

    // =======================
    // Search Operations
    // =======================
    
    /// @brief Find first occurrence
    int find(const T& value) const {
        auto it = std::find(m_data.begin(), m_data.end(), value);
        return (it != m_data.end()) ? std::distance(m_data.begin(), it) : -1;
    }
    
    /// @brief Count occurrences of value
    size_t count(const T& value) const {
        return std::count(m_data.begin(), m_data.end(), value);
    }
    
    /// @brief Check if any element satisfies predicate
    template <typename Pred>
    bool any(Pred pred) const {
        return std::any_of(m_data.begin(), m_data.end(), pred);
    }
    
    /// @brief Check if all elements satisfy predicate  
    template <typename Pred>
    bool all(Pred pred) const {
        return std::all_of(m_data.begin(), m_data.end(), pred);
    }

    // =======================
    // Conversion & Output
    // =======================
    
    /// @brief Convert to std::vector
    operator std::vector<T>() const {
        return m_data;
    }
    
    /// @brief Print elements
    void print(bool new_line = false) const {
        for (size_t i = 0; i < m_data.size(); ++i) {
            std::cout << m_data[i];
            if (i < m_data.size() - 1) std::cout << " ";
        }
        if (new_line) std::cout << "\n";
    }

    // =======================
    // Iterators
    // =======================
    auto begin() { return m_data.begin(); }
    auto end() { return m_data.end(); }
    auto begin() const { return m_data.begin(); }
    auto end() const { return m_data.end(); }
    auto rbegin() { return m_data.rbegin(); }
    auto rend() { return m_data.rend(); }
    auto rbegin() const { return m_data.rbegin(); }
    auto rend() const { return m_data.rend(); }
};

} // namespace adv