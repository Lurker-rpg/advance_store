#pragma once
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <string>
#include <stdexcept>
#include <type_traits>

namespace adv
{
using std::cout;
using std::endl;
using std::initializer_list;
using std::ostream;
using std::size_t;
using std::string;
using std::vector;

// =======================
// Error Management Class
// =======================
class Errors
{
  public:
	/// @brief Throws out_of_range exception
	[[noreturn]] inline void throw_out_of_range() const
	{
		throw std::out_of_range("Error: Out of range");
	}

	/// @brief Throws invalid_argument exception
	[[noreturn]] inline void throw_invalid_argument() const
	{
		throw std::invalid_argument("Error: Invalid argument");
	}

	/// @brief Throws runtime_error exception
	[[noreturn]] inline void throw_runtime_error() const
	{
		throw std::runtime_error("Error: Runtime error");
	}
};

// =======================
// Store Template Class
// =======================
template <typename T>
class Store
{
  private:
	vector<T> m_data;	   // Internal storage
	static Errors s_error; // Error management

  public:
	// =======================
	// Constructors & Destructor
	// =======================

	/// @brief Default constructor
	Store() = default;

	/// @brief Constructor with size
	/// @param size Initial size of the store
	explicit Store(size_t size) : m_data(size) {}

	/// @brief Constructor with initializer list
	/// @param list Initializer list of elements
	Store(initializer_list<T> list) : m_data(list) {}

	/// @brief Constructor with iterator range
	/// @tparam Iterator Iterator type
	/// @param begin Start iterator
	/// @param end End iterator
	template <typename Iterator>
	Store(Iterator begin, Iterator end) : m_data(begin, end) {}

	/// @brief Constructor with range
	/// @tparam Range Range type
	/// @param range Input range
	template <typename Range>
	explicit Store(const Range &range) : m_data(range.begin(), range.end()) {}

	/// @brief Move assignment operator
	/// @param other Other store to move from
	/// @return Reference to this store
	Store &operator+=(Store<T> &&other)
	{
		m_data.insert(m_data.end(),
					  std::make_move_iterator(other.m_data.begin()),
					  std::make_move_iterator(other.m_data.end()));
		return *this;
	}

	// =======================
	// Element Access
	// =======================

	/// @brief Access element with bounds checking
	/// @param pos Position to access
	/// @return Reference to element at position
	/// @throws std::out_of_range if position is invalid
	T &at(size_t pos)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range();
		}
		return m_data[pos];
	}

	/// @brief Const access element with bounds checking
	/// @param pos Position to access
	/// @return Const reference to element at position
	/// @throws std::out_of_range if position is invalid
	const T &at(size_t pos) const
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range();
		}
		return m_data[pos];
	}

	/// @brief Access element without bounds checking
	/// @param pos Position to access
	/// @return Reference to element at position
	T &operator[](size_t pos) noexcept
	{
		return m_data[pos];
	}

	/// @brief Const access element without bounds checking
	/// @param pos Position to access
	/// @return Const reference to element at position
	const T &operator[](size_t pos) const noexcept
	{
		return m_data[pos];
	}

	/// @brief Get first element
	/// @return Const reference to first element
	/// @throws std::out_of_range if store is empty
	const T &front() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		return m_data.front();
	}

	/// @brief Get middle element
	/// @return Const reference to middle element
	/// @throws std::out_of_range if store is empty
	const T &mid() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		return m_data[m_data.size() / 2];
	}

	/// @brief Get last element
	/// @return Const reference to last element
	/// @throws std::out_of_range if store is empty
	const T &back() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		return m_data.back();
	}

	/// @brief Get maximum element
	/// @return Const reference to maximum element
	/// @throws std::out_of_range if store is empty
	const T &max() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		return *std::max_element(m_data.begin(), m_data.end());
	}

	/// @brief Get minimum element
	/// @return Const reference to minimum element
	/// @throws std::out_of_range if store is empty
	const T &min() const
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		return *std::min_element(m_data.begin(), m_data.end());
	}

	/// @brief Get raw pointer to data
	/// @return Pointer to underlying data array
	T *data() noexcept
	{
		return m_data.data();
	}

	/// @brief Get const raw pointer to data
	/// @return Const pointer to underlying data array
	const T *data() const noexcept
	{
		return m_data.data();
	}

	// =======================
	// Capacity
	// =======================

	/// @brief Get current size
	/// @return Number of elements in store
	size_t size() const noexcept
	{
		return m_data.size();
	}

	/// @brief Check if store is empty
	/// @return true if store is empty, false otherwise
	bool empty() const noexcept
	{
		return m_data.empty();
	}

	/// @brief Get capacity
	/// @return Current capacity of the store
	size_t capacity() const noexcept
	{
		return m_data.capacity();
	}

	// =======================
	// Conversion Operators
	// =======================

	/// @brief Convert to vector
	/// @return Vector containing store elements
	operator vector<T>() const
	{
		return m_data;
	}

	// =======================
	// Iterators
	// =======================
	auto begin() noexcept { return m_data.begin(); }
	auto end() noexcept { return m_data.end(); }
	auto begin() const noexcept { return m_data.begin(); }
	auto end() const noexcept { return m_data.end(); }
	auto cbegin() const noexcept { return m_data.cbegin(); }
	auto cend() const noexcept { return m_data.cend(); }
	auto rbegin() noexcept { return m_data.rbegin(); }
	auto rend() noexcept { return m_data.rend(); }
	auto rbegin() const noexcept { return m_data.rbegin(); }
	auto rend() const noexcept { return m_data.rend(); }

	// =======================
	// Basic Operations
	// =======================

	/// @brief Reserve capacity
	/// @param new_capacity New capacity to reserve
	void reserve(size_t new_capacity)
	{
		m_data.reserve(new_capacity);
	}

	/// @brief Resize store
	/// @param new_size New size of store
	void resize(size_t new_size)
	{
		m_data.resize(new_size);
	}

	/// @brief Clear all elements
	void clear() noexcept
	{
		m_data.clear();
	}

	/// @brief Shrink capacity to fit size
	void shrink_to_fit()
	{
		m_data.shrink_to_fit();
	}

	/// @brief Remove first element
	/// @throws std::out_of_range if store is empty
	void pop_front()
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		m_data.erase(m_data.begin());
	}

	/// @brief Remove last element
	/// @throws std::out_of_range if store is empty
	void pop_back()
	{
		if (m_data.empty())
		{
			s_error.throw_out_of_range();
		}
		m_data.pop_back();
	}

	/// @brief Remove element at position
	/// @param pos Position to remove
	/// @throws std::out_of_range if position is invalid
	void remove_at(size_t pos)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range();
		}
		m_data.erase(m_data.begin() + pos);
	}

	/// @brief Insert element at position
	/// @param pos Position to insert at
	/// @param value Value to insert
	/// @throws std::out_of_range if position is invalid
	void insert(size_t pos, const T &value)
	{
		if (pos > m_data.size())
		{
			s_error.throw_out_of_range();
		}
		m_data.insert(m_data.begin() + pos, value);
	}

	/// @brief Replace element at position
	/// @param pos Position to replace
	/// @param value New value
	/// @throws std::out_of_range if position is invalid
	void replace_at(size_t pos, const T &value)
	{
		if (pos >= m_data.size())
		{
			s_error.throw_out_of_range();
		}
		m_data[pos] = value;
	}

	/// @brief Replace all occurrences of a value
	/// @param old_value Value to replace
	/// @param new_value New value
	void replace_all(const T &old_value, const T &new_value)
	{
		std::replace(m_data.begin(), m_data.end(), old_value, new_value);
	}

	/// @brief Fill store with value
	/// @param value Value to fill with
	void fill(const T &value)
	{
		std::fill(m_data.begin(), m_data.end(), value);
	}

	/// @brief Reverse elements in store
	void reverse()
	{
		std::reverse(m_data.begin(), m_data.end());
	}

	/// @brief Swap contents with another store
	/// @param other Store to swap with
	void swap(Store<T> &other) noexcept
	{
		m_data.swap(other.m_data);
	}

	/// @brief Print store contents
	/// @param new_line Whether to print newline at the end
	void print(bool new_line = false) const
	{
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			cout << m_data[i];
			if (i < m_data.size() - 1)
			{
				cout << " ";
			}
		}
		if (new_line)
		{
			cout << '\n';
		}
	}

	// =======================
	// Adding Elements
	// =======================

	/// @brief Add container to front
	/// @tparam Container Container type
	/// @param container Container to add
	template <typename Container>
	void push_front(const Container &container)
	{
		m_data.insert(m_data.begin(), container.begin(), container.end());
	}

	/// @brief Add initializer list to front
	/// @param list Initializer list to add
	void push_front(initializer_list<T> list)
	{
		m_data.insert(m_data.begin(), list.begin(), list.end());
	}

	/// @brief Add value to front
	/// @param value Value to add
	void push_front(const T &value)
	{
		m_data.insert(m_data.begin(), value);
	}

	/// @brief Add moved value to front
	/// @param value Value to move
	void push_front(T &&value)
	{
		m_data.insert(m_data.begin(), std::move(value));
	}

	/// @brief Add container to back
	/// @tparam Container Container type
	/// @param container Container to add
	template <typename Container>
	void push_back(const Container &container)
	{
		m_data.insert(m_data.end(), container.begin(), container.end());
	}

	/// @brief Add initializer list to back
	/// @param list Initializer list to add
	void push_back(initializer_list<T> list)
	{
		m_data.insert(m_data.end(), list.begin(), list.end());
	}

	/// @brief Add value to back
	/// @param value Value to add
	void push_back(const T &value)
	{
		m_data.push_back(value);
	}

	/// @brief Add moved value to back
	/// @param value Value to move
	void push_back(T &&value)
	{
		m_data.push_back(std::move(value));
	}

	/// @brief Emplace element at back
	/// @tparam Args Argument types
	/// @param args Arguments to construct element
	template <typename... Args>
	void emplace_back(Args &&... args)
	{
		m_data.emplace_back(std::forward<Args>(args)...);
	}

	/// @brief Emplace element at front
	/// @tparam Args Argument types
	/// @param args Arguments to construct element
	template <typename... Args>
	void emplace_front(Args &&... args)
	{
		m_data.emplace(m_data.begin(), std::forward<Args>(args)...);
	}

	// =======================
	// Search & Check
	// =======================

	/// @brief Check if store contains value
	/// @param value Value to search for
	/// @return true if value found, false otherwise
	bool contains(const T &value) const
	{
		return std::find(m_data.begin(), m_data.end(), value) != m_data.end();
	}

	/// @brief Check if any element satisfies predicate
	/// @tparam Pred Predicate type
	/// @param pred Predicate function
	/// @return true if any element satisfies predicate
	template <typename Pred>
	bool any_of(Pred pred) const
	{
		return std::any_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Check if any element equals value
	/// @param value Value to compare
	/// @return true if any element equals value
	bool any_of(const T &value) const
	{
		return std::any_of(m_data.begin(), m_data.end(),
						   [&](const T &elem) { return elem == value; });
	}

	/// @brief Check if all elements satisfy predicate
	/// @tparam Pred Predicate type
	/// @param pred Predicate function
	/// @return true if all elements satisfy predicate
	template <typename Pred>
	bool all_of(Pred pred) const
	{
		return std::all_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Check if all elements equal value
	/// @param value Value to compare
	/// @return true if all elements equal value
	bool all_of(const T &value) const
	{
		return std::all_of(m_data.begin(), m_data.end(),
						   [&](const T &elem) { return elem == value; });
	}

	/// @brief Check if no elements satisfy predicate
	/// @tparam Pred Predicate type
	/// @param pred Predicate function
	/// @return true if no elements satisfy predicate
	template <typename Pred>
	bool none_of(Pred pred) const
	{
		return std::none_of(m_data.begin(), m_data.end(), pred);
	}

	/// @brief Check if no elements equal value
	/// @param value Value to compare
	/// @return true if no elements equal value
	bool none_of(const T &value) const
	{
		return std::none_of(m_data.begin(), m_data.end(),
							[&](const T &elem) { return elem == value; });
	}

	/// @brief Find all positions of value
	/// @param value Value to find
	/// @return Vector of positions where value appears
	vector<size_t> find_all(const T &value) const
	{
		vector<size_t> positions;
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			if (m_data[i] == value)
			{
				positions.push_back(i);
			}
		}
		return positions;
	}

	/// @brief Find all positions satisfying predicate
	/// @tparam Pred Predicate type
	/// @param pred Predicate function
	/// @return Vector of positions satisfying predicate
	template <typename Pred>
	vector<size_t> find_all_if(Pred pred) const
	{
		vector<size_t> positions;
		for (size_t i = 0; i < m_data.size(); ++i)
		{
			if (pred(m_data[i]))
			{
				positions.push_back(i);
			}
		}
		return positions;
	}

	// =======================
	// Transformation & Filtering
	// =======================

	/// @brief Transform elements in-place
	/// @tparam Func Function type
	/// @param func Transformation function
	template <typename Func>
	void transform(Func func)
	{
		std::transform(m_data.begin(), m_data.end(), m_data.begin(), func);
	}

	/// @brief Filter elements based on predicate
	/// @tparam Pred Predicate type
	/// @param pred Predicate function
	/// @return New store with filtered elements
	template <typename Pred>
	Store<T> filter(Pred pred) const
	{
		Store<T> result;
		for (const auto &elem : m_data)
		{
			if (pred(elem))
			{
				result.push_back(elem);
			}
		}
		return result;
	}

	// =======================
	// Sorting
	// =======================

	/// @brief Sort elements
	/// @param ascending Whether to sort in ascending order (default true)
	void sort(bool ascending = true)
	{
		if (ascending)
		{
			std::sort(m_data.begin(), m_data.end());
		}
		else
		{
			std::sort(m_data.begin(), m_data.end(), std::greater<T>());
		}
	}

	/// @brief Sort with custom comparator
	/// @tparam Compare Comparator type
	/// @param comp Comparator function
	template <typename Compare>
	void sort(Compare comp)
	{
		std::sort(m_data.begin(), m_data.end(), comp);
	}

	/// @brief Remove duplicate elements
	/// @param auto_sort Whether to sort before removing duplicates
	void unique(bool auto_sort = true)
	{
		if (auto_sort)
		{
			sort();
		}
		auto it = std::unique(m_data.begin(), m_data.end());
		m_data.erase(it, m_data.end());
	}

	// =======================
	// Type Conversion
	// =======================

	/// @brief Convert to store of integers
	/// @tparam U Original type (deduced)
	/// @return New store with integer values
	template <typename U = T>
	Store<int> to_int() const
	{
		static_assert(std::is_arithmetic_v<U> || std::is_same_v<U, string>,
					  "Type must be arithmetic or string for conversion to int");

		if (m_data.empty())
		{
			s_error.throw_runtime_error();
		}

		Store<int> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<U, string>)
			{
				try
				{
					result.push_back(std::stoi(val));
				}
				catch (...)
				{
					result.push_back(0);
				}
			}
			else
			{
				result.push_back(static_cast<int>(val));
			}
		}
		return result;
	}

	/// @brief Convert to store of doubles
	/// @tparam U Original type (deduced)
	/// @return New store with double values
	template <typename U = T>
	Store<double> to_double() const
	{
		static_assert(std::is_arithmetic_v<U> || std::is_same_v<U, string>,
					  "Type must be arithmetic or string for conversion to double");

		if (m_data.empty())
		{
			s_error.throw_runtime_error();
		}

		Store<double> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<U, string>)
			{
				try
				{
					result.push_back(std::stod(val));
				}
				catch (...)
				{
					result.push_back(0.0);
				}
			}
			else
			{
				result.push_back(static_cast<double>(val));
			}
		}
		return result;
	}

	/// @brief Convert to store of characters
	/// @tparam U Original type (deduced)
	/// @return New store with character values
	template <typename U = T>
	Store<char> to_char() const
	{
		static_assert(std::is_arithmetic_v<U> || std::is_same_v<U, string>,
					  "Type must be arithmetic or string for conversion to char");

		if (m_data.empty())
		{
			s_error.throw_runtime_error();
		}

		Store<char> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_same_v<U, string>)
			{
				if (!val.empty())
				{
					result.push_back(val[0]);
				}
				else
				{
					result.push_back('\0');
				}
			}
			else
			{
				result.push_back(static_cast<char>(val));
			}
		}
		return result;
	}

	/// @brief Convert to store of strings
	/// @tparam U Original type (deduced)
	/// @return New store with string values
	template <typename U = T>
	Store<string> to_string() const
	{
		if (m_data.empty())
		{
			s_error.throw_runtime_error();
		}

		Store<string> result;
		for (const auto &val : m_data)
		{
			if constexpr (std::is_arithmetic_v<U>)
			{
				result.push_back(std::to_string(val));
			}
			else if constexpr (std::is_same_v<U, char>)
			{
				result.push_back(string(1, val));
			}
			else if constexpr (std::is_same_v<U, string>)
			{
				result.push_back(val);
			}
			else
			{
				// For other types, use string stream
				std::ostringstream oss;
				oss << val;
				result.push_back(oss.str());
			}
		}
		return result;
	}
};

// =======================
// Static Member Initialization
// =======================
template <typename T>
Errors Store<T>::s_error;

} // namespace adv