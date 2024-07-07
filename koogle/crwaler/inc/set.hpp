#ifndef SET_HPP
#define SET_HPP

#include <set>
#include <mutex>

/**
 * @class Set
 * @brief A thread-safe set.
 *
 * This class provides a thread-safe implementation of a set using a mutex to
 * synchronize access.
 *
 * @tparam T The type of elements stored in the set.
 */
template <typename T>
class Set
{
private:
    std::set<T> m_set;          ///< The underlying set.
    mutable std::mutex mtx;     ///< Mutex for synchronizing access to the set.

public:
    /**
     * @brief Default constructor for Set.
     */
    Set();

    /**
     * @brief Default destructor for Set.
     */
    ~Set();

    /**
     * @brief Inserts an element into the set.
     *
     * This function adds a new element to the set.
     *
     * @param e The element to insert.
     */
    void insert(T const &e);

    /**
     * @brief Checks if an element is in the set.
     *
     * This function checks if a given element is present in the set.
     *
     * @param e The element to check.
     * @return True if the element is found, false otherwise.
     */
    bool contains(T const &e) const;
};

template <typename T>
Set<T>::Set()
{
}

template <typename T>
Set<T>::~Set()
{
}

template <typename T>
void Set<T>::insert(T const &e)
{
    std::unique_lock<std::mutex> g{mtx};
    m_set.insert(e);
}

template <typename T>
bool Set<T>::contains(T const &e) const
{
    std::unique_lock<std::mutex> g{mtx};
    return m_set.find(e) != m_set.end();
}

#endif
