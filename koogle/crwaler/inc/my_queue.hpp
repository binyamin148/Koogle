#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include "./settings.hpp"

#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <vector>

/**
 * @class MyQueue
 * @brief A thread-safe multi-level queue.
 *
 * This class provides a thread-safe implementation of a multi-level queue using
 * vectors of queues. It uses condition variables to handle synchronization between
 * threads and supports a special task when all threads are waiting.
 *
 * @tparam T The type of elements stored in the queues.
 */
template <typename T>
class MyQueue
{
private:
    std::vector<std::queue<T>> m_queue;   ///< Vector of queues for multi-level storage.
    mutable std::mutex mtx;               ///< Mutex for synchronizing access to the queues.
    std::condition_variable cond_not_empty; ///< Condition variable for waiting when the queue is empty.
    std::condition_variable cond_not_full;  ///< Condition variable for waiting when the queue is full.

    size_t size_threads_waiting = 0;      ///< Counter for the number of waiting threads.

    /**
     * @brief Checks if all the queues are empty.
     *
     * @return True if all queues are empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Helper function to pop an element from the front of the non-empty queue.
     *
     * @param e The element to pop.
     * @param index The index of the queue from which the element was popped.
     * @return True if an element was popped, false otherwise.
     */
    bool help_front_pop(T &e, size_t &index);

public:
    /**
     * @brief Default constructor for MyQueue.
     */
    MyQueue();

    /**
     * @brief Default destructor for MyQueue.
     */
    ~MyQueue();

    /**
     * @brief Pushes an element onto the specified queue.
     *
     * This function adds a new element to the queue at the specified depth.
     *
     * @param e The element to push onto the queue.
     * @param depth The depth (index) of the queue to push the element into.
     */
    void push(T const &e, const size_t &depth);

    /**
     * @brief Pops an element from the front of the queue.
     *
     * This function removes an element from the front of the first non-empty
     * queue. If all queues are empty, it will wait until an element is available.
     *
     * @param e The element to pop from the queue.
     * @param index The index of the queue from which the element was popped.
     * @return True if an element was popped, false otherwise.
     */
    bool pop(T &e, size_t &index);

    /**
     * @brief Performs a special task when all threads are waiting.
     *
     * This function pushes a special element (POISON_APPLE) into the first queue
     * when all threads are waiting, signaling them to stop.
     */
    void special_task();

    /**
     * @brief Checks if all threads are waiting and triggers the special task if so.
     *
     * This function checks if the number of waiting threads equals the total number
     * of threads and calls special_task if true.
     */
    void check_finish();
};

template <typename T>
MyQueue<T>::MyQueue()
    : m_queue(1) // Initialize with one empty queue
{
}

template <typename T>
MyQueue<T>::~MyQueue()
{
}

template <typename T>
void MyQueue<T>::push(T const &e, const size_t &depth)
{
    std::unique_lock<std::mutex> g{mtx};

    if (depth >= m_queue.size())
    {
        m_queue.resize(depth + 1);
    }

    m_queue[depth].push(e);
    cond_not_empty.notify_one();
}

template <typename T>
bool MyQueue<T>::pop(T &e, size_t &index)
{
    std::unique_lock<std::mutex> g{mtx};
    size_threads_waiting++;
    this->check_finish();
    cond_not_empty.wait(g, [this]
                        { return !this->empty(); });
    size_threads_waiting--;

    if (this->help_front_pop(e, index))
    {
        cond_not_full.notify_one();
        return true;
    }
    return false;
}

template <typename T>
bool MyQueue<T>::empty() const
{
    for (const auto &q : m_queue)
    {
        if (!q.empty())
            return false;
    }
    return true;
}

template <typename T>
bool MyQueue<T>::help_front_pop(T &e, size_t &index)
{
    for (size_t i = 0; i < m_queue.size(); ++i)
    {
        if (!m_queue[i].empty())
        {
            e = m_queue[i].front();
            index = i;
            m_queue[i].pop();
            return true;
        }
    }
    return false;
}

template <typename T>
void MyQueue<T>::special_task()
{
    for (size_t i = 0; i < 10; ++i)
    {
        m_queue[0].push(Settings::POISON_APPLE);
    }
}

template <typename T>
void MyQueue<T>::check_finish()
{
    if (size_threads_waiting == Settings::NUM_THREADS)
    {
        this->special_task();
        cond_not_empty.notify_all();
    }
}

#endif
