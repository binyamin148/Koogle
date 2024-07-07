#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

/**
 * @class Queue
 * @brief A thread-safe queue with a maximum size.
 *
 * This class provides a thread-safe implementation of a queue with a specified
 * maximum size. It uses condition variables to handle synchronization between
 * threads.
 *
 * @tparam T The type of elements stored in the queue.
 */
template <typename T>
class Queue
{
public:
    /**
     * @brief Pushes an element onto the queue.
     *
     * This function adds a new element to the queue. If the queue is full, it
     * will wait until space is available.
     *
     * @param e The element to push onto the queue.
     */
    void push(T const &e);

    /**
     * @brief Pops an element from the queue.
     *
     * This function removes an element from the queue. If the queue is empty,
     * it will wait until an element is available.
     *
     * @param e The element to pop from the queue.
     * @return True if an element was popped, false otherwise.
     */
    bool pop(T &e);

private:
    std::queue<T> q;                         ///< The underlying queue.
    size_t max_size = 10000000;              ///< The maximum size of the queue.
    mutable std::mutex mtx;                  ///< Mutex for synchronizing access to the queue.
    std::condition_variable cond_not_empty;  ///< Condition variable for waiting when the queue is empty.
    std::condition_variable cond_not_full;   ///< Condition variable for waiting when the queue is full.
};

template <typename T>
void Queue<T>::push(T const &e)
{
    std::unique_lock<std::mutex> g{mtx};
    while (q.size() == max_size)
    {
        cond_not_full.wait(g);
    }

    q.push(e);
    cond_not_empty.notify_one();
}

template <typename T>
bool Queue<T>::pop(T &e)
{
    std::unique_lock<std::mutex> g{mtx};

    cond_not_empty.wait(g, [this]()
                        { return !q.empty(); });

    if (q.empty())
    {
        return false;
    }

    e = q.front();
    q.pop();
    cond_not_full.notify_one();

    return true;
}

#endif
