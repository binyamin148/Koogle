#include "../inc/crawler.hpp"
#include "../inc/settings.hpp"
#include <iostream>

/**
 * @brief Constructor for Crawler class.
 */
Crawler::Crawler()
{
}

/**
 * @brief Destructor for Crawler class.
 */
Crawler::~Crawler() = default;

/**
 * @brief Initiates the crawling process.
 *
 * Creates multiple threads, each executing the work function of the Worker class.
 */
void Crawler::work()
{
    // Create threads for workers
    for (size_t i = 0; i < Settings::NUM_THREADS; i++)
    {
        m_threads.push_back(std::thread([this]
                                        { m_worker.work(); }));
    }

    // Join all threads
    for (auto &thread : m_threads)
    {
        thread.join();
    }
}
