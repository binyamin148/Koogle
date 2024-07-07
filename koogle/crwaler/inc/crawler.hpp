#ifndef CRAWLER_HPP
#define CRAWLER_HPP

#include "worker.hpp"
#include <thread>
#include <vector>

/**
 * @class Crawler
 * @brief A class to manage crawling with multiple threads.
 *
 * This class creates and manages multiple worker threads to crawl and index web pages.
 */
class Crawler
{
private:
    Worker m_worker;                ///< The worker instance responsible for crawling.
    std::vector<std::thread> m_threads;  ///< Container for worker threads.

public:
    Crawler();          ///< Constructor.
    ~Crawler();         ///< Destructor.

    /**
     * @brief Initiates the crawling process.
     *
     * Creates multiple threads, each executing the work function of the Worker class.
     */
    void work();
};

#endif
