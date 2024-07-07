#ifndef WORKER_HPP
#define WORKER_HPP

#include "./queue.hpp"
#include "../inc/my_queue.hpp"
#include "./db_manager.hpp"
#include "./set.hpp"

#include <iostream>

/**
 * @class Worker
 * @brief A worker class to handle downloading and processing web pages.
 *
 * This class provides functionality to download web pages, extract URLs and
 * words, and store the extracted data. It uses a multi-level queue to manage
 * the URLs to be processed and a set to keep track of processed URLs.
 */
class Worker
{
private:
    MyQueue<std::string> m_queue;  ///< Multi-level queue for managing URLs.
    Set<std::string> m_set;        ///< Set to keep track of processed URLs.
    size_t m_max_depth;            ///< Maximum depth for URL processing.
    DBManager m_storing;           ///< Database manager for storing extracted data.

    /**
     * @brief Handles new URLs extracted from the current web page.
     *
     * This function checks if the extracted URLs should be added to the queue
     * for further processing, based on the current depth and the root URL.
     *
     * @param urls The vector of extracted URLs.
     * @param depth The current depth of URL processing.
     */
    void handle_new_urls(std::vector<std::string> urls, const size_t depth);

public:
    /**
     * @brief Default constructor for Worker.
     */
    Worker();

    /**
     * @brief Default destructor for Worker.
     */
    ~Worker();

    /**
     * @brief The main work function for processing URLs.
     *
     * This function pops URLs from the queue, downloads the corresponding web
     * pages, extracts URLs and words, and stores the extracted data. It continues
     * until a special stop signal (POISON_APPLE) is encountered.
     */
    void work();
};

#endif
