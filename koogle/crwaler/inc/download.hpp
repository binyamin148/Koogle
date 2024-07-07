#ifndef DOWNLOAD_HPP
#define DOWNLOAD_HPP

#include <vector>
#include <string>

/**
 * @class Download
 * @brief A class to handle downloading HTML content from a URL.
 */
class Download
{
public:
    /**
     * @brief Default constructor for Download.
     */
    Download() = default;

    /**
     * @brief Default destructor for Download.
     */
    ~Download() = default;

    /**
     * @brief Downloads HTML content from the specified URL.
     *
     * This function takes a URL as input, performs an HTTP GET request, 
     * and returns the HTML content of the response as a string.
     *
     * @param url The URL from which to download HTML content.
     * @return A string containing the HTML content of the response.
     */
    static std::string download_html(const std::string &url);
};

#endif
