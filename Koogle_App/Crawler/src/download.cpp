#include "../inc/download.hpp"

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/**
 * @brief Downloads HTML content from the specified URL.
 * @param url The URL to download the HTML content from.
 * @return The downloaded HTML content as a string.
 * @throws curlpp::RuntimeError if a runtime error occurs during the download.
 * @throws curlpp::LogicError if a logic error occurs during the download.
 */
std::string Download::download_html(const std::string& url)
{
    // Object to store the downloaded data
    std::ostringstream html_os;

    try
    {
        // Initialize and clean up curlpp when this object goes out of scope
        curlpp::Cleanup cleaner;

        // Create an easy request for the download
        curlpp::Easy request;
        
        // Set the URL option for the request
        request.setOpt(new curlpp::options::Url(url));

        // Set the write stream option to store the downloaded data
        request.setOpt(new curlpp::options::WriteStream(&html_os));

        // Perform the download request
        request.perform();

        // Return the HTML content as a string
        return html_os.str();
    }
    catch (curlpp::RuntimeError& e)
    {
        // Handle runtime error
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError& e)
    {
        // Handle logic error
        std::cerr << "Logic error: " << e.what() << std::endl;
    }

    // Return an empty string in case of an error
    return "";
}
