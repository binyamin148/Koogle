#include "../inc/download.hpp"

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/**
 * @brief Downloads HTML content from the specified URL.
 *
 * This function takes a URL as input, performs an HTTP GET request, 
 * and returns the HTML content of the response as a string.
 * It uses the cURLpp library to handle the HTTP request and response.
 *
 * @param url The URL from which to download HTML content.
 * @return A string containing the HTML content of the response. 
 *         If an error occurs, an empty string is returned.
 */
std::string Download::download_html(const std::string &url)
{
    std::ostringstream html_os; // Output string stream to store HTML content

    try
    {
        curlpp::Cleanup cleaner; // Ensures proper cleanup of cURLpp resources
        curlpp::Easy request;    // Create a request object

        // Set the URL for the request
        request.setOpt(new curlpp::options::Url(url));

        // Set the output stream to capture the HTML content
        request.setOpt(new curlpp::options::WriteStream(&html_os));
        
        // Perform the request
        request.perform();

        // Return the HTML content as a string
        return html_os.str();
    }
    catch (curlpp::RuntimeError &e)
    {
        // Handle runtime errors (e.g., network issues)
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    catch (curlpp::LogicError &e)
    {
        // Handle logic errors (e.g., invalid cURL options)
        std::cerr << "Logic error: " << e.what() << std::endl;
    }

    // Return an empty string in case of an error
    return "";
}
