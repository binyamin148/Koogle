#include "Crawler/inc/download.hpp"
#include "Crawler/inc/parser.hpp"
#include <iostream>

int main()
{
    std::string url = "https://en.wikipedia.org/wiki/Harry_Potter_(film_series)";
    std::string html_content = Download::download_html(url);

    std::cout << "Downloaded HTML content: " << std::endl;
    std::cout << html_content << std::endl;

    std::vector<std::string> urls = Parser::extract_url(html_content);
    std::cout << "Extracted URLs:" << std::endl;
    for (const auto &extracted_url : urls)
    {
        std::cout << extracted_url << std::endl;
    }

    std::vector<std::string> words = Parser::extract_words(html_content);
    std::cout << "Extracted Words:" << std::endl;
    for (const auto &word : words)
    {
        std::cout << word << std::endl;
    }

    return 0;
}