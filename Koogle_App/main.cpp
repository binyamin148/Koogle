#include "Crawler/inc/download.hpp"
#include "Crawler/inc/parser.hpp"
#include "Crawler/inc/indexer.hpp"
#include <unordered_map>
#include <iostream>

int main() {
    std::string url = "https://en.wikipedia.org/wiki/Harry_Potter_(film_series)";
    std::string html_content = Download::download_html(url);

    std::cout << "Downloaded HTML content: " << std::endl;
    std::cout << html_content << std::endl;

    std::vector<std::string> urls;
    std::vector<std::string> words;

    HtmlParser::parse_html(html_content, urls, words);

    std::cout << "Extracted URLs:" << std::endl;
    for (const auto& extracted_url : urls) {
        std::cout << extracted_url << std::endl;
    }

    std::cout << "Extracted Words:" << std::endl;
    for (const auto& word : words) {
        std::cout << word << std::endl;
    }

    // Use Indexer to index words
    std::unordered_map<std::string, size_t> word_frequency = Indexer::index(words);
    std::cout << "Word Frequencies:" << std::endl;
    for (const auto& entry : word_frequency) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    return 0;
}