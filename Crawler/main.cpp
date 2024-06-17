#include "./inc/download.hpp"
#include <iostream>

int main() {
    std::string url = "https://en.wikipedia.org/wiki/Harry_Potter";
    std::string html_content = Download::download_html(url);

    std::cout << "Downloaded HTML content: " << std::endl;
    std::cout << html_content << std::endl;

    return 0;
}