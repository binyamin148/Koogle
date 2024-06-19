#ifndef HTML_PARSER_HPP
#define HTML_PARSER_HPP

#include <string>
#include <vector>
#include <gumbo.h>

class HtmlParser {
public:
    static void extract_urls(GumboNode* node, std::vector<std::string>& urls);
    static void extract_text(GumboNode* node, std::string& output);
    static std::vector<std::string> split_words(const std::string& text);
    static void parse_html(const std::string& html, std::vector<std::string>& urls, std::vector<std::string>& words);
};

#endif // HTML_PARSER_HPP
