#include "../inc/parser.hpp"

#include <regex>
#include <iostream>
#include <string>
#include <sstream>

#include <htmlcxx/html/ParserDom.h>
#include <algorithm>
#include <cctype>

/**
 * @brief Extracts URLs from the given HTML string.
 *
 * This function searches for anchor tags in the HTML string and extracts
 * the URLs from the href attributes.
 *
 * @param str The HTML string to parse.
 * @return A vector of strings containing the extracted URLs.
 */
std::vector<std::string> Parser::extract_url(const std::string &str)
{
    std::vector<std::string> urls;
    std::string regex_str = "<a href=\"(https?://[^\"]+)\"";

    std::regex regex_pattern(regex_str);
    std::smatch match;

    std::string::const_iterator search_start(str.cbegin());
    while (std::regex_search(search_start, str.cend(), match, regex_pattern))
    {
        std::string url = match[1];
        urls.push_back(url);
        search_start = match.suffix().first;
    }
    return urls;
}

/**
 * @brief Extracts words from the given HTML string.
 *
 * This function parses the HTML string, ignoring content within non-visible
 * tags such as style, script, and meta, and extracts the visible text content
 * into a list of words.
 *
 * @param str The HTML string to parse.
 * @return A vector of strings containing the extracted words.
 */
std::vector<std::string> Parser::extract_words(const std::string &str)
{
    std::vector<std::string> words;

    htmlcxx::HTML::ParserDom parser;
    tree<htmlcxx::HTML::Node> dom = parser.parseTree(str);

    std::set<std::string> non_visible_tags = {"style", "script", "noscript", "meta", "link"};

    for (auto it = dom.begin(); it != dom.end(); ++it)
    {
        if (it->isTag() && non_visible_tags.find(it->tagName()) != non_visible_tags.end())
        {
            it.skip_children();
        }
        else if (!it->isTag() && !it->isComment())
        {
            std::string text = it->text();
            std::istringstream iss(text);
            std::string word;
            while (iss >> word)
            {
                remove_punctuation(word);
                if (!word.empty())
                {
                    words.push_back(word);
                }
            }
        }
    }

    return words;
}

/**
 * @brief Removes punctuation from the given word.
 *
 * This function modifies the input string by removing punctuation
 * characters from the beginning and end of the word.
 *
 * @param word The word from which to remove punctuation.
 */
void Parser::remove_punctuation(std::string &word)
{
    word.erase(word.begin(), std::find_if(word.begin(), word.end(), [](unsigned char ch)
                                          { return !std::ispunct(ch); }));
    word.erase(std::find_if(word.rbegin(), word.rend(), [](unsigned char ch)
                            { return !std::ispunct(ch); })
                   .base(),
               word.end());
}
