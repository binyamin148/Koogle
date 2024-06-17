#include "../inc/parser.hpp"

#include <regex>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cctype>
#include <htmlcxx/html/ParserDom.h>

void Parser::remove_punctuation(std::string &word)
{
    word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
}

std::vector<std::string> Parser::extract_url(const std::string &str)
{
    std::vector<std::string> urls;
    std::regex regex_pattern(R"(<a href=\"(https?://[^\"]+)\")");
    std::smatch match;

    std::string::const_iterator search_start(str.cbegin());
    while (std::regex_search(search_start, str.cend(), match, regex_pattern))
    {
        urls.push_back(match[1].str());
        search_start = match.suffix().first;
    }
    return urls;
}

std::vector<std::string> Parser::extract_words(const std::string &str)
{
    std::vector<std::string> words;
    htmlcxx::HTML::ParserDom parser;
    auto dom = parser.parseTree(str);

    std::set<std::string> non_visible_tags = {"style", "script", "noscript", "meta", "link"};

    for (auto it = dom.begin(); it != dom.end(); ++it)
    {
        if (it->isTag() && non_visible_tags.find(it->tagName()) != non_visible_tags.end())
        {
            it.skip_children();
        }
        else if (!it->isTag() && !it->isComment())
        {
            std::istringstream iss(it->text());
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