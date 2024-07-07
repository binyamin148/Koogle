#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <string>

/**
 * @class Parser
 * @brief A class to parse HTML content and extract specific data.
 */
class Parser
{
private:
    /**
     * @brief Removes punctuation from the given word.
     *
     * This function modifies the input string by removing punctuation
     * characters from the beginning and end of the word.
     *
     * @param word The word from which to remove punctuation.
     */
    static void remove_punctuation(std::string &word);

public:
    /**
     * @brief Default constructor for Parser.
     */
    Parser() = default;

    /**
     * @brief Default destructor for Parser.
     */
    ~Parser() = default;

    /**
     * @brief Extracts URLs from the given HTML string.
     *
     * This function searches for anchor tags in the HTML string and extracts
     * the URLs from the href attributes.
     *
     * @param str The HTML string to parse.
     * @return A vector of strings containing the extracted URLs.
     */
    static std::vector<std::string> extract_url(const std::string &str);

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
    static std::vector<std::string> extract_words(const std::string &str);
};

#endif
