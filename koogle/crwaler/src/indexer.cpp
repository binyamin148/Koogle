#include "../inc/indexer.hpp"

/**
 * @brief Indexes a vector of strings.
 *
 * This function creates a frequency map (unordered_map) from a vector of strings,
 * where the key is the string (word or URL) and the value is its frequency of occurrence.
 *
 * @param str_vec The vector of strings to index.
 * @return An unordered_map representing the frequency of each string in the input vector.
 */
std::unordered_map<std::string, size_t> Indexer::index(std::vector<std::string> &str_vec)
{
    std::unordered_map<std::string, size_t> ump;
    for (auto &item : str_vec)
    {
        ump[item]++;
    }
    return ump;
}
