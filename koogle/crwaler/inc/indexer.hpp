#ifndef INDEXER_HPP
#define INDEXER_HPP

#include <vector>
#include <string>
#include <unordered_map>

/**
 * @class Indexer
 * @brief A class for indexing strings.
 *
 * This class provides functionality to create a frequency map (unordered_map)
 * from a vector of strings.
 */
class Indexer
{
public:
    Indexer() = default;
    ~Indexer() = default;

    /**
     * @brief Indexes a vector of strings.
     *
     * This function creates a frequency map (unordered_map) from a vector of strings,
     * where the key is the string (word or URL) and the value is its frequency of occurrence.
     *
     * @param str_vec The vector of strings to index.
     * @return An unordered_map representing the frequency of each string in the input vector.
     */
    static std::unordered_map<std::string, size_t> index(std::vector<std::string> &str_vec);
};

#endif
