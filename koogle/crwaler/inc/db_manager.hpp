#ifndef STORING_HPP
#define STORING_HPP

#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>

#include <string>
#include <unordered_map>
#include <iostream>
#include <mutex>

class DBManager
{
private:
    mongocxx::instance m_instance;
    const mongocxx::uri m_uri;
    mongocxx::client m_client;
    mongocxx::database m_db;
    mongocxx::collection m_words_collection;
    mongocxx::collection m_urls_collection;

    mutable std::mutex mtx;

public:
    DBManager();
    ~DBManager() = default;
    void store_urls(std::unordered_map<std::string, size_t> &urls_dict, std::string &parent_key);
    void store_words(std::unordered_map<std::string, size_t> &wordData, std::string &url);
    // void insert_word_count_to_mongodb(const std::string &word, const std::string &url, size_t count);
};
#endif