#include "../inc/db_manager.hpp"
#include "../inc/settings.hpp"
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <vector>

DBManager::DBManager()
    : m_uri(Settings::URI_CONNECTION)
    ,m_client(m_uri)
    ,m_db(m_client[Settings::DB_NAME])
    ,m_words_collection(m_db[Settings::WORDS_COLLECTION])
    ,m_urls_collection(m_db[Settings::URLS_COLLECTION])

{
}

void DBManager::store_urls(std::unordered_map<std::string, size_t> &urls_dict, std::string &parent_key)
{
    std::unique_lock<std::mutex> g{mtx};
    try
    {
        bsoncxx::builder::stream::document document{};

        document << "_id" << parent_key;

        for (const auto &[url, count] : urls_dict)
        {
            document << url << static_cast<int64_t>(count);
        }
        m_urls_collection.insert_one(document.view());
    }
    catch (const mongocxx::exception &e)
    {
    }
    catch (const std::exception &e)
    {
    }
}

void DBManager::store_words(std::unordered_map<std::string, size_t> &words_vec, std::string &url)
{
    std::unique_lock<std::mutex> g{mtx};
    for (const auto &[word, count] : words_vec)
    {
        bsoncxx::builder::stream::document filter;
        bsoncxx::builder::stream::document update;

        // Create filter for the word
        filter << "word" << word;

        // Create the update document with $push for the links array
        update << "$set" << filter
               << "$push" << bsoncxx::builder::stream::open_document
               << "links" << bsoncxx::builder::stream::open_document
               << url << static_cast<int64_t>(count)
               << bsoncxx::builder::stream::close_document
               << bsoncxx::builder::stream::close_document;

        mongocxx::options::update options{};
        options.upsert(true);
        m_words_collection.update_one(filter.view(), update.view(), options);
    }
}

