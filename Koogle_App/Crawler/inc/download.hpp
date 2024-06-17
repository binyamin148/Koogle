#ifndef DOWNLOAD_HPP
#define DOWNLOAD_HPP

#include <string>
#include <vector>

class Download
{
public:
    Download() = default;
    ~Download() = default;

    static std::string download_html(const std::string &url);
};

#endif // DOWNLOAD_HPP
