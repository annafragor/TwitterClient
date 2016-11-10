//
// Created by anna on 25.10.16.
//

#ifndef TWITTERCLIENT_CLIENT_H
#define TWITTERCLIENT_CLIENT_H

#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>

#include <twitter/constants.h>
#include <json.h>
#include <twitter/base64.h>

using json = nlohmann::json;

namespace Twitter
{
    class Client
    {
    private:
        std::string bearer_token;
        CURL* client_handle;
        static auto write_to_string(void*, size_t, size_t, void*) -> size_t;
        static auto escape(CURL*, const std::string&) noexcept -> std::string;

    public:
        Client();
        ~Client();
        auto check_connection(const std::string, const std::string) -> bool;
        auto get_tweets(std::string, std::string) -> void;
    };
}

#endif //TWITTERCLIENT_CLIENT_H
