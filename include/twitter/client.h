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

namespace Twitter
{
    class Client
    {
    private:
        std::string bearer_token;
        CURL* client_handle;

    public:
        Client();
        ~Client();
        auto check_connection() -> bool;

        static auto write_to_string(void* data, size_t size, size_t nmemb, void* stream) -> size_t;
        static auto escape(CURL* curl_handle, const std::string& link) noexcept -> std::string;
        static auto read_callback(void* ptr, size_t size, size_t nmemb, void* stream) -> size_t;
    };
}

#endif //TWITTERCLIENT_CLIENT_H
