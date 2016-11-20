//
// Created by anna on 25.10.16.
//

#ifndef TWITTERCLIENT_CLIENT_H
#define TWITTERCLIENT_CLIENT_H

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <exception>
#include <curl/curl.h>

#include <twitter/constants.h>
#include <twitter/base64.h>
#include <json.h>

using json = nlohmann::json;

namespace Twitter
{
    struct Tweet
    {
        std::string text;
        std::string created_at;
        std::string username;
        size_t retweet_count;

        friend auto operator << (std::ostream& out, const Tweet& tweet) -> std::ostream&
        {
            out << "\nauthor: " << tweet.username;
            out << "\ntext: " << tweet.text;
            out << "\ncreated_at: " << tweet.created_at;
            out << "\nretweets: " << tweet.retweet_count << "\n";
            return out;
        }
    };

    class Client
    {
    private:
        std::string bearer_token;
        CURL* client_handle;
        static auto write_to_string(void*, size_t, size_t, void*) -> size_t;
        static auto escape(CURL*, const std::string&) noexcept -> std::string;

    public:
        Client();
        Client(std::map<const std::string, const std::string>);
        ~Client();
        auto check_connection() -> bool;
        auto get_tweets(std::string, std::string) -> std::vector<Tweet>;
    };
}

#endif //TWITTERCLIENT_CLIENT_H
