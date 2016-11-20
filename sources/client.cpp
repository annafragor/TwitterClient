//
// Created by anna on 25.10.16.
//

#include <twitter/client.h>

Twitter::Client::Client(std::map<const std::string, const std::string> input_data) :
        bearer_token(""), client_handle(curl_easy_init())
{
    std::string str;
    if (client_handle)
    {
        curl_easy_setopt(client_handle, CURLOPT_URL, "https://api.twitter.com/oauth2/token");
        curl_easy_setopt(client_handle, CURLOPT_POST, 1);

        //client header list
        curl_slist* client_hlist = nullptr;
        const std::string my_bearer = input_data["consumer key"] + ":" + input_data["consumer secret"];
        std::string my_base64_bearer = encode64(my_bearer);

        client_hlist = curl_slist_append(client_hlist, ("Authorization: Basic " + my_base64_bearer).c_str());
        client_hlist = curl_slist_append(client_hlist, URL_SEPARATOR.c_str());
        client_hlist = curl_slist_append(client_hlist, "Content-Type=applicatioт/x-www-form-urlencoded");

        std::string post_body_data;
        post_body_data += "grant_type=client_credentials";

        curl_easy_setopt(client_handle, CURLOPT_HTTPHEADER, client_hlist);
        curl_easy_setopt(client_handle, CURLOPT_POSTFIELDS, post_body_data.c_str());
        curl_easy_setopt(client_handle, CURLOPT_POSTFIELDSIZE, post_body_data.length());

        std::string content; std::string header;
        curl_easy_setopt(client_handle, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(client_handle, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(client_handle, CURLOPT_HEADERFUNCTION, write_to_string);
        curl_easy_setopt(client_handle, CURLOPT_WRITEHEADER, header);

        if (curl_easy_perform(client_handle) == CURLE_OK)
        {
            std::regex test_content("\\{\"token_type\":\"bearer\",\"access_token\":\"(.*)\"\\}");
            std::smatch result;
            if(std::regex_search(content, result, test_content))
            {
                bearer_token = result[1];
                curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
            }
        }
        curl_slist_free_all(client_hlist);
        curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
    }
}

Twitter::Client::~Client()
{
    curl_easy_cleanup(client_handle);
}

auto Twitter::Client::check_connection() -> bool
{
    if(!bearer_token.length())
        return false;
    else
        return true;
}

auto Twitter::Client::get_tweets(std::string username, std::string tweets_num) -> std::vector<Tweet>
{
    curl_easy_setopt(client_handle, CURLOPT_POST, 0);
    curl_easy_setopt(client_handle, CURLOPT_HTTPGET, 1L);

    std::string content; std::string header;
    curl_easy_setopt(client_handle, CURLOPT_WRITEFUNCTION, write_to_string);
    curl_easy_setopt(client_handle, CURLOPT_WRITEDATA, &content);
    curl_easy_setopt(client_handle, CURLOPT_HEADERFUNCTION, write_to_string);
    curl_easy_setopt(client_handle, CURLOPT_WRITEHEADER, header);

    curl_slist* client_hlist = nullptr;
    std::string str = "Authorization: Bearer " + bearer_token;
    client_hlist = curl_slist_append(client_hlist, str.c_str());
    curl_easy_setopt(client_handle, CURLOPT_HTTPHEADER, client_hlist);

    //curl_easy_setopt(client_handle, CURLOPT_VERBOSE, 1L);

    std::string url;
    url = std::string("https://api.twitter.com/1.1/search/tweets.json?") + "q=" + escape(client_handle, username);
    url = url + URL_SEPARATOR + "count=" + tweets_num + URL_SEPARATOR + "result_type=recent";
    curl_easy_setopt(client_handle, CURLOPT_URL, url.c_str());

    size_t num = 0;
    std::vector<Tweet> result_tweets;
    if(curl_easy_perform(client_handle) == CURLE_OK)
    {
        try
        {
            json result = json::parse(content);
            json statuses = result["statuses"];
            for (json::iterator it = statuses.begin(); it != statuses.end(); ++it, ++num)
            {
                Tweet tweet;

                json text = it.value()["text"];
                if(!text.is_null())
                    tweet.text = text.begin().value();

                json created_at = it.value()["created_at"];
                if(!created_at.is_null())
                    tweet.created_at = created_at.begin().value();

                json retweet_count = it.value()["retweet_count"];
                if(!retweet_count.is_null())
                    tweet.retweet_count = retweet_count.begin().value();

                json user = it.value()["user"];
                if(!user.is_null())
                    tweet.username = user["screen_name"];

                result_tweets.push_back(tweet);
            }
        } catch(...)
        {
            std::cerr << "There was an error in parsing server answer. Return value will be empty" << std::endl;
            result_tweets.clear();
        }
    }
    curl_slist_free_all(client_hlist);
    curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
    return result_tweets;
}

auto Twitter::Client::write_to_string(void* ptr, size_t size, size_t count, void* stream) -> size_t
{
    ((std::string*)stream)->append((char*)ptr, 0, size*count);
    return size*count;
}

auto Twitter::Client::escape(CURL* curl_handle, const std::string& link) noexcept -> std::string try
{
    std::string result_url;

    //преобразование в URL вид
    char* esc_link = curl_easy_escape(curl_handle, link.c_str(), (int)link.length());
    if(!esc_link)
        throw std::runtime_error("Can't convert string to URL");

    result_url = esc_link;
    curl_free(esc_link); //обязательно делать, если был curl_easy_escape

    return result_url;
}
catch(std::runtime_error& err)
{
    std::cerr << err.what() << std::endl;
}