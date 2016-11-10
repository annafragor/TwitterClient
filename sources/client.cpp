//
// Created by anna on 25.10.16.
//

#include <twitter/client.h>

Twitter::Client::Client() : bearer_token("")
{
    client_handle = curl_easy_init();
}

Twitter::Client::~Client()
{
    curl_easy_cleanup(client_handle);
}

auto Twitter::Client::check_connection(const std::string cons_key, const std::string cons_secret) -> bool
{
    std::string str;
    if (client_handle)
    {
        curl_easy_setopt(client_handle, CURLOPT_URL, "https://api.twitter.com/oauth2/token");
        curl_easy_setopt(client_handle, CURLOPT_POST, 1);

        curl_slist* client_hlist = nullptr; //client header list
        client_hlist = curl_slist_append(client_hlist, "Authorization: Basic eE5EWjA2UFVoNXB1WFRzUDZ1OU5OQ1dBWjp2dzRTamdaMTUwSDBIQzY1MzZsajJJTzhrdHp5V2hQNTJtTE9TVEZVQ2l0cVFOeGQ5SQ==");
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

        // для более полной информации о процессе, которая будет выводить в консоли
        //curl_easy_setopt(client_handle, CURLOPT_VERBOSE, 1L);

        if (curl_easy_perform(client_handle) == CURLE_OK)
        {
            curl_slist_free_all(client_hlist);

            std::cout << "content: " << std::endl << content << std::endl;
            std::cout << "header: " << std::endl << header << std::endl;

            std::regex test_content("\\{\"token_type\":\"bearer\",\"access_token\":\"(.*)\"\\}");
            std::smatch result;
            if(std::regex_search(content, result, test_content))
            {
                bearer_token = result[1];
                curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
                return true;
            }
        }
        curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
    }
    return false;
}

auto Twitter::Client::get_tweets(std::string username, std::string tweets_num) -> void
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

    size_t num = 1;
    if(curl_easy_perform(client_handle) == CURLE_OK)
    {
        std::cout << "header:" << std::endl << header << std::endl;
        std::cout << "content: " << std::endl << content << std::endl;

        json result = json::parse(content);
        json statuses = result["statuses"];
        for (json::iterator it = statuses.begin(); it != statuses.end(); ++it, ++num)
        {
            json text = it.value()["text"];
            if (!text.is_null())
                std::cout << "tweet №" << num << ": " << text.begin().value() << std::endl;
        }
    }
    curl_slist_free_all(client_hlist);
    curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
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
    std::cout << err.what() << std::endl;
}