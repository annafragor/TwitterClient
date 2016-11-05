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

auto Twitter::Client::check_connection() -> bool
{
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

        CURLcode res = curl_easy_perform(client_handle);
        curl_slist_free_all(client_hlist);

        std::cout << curl_easy_strerror(res) << std::endl;
        std::cout << "content: " << std::endl << content << std::endl;
        std::cout << "header: " << std::endl << header << std::endl;

        std::regex test_content("\\{\"token_type\":\"bearer\",\"access_token\":\"(.*)\"\\}");
        std::smatch result;
        std::regex_search(content, result, test_content);
        std::cout << "!!! " << result[1] << std::endl;
    }
    curl_easy_reset(client_handle); //обнуляем все ранее заданные опции данного хендла
    return true;
}

static size_t write_head(char* ptr, size_t size, size_t nmemb, std::ostream* stream)
{
    (*stream) << std::string(ptr, size * nmemb);
    return size * nmemb;
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
