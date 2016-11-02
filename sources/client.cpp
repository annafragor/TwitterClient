//
// Created by anna on 25.10.16.
//

#include <twitter/client.h>

Twitter::Client::Client() :
        Base64_BEARER_TOKEN("eE5EWjA2UFVoNXB1WFRzUDZ1OU5OQ1dBWjp2dzRTamdaMTUwSDBIQzY1MzZsajJJTzhrdHp5V2hQNTJtTE9TVEZVQ2l0cVFOeGQ5SQ==")
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
       /* curl_easy_setopt(client_handle, CURLOPT_URL, REQUEST_TOKEN_URL.c_str());
        curl_easy_setopt(client_handle, CURLOPT_CUSTOMREQUEST, "POST");

        //std::string post_header_data;
        //random_string в base64


        std::string sign;
        std::string str;
        str =   "POST" + URL_SEPARATOR + escape(client_handle, REQUEST_TOKEN_URL.c_str()) +
                URL_SEPARATOR +
                escape(client_handle, escape(client_handle, ("oauth_comsumer_key=" + CONSUMER_KEY).c_str())) +
                URL_SEPARATOR


        ;





        std::string oauth_nonce = "cmFuZG9tX3N0cmluZw==";
        curl_slist* post_header_data = nullptr;
        post_header_data = curl_slist_append(post_header_data, "Authorization:OAuth oauth_callback=");
        post_header_data = curl_slist_append(post_header_data, escape(client_handle, (CALLBACK_URL).c_str()).c_str());
        post_header_data = curl_slist_append(post_header_data, URL_SEPARATOR.c_str());
        post_header_data = curl_slist_append(post_header_data, "oauth_consumer_key=");
        post_header_data = curl_slist_append(post_header_data, (CONSUMER_KEY + URL_SEPARATOR).c_str());
        post_header_data = curl_slist_append(post_header_data, "oauth_nonce=");
        post_header_data = curl_slist_append(post_header_data, (oauth_nonce + URL_SEPARATOR).c_str());
        post_header_data = curl_slist_append(post_header_data, "oauth_signature_method=HMAC-SHA1");
        post_header_data = curl_slist_append(post_header_data, URL_SEPARATOR.c_str());
        post_header_data = curl_slist_append(post_header_data, "oauth_timestamp=");
        time_t timer;   time(&timer);
        post_header_data = curl_slist_append(post_header_data, (Twitter::to_string(timer) + URL_SEPARATOR).c_str());
        post_header_data = curl_slist_append(post_header_data, "oauth_signature=");
        post_header_data = curl_slist_append(post_header_data, "oauth_version=1.0");








             //   'POST&https%3A%2F%2Fapi.twitter.com%2Foauth%2Frequest_token&oauth_callb
        // ack%3D{http%253A%252F%252Fmysite.com%252Ftwlogin}%26oauth_consumer_key%3D{consumer_key}%26oauth_nonce%3D{random base64 srting}%26
        // oauth_signature_method%3DHMAC-SHA1%26oauth_timestamp%3D{time}%26oauth_version%3D1.0'










        std::string response;
        curl_easy_setopt(client_handle, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(client_handle, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(client_handle);

        std::cout << "response: " << response << std::endl;
        std::cout << "you should go to" << std::endl;
        std::cout << AUTHORIZE_URL << std::endl;





        char c;
        std::cin >> c;
        */

        curl_easy_setopt(client_handle, CURLOPT_URL, "https://api.twitter.com/oauth2/token");
        curl_easy_setopt(client_handle, CURLOPT_POST, 1);

        std::string post_header_data;
        post_header_data += "Authorization:Basic ";
        post_header_data += Base64_BEARER_TOKEN;
        post_header_data += URL_SEPARATOR;
        post_header_data += "Content-Type=application/";
        post_header_data += escape(client_handle, "https://apps.twitter.com/app/13018740");

        std::string post_body_data;
        post_body_data += "grant_type=client_credentials";

        std::string content; std::string header;
        curl_easy_setopt(client_handle, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(client_handle, CURLOPT_WRITEDATA, &content);
        curl_easy_setopt(client_handle, CURLOPT_HEADERFUNCTION, write_to_string);
        curl_easy_setopt(client_handle, CURLOPT_WRITEHEADER, header);
        FILE* read_f;
        read_f = fopen("~//TwitterClient//sources//post_body.txt", "rb");


        curl_easy_setopt(client_handle, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(client_handle, CURLOPT_READDATA, read_f);


        // для более полной информации о процессе, которая будет выводить в консоли
        curl_easy_setopt(client_handle, CURLOPT_VERBOSE, 1L);

       // curl_easy_setopt(client_handle, CURLOPT_FOLLOWLOCATION, 1);


        curl_easy_setopt(client_handle, CURLOPT_POSTFIELDS, post_header_data.c_str());
        curl_easy_setopt(client_handle, CURLOPT_POSTFIELDSIZE, post_header_data.length());

        CURLcode res = curl_easy_perform(client_handle);

        std::cout << curl_easy_strerror(res) << std::endl;
        std::cout << "content: " << std::endl << content << std::endl;
        std::cout << "header: " << std::endl << header << std::endl;
        std::cout << "you should go to" << std::endl;
        std::cout << AUTHORIZE_URL << std::endl;
    }
    return true;
}


static size_t read_callback(void *ptr, size_t size, size_t nmemb, void* stream)
{
    curl_off_t nread;
    /* in real-world cases, this would probably get this data differently
       as this fread() stuff is exactly what the library already would do
       by default internally */
    size_t retcode = fread(ptr, size, nmemb, stream);

    nread = (curl_off_t) retcode;

    fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
            " bytes from file\n", nread);
    return retcode;
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