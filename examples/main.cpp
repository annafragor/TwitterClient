#include <twitter/client.h>

int main()
{
   /* std::cout << "ok" << std::endl;
    CURL* curl_handle;
    curl_handle = curl_easy_init();
    if (curl_handle)
    {
        std::cout << "ok" << std::endl;
        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://twitter.com");
        curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, stdout);

        CURLcode res = curl_easy_perform(curl_handle);
        if (res == CURLE_OK)
            std::cout << "CURLE_OK" << std::endl;
        else
            std::cout << "error: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl_handle);
    }*/

    Twitter::Client cl;
    cl.check_connection();



    time_t timer;
    time(&timer);
    std::cout << timer << std::endl;
}

