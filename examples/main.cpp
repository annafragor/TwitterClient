#include <twitter/client.h>

int main()
{
    std::map<const std::string, const std::string> data;
    data.insert(std::pair<const std::string, const std::string>("consumer key", CONSUMER_KEY));
    data.insert(std::pair<const std::string, const std::string>("consumer secret", CONSUMER_SECRET));
    Twitter::Client cl(data);

    std::cout << cl.check_connection() << std::endl;

    std::cout << ">------------------------------------------------------------";

    std::vector<Twitter::Tweet> tweets = cl.get_tweets("@taylorswift13", "10");
    for(auto& k : tweets)
    {
        std::cout << k;
    }
}

