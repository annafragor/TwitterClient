#include <twitter/client.h>

int main()
{
    std::map<const std::string, const std::string> data;
    data.insert(std::pair<const std::string, const std::string>("consumer key", CONSUMER_KEY));
    data.insert(std::pair<const std::string, const std::string>("consumer secret", CONSUMER_SECRET));
    Twitter::Client cl(data);

    if(cl.check_connection())
        std::cout << "connection was set" << std::endl;

    std::cout << ">------------------------------------------------------------";

    std::vector<Twitter::Tweet> tweets = cl.get_tweets("@taylorswift13", "3");
    for(auto& k : tweets)
    {
        std::cout << k;
    }
}

