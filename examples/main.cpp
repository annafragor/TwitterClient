#include <twitter/client.h>

int main()
{
    Twitter::Client cl;
    cl.check_connection(CONSUMER_KEY, CONSUMER_SECRET);
    std::cout << ">------------------------------------------------------------" << std::endl;
    cl.get_tweets("@taylorswift13", "3");
}

