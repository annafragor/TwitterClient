#include <twitter/client.h>

int main()
{
    Twitter::Client cl;
    cl.check_connection();
    std::cout << ">------------------------------------------------------------" << std::endl;
    cl.get_tweets("@taylorswift13", "3");
}

