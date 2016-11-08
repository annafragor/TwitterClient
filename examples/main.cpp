#include <twitter/client.h>

int main()
{
    Twitter::Client cl;
    cl.check_connection();
    std::cout << ">------------------------------------------------------------" << std::endl;
    json last_tweets = cl.get_tweets("@taylorswift13");
    // можно что-либо делать с данными о последних уоминаниях об аккаунте
    std::cout << std::endl << "the end" << std::endl;
}

