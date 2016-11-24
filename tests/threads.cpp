//
// Created by anna on 24.11.16.
//
#include <twitter/client.h>

std::mutex mut;
static size_t last_thr = 0;

void f(bool _v, const size_t thr_id, const std::vector<Twitter::Tweet>& tweets, const size_t n)
{
    std::chrono::system_clock::time_point thr_time = std::chrono::system_clock::now();
    std::time_t t;

    for(size_t i = thr_id; i < tweets.size(); i += n)
    {
        while(last_thr != thr_id) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
        std::lock_guard<std::mutex> lck(mut);
        std::cout << std::endl << "thread №" << thr_id + 1 << std::endl;
        if(_v)
        {
            t = std::chrono::system_clock::to_time_t(thr_time);
            std::cout << "thread №" << thr_id + 1 << " started at " << ctime(&t);
        }
        std::cout << tweets[i] << std::endl;

        if(last_thr == n - 1)
            last_thr = 0;
        else
            last_thr++;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(_v)
        {
            thr_time = std::chrono::system_clock::now();
            t = std::chrono::system_clock::to_time_t(thr_time);
            std::cout << "thread №" << thr_id + 1 << " ended at " << ctime(&t);
        }
    }
}

int main(int argc, char* argv[])
{
    std::map<const std::string, const std::string> data;
    data.insert(std::pair<const std::string, const std::string>("consumer key", CONSUMER_KEY));
    data.insert(std::pair<const std::string, const std::string>("consumer secret", CONSUMER_SECRET));
    Twitter::Client cl(data);

    if(cl.check_connection())
        std::cout << "connection was set" << std::endl;

    std::cout << ">------------------------------------------------------------";
    std::vector<Twitter::Tweet> tweets = cl.get_tweets("@taylorswift13", "5");
    for(auto& tweet : tweets)
        std::cout << tweet << std::endl << std::endl;

    std::cout << ">------------------------------------------------------------" << std::endl;
    size_t n = 3;
    std::cout << "Take into consideration, that " << std::thread::hardware_concurrency() <<
              " concurrent threads are supported." << std::endl;
    std::cout << "number of threads: " << n << std::endl;
    
    std::vector<std::thread> thrds(n);
    bool _v = false;
    if(argc == 2 && std::string(argv[1]) == "-v")
        _v = true;
    for(size_t i = 0; i < n; ++i)
        thrds[i] = std::thread(f, _v, i, std::ref(tweets), n);
    for(size_t i = 0; i < n; ++i)
        if(thrds[i].joinable())
            thrds[i].join();
}
