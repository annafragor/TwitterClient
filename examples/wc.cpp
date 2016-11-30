//
// Created by anna on 30.11.16.
//
#include <twitter/client.h>

namespace bp = ::boost::process;

std::regex control_string("\\s*(\\S+)\\s*(.*)\\s*");

void word_counter(std::string str, size_t& counter)
{
    std::smatch res;
    if(std::regex_match(str, res, control_string))
    {
        ++counter;
        word_counter(res[2].str(), counter);
    }
}

int main(int argc, char* argv[])
{
    std::string exec;
    std::vector<std::string> args(1, "");
    if((argc != 3) && (argc != 2))
    {
        std::cout << "wrong number of arguments!" << std::endl;
        return 0;
    } else
    {
        exec = argv[1];
        if(argc == 3)
            args[0] = argv[2];
    }

    size_t counter = 0;

    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();
    ctx.stdin_behavior = bp::capture_stream();

    bp::child c = bp::launch(exec, args, ctx);

    bp::postream &os = c.get_stdin();
    bp::pistream &is = c.get_stdout();

    os << "3\n";
    os.close();

    std::string line;
    while (std::getline(is, line))
        word_counter(line, counter);

    std::cout << "number of words = " << counter << std::endl;
}