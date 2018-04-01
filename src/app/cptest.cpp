#include <atomic>
#include <boost/program_options.hpp>
#include <csignal>
#include <iostream>
#include <thread>
#include <vector>
#include "output/output.hpp"
#include "private/CommandFactory.hpp"

using namespace CPTest;

namespace {

std::atomic_bool s_done;

void handlesigterm(int)
{
    s_done.store(true);
}

const std::vector<std::string> prepare_args(int argc, char** argv)
{
    std::vector<std::string> ret;
    for (int i = 2; i < argc; ++i)
        ret.emplace_back(argv[i]);
    return ret;
}

} // namespace

int main(int argc, char** argv)
try
{
    if (argc == 1)
    {
        error("No arguments");
        return 1;
    }

    auto command = CCommandFactory{}.create(argc, argv);
    auto res = command->run(prepare_args(argc, argv));
    return res == ICommand::EResult::Success ? 0 : 1;
}
catch(const std::runtime_error& er)
{
    error(std::string{"Runtime error: "} + er.what());
}
catch(const boost::program_options::error& e)
{
    error(std::string{"with options: "} + e.what());
}
catch(...)
{
    error(std::string{"Unexpected error"});
}
