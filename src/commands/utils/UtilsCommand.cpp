#include "commands/UtilsCommand.hpp"
#include "status/status.hpp"
#include "test_archive/Archive.hpp"

namespace CPTest {

CUtilsCommand::CUtilsCommand()
{
    using std::placeholders::_1;

    m_funcs = {
        {"test_folder", std::bind(&CUtilsCommand::testFolder, this, _1)},
        {"test_count", std::bind(&CUtilsCommand::testCount, this, _1)},
        {"is_problem_dir", std::bind(&CUtilsCommand::isProblemDir, this, _1)},
    };
}

ICommand::EResult CUtilsCommand::run(const std::vector<std::string>& args)
{
    if (args.empty())
    {
        std::cout << "???" << std::endl;
        return EResult::Failed;
    }
    auto itr = m_funcs.find(args.front());
    if (itr == m_funcs.end())
    {
        std::cout << "???" << std::endl;
        return EResult::Failed;
    }

    auto vec = args;
    vec.erase(vec.begin());

    return (*itr).second(vec);
}

ICommand::EResult CUtilsCommand::testFolder(const std::vector<std::string>& args)
{
    auto f = test_folder();
    if (f != Filesystem::PathType())
    {
        std::cout << f.filename().string() << std::endl;
        return EResult::Success;
    }
    else
    {
        return EResult::Failed;
    }
}

ICommand::EResult CUtilsCommand::testCount(const std::vector<std::string>& args)
{
    auto f = test_folder();
    TestArchive::CTestArchive<TestArchive::CStoredTest> archive(f);
    std::cout << archive.size() << std::endl;
    return EResult::Success;
}

ICommand::EResult CUtilsCommand::isProblemDir(const std::vector<std::string>&)
{
    return is_problem_folder() ? EResult::Success : EResult::Failed;
}

} // namespace CPTest
