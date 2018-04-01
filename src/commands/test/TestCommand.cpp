#include "commands/TestCommand.hpp"
#include <queue>
#include "TestUtils.hpp"
#include "advanced_terminal_output/table.hpp"
#include "commands/InitCommand.hpp"
#include "status/status.hpp"
#include "termcolor/termcolor.hpp"
#include "test_archive/Archive.hpp"

namespace CPTest {

CTestCommand::CTestCommand()
{
    m_desc.add_options()("add,a", "add new test")
        ("print", boost::program_options::value<std::vector<std::string>>(), "print tests")
        ("checkout", boost::program_options::value<std::string>(), "change test folder")
        ("remove,r", boost::program_options::value<std::vector<std::string>>(), "remove tests")
        ("move,m", boost::program_options::value<std::string>/*??*/(), "move tests")
        ("copy,c", boost::program_options::value<std::string>/*??*/(), "copy tests");
    m_positional.add("print", 1000);
}

ICommand::EResult CTestCommand::run(const std::vector<std::string>& args)
{
    using namespace AdvancedTerm;

    auto read_result = readArgs(args);
    if (read_result != ICommand::EResult::Success)
    {
        return ICommand::EResult::Success;
    }

    if (!is_problem_folder())
    {
        CInitCommand{}.init(Filesystem::get_current_path());
    }

    if (m_var_map.count("add"))
    {
        return addTest();
    }
    else if (m_var_map.count("print"))
    {
        auto test_vec = m_var_map["print"].as<std::vector<std::string>>();
        TestList list;
        for (const auto& test_str : test_vec)
        {
            parseRange(test_str, list);
        }
        return printTest(list);
    }
    else if (m_var_map.count("checkout"))
    {
        checkout(m_var_map["checkout"].as<std::string>());
    }
    else if (m_var_map.count("remove"))
    {
        auto test_vec = m_var_map["remove"].as<std::vector<std::string>>();
        TestList list;
        for (const auto& test_str : test_vec)
        {
            parseRange(test_str, list);
        }
        removeTests(list);
    }
    else
    {
        return printInfo();
    }
}

ICommand::EResult CTestCommand::addTest()
{
    auto ret = system("/opt/cptest/bin/cptest_test_create.sh");
    return ret == 0 ? EResult::Success : EResult::Failed;
}

ICommand::EResult CTestCommand::printTest(const TestList& tests)
{
    using namespace AdvancedTerm;

    TestArchive::CTestArchive<TestArchive::CStoredTest> archive(test_folder());
    if (tests.empty())
    {
        warning("Archive is empty");
        return EResult::Success;
    }
    auto mx_element = *std::max_element(tests.begin(), tests.end());
    if (mx_element > archive.size())
    {
        error(std::to_string(mx_element) + " is out of range");
        return EResult::Failed;
    }

    auto header = createRow(
        createCell<EAlign::Center>(createData<termcolor::color<termcolor::LightMagenta>>("input")),
        createCell<EAlign::Center>(createData<termcolor::color<termcolor::LightYellow>>("output")));

    for (const auto& test_num : tests)
    {
        if (test_num == 0)
        {
            continue;
        }
        std::cout << ":" << test_num << std::endl;
        auto table = createTable(
            header,
            createRow(
                split(archive[test_num - 1].getTest().getInput()),
                split(archive[test_num - 1].getTest().getOutput())));
        std::cout << getTableStr(table);
    }
    return EResult::Success;
}

ICommand::EResult CTestCommand::printInfo()
{
    out("Problem is initialized\n");
    std::cout << termcolor::apply<termcolor::Green> << "Test folder: " << termcolor::reset
              << getProblemSetting<std::string>("test_dir") << std::endl;
    return EResult::Failed;
}

ICommand::EResult CTestCommand::removeTests(CTestCommand::TestList tests)
{
    std::sort(tests.begin(), tests.end());
    TestArchive::CTestArchive<TestArchive::CStoredTest> archive(test_folder());
    if (tests.empty())
    {
        warning("Archive is empty");
        return EResult::Success;
    }
    auto mx_element = *std::max_element(tests.begin(), tests.end());
    if (mx_element > archive.size())
    {
        error(std::to_string(mx_element) + " is out of range");
        return EResult::Failed;
    }

    for (const auto& id : tests)
    {
        archive[id - 1].deleteFiles();
    }

    std::queue<std::size_t> free_list;
    for (std::size_t i = 0; i < archive.size(); ++i)
    {
        if (!archive[i].exists())
        {
            free_list.push(i);
        }
        else if (!free_list.empty())
        {
            auto idx = free_list.front();
            free_list.pop();
            archive[i].changeNumber(idx + 1);
            free_list.push(i);
        }
    }
    out (std::to_string(tests.size()) + " tests was removed");
    return EResult::Success;
}

ICommand::EResult CTestCommand::copyTests(
    const CTestCommand::TestList& tests,
    const std::string& dest_folder)
{
}

ICommand::EResult CTestCommand::moveTests(
    const CTestCommand::TestList& tests,
    const std::string& dest_folder)
{
}

ICommand::EResult CTestCommand::checkout(const std::string& folder)
{
    /*TODO: check folder name*/

    auto cur_folder = test_folder();
    auto needed = test_folder_by_name(folder);
    if (cur_folder != needed)
    {
        if (!Filesystem::exists(needed) && !boost::filesystem::create_directory(needed))
        {
            error("Failed to checkout - cannot create directory " + needed.string());
            return EResult::Failed;
        }
        Settings::CSettingsFile settings(cptest_path() / c_problem_file);
        settings.set("test_dir", folder);
    }
    else
    {
        out("You are already using " + folder + " test folder");
    }
    return EResult::Success;
}

} // namespace CPTest
