#include "commands/InitCommand.hpp"
#include "output/output.hpp"
#include "filesystem/filesystem.hpp"
#include "settings_reader/SettingsFile.hpp"
#include "status/status.hpp"
#include "filesystem/io.hpp"

namespace CPTest {

CInitCommand::CInitCommand()
{
}

ICommand::EResult CInitCommand::run(const std::vector<std::string>& args)
{
    auto read_result = readArgs(args);
    if (read_result != ICommand::EResult::Success)
    {
        return ICommand::EResult::Success;
    }

    if (!init(Filesystem::get_current_path()))
    {
        return EResult::Failed;
    }

    return EResult::Success;
}

bool CInitCommand::init(const Filesystem::PathType& path)
{
    if (is_problem_folder(path))
    {
        error("This folder is already initialized");
        return false;
    }

    auto cptest_p = cptest_path(path);
    if (!Filesystem::exists(cptest_p))
    {
        boost::filesystem::create_directory(cptest_p);
    }
    Filesystem::write_to_file(cptest_p / c_problem_file, "");
    Settings::CSettingsFile settings(cptest_p / c_problem_file);
    settings.set("test_dir", "main");
    info("Problem was initialized");
    if (!Filesystem::exists(path / "tests"))
    {
        boost::filesystem::create_directory(path / "tests");
        info("'tests' folder was created");
    }
    return true;
}

} // namespace CPTest
