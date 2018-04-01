#include "status/status.hpp"

namespace CPTest {

bool is_problem_folder(const Filesystem::PathType& path)
{
    return is_cptest_folder(path) && Filesystem::exists(cptest_path(path) / c_problem_file);
}

bool is_cptest_folder(const Filesystem::PathType& path)
{
    return Filesystem::exists(cptest_path(path));
}

Filesystem::PathType test_folder(const Filesystem::PathType& path)
{
    Settings::CSettingsFile file(cptest_path(path) / c_problem_file);
    auto dir = file.get<std::string>("test_dir");
    auto ret = test_folder_by_name(dir, path);
    if (Filesystem::exists(ret))
    {
        return ret;
    }
    else
    {
        return Filesystem::PathType();
    }
}

Filesystem::PathType test_folder_by_name(const std::string& name, const Filesystem::PathType& path)
{
    if (name == "main")
    {
        return path / "tests";
    }
    else
    {
        return path / "tests" / name;
    }
}

Filesystem::PathType cptest_path(const Filesystem::PathType& path)
{
    return path / c_cptest_path;
}

} // namespace CPTest
