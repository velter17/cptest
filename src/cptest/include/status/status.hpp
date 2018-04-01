#pragma once

#include <string>
#include "filesystem/filesystem.hpp"
#include "settings_reader/SettingsFile.hpp"

namespace CPTest {

const std::string c_cptest_path = ".cptest";
const std::string c_problem_file = "problem.ini";

bool is_problem_folder(const Filesystem::PathType& path = Filesystem::get_current_path());
bool is_cptest_folder(const Filesystem::PathType& path = Filesystem::get_current_path());

Filesystem::PathType test_folder(const Filesystem::PathType& path = Filesystem::get_current_path());
Filesystem::PathType test_folder_by_name(
    const std::string& name,
    const Filesystem::PathType& path = Filesystem::get_current_path());
Filesystem::PathType cptest_path(const Filesystem::PathType& path = Filesystem::get_current_path());

template <typename T>
T getProblemSetting(
    const std::string& property,
    const Filesystem::PathType& path = Filesystem::get_current_path())
{
    Settings::CSettingsFile file(cptest_path(path) / c_problem_file);
    return file.get<T>(property);
}

} // namespace CPTest
