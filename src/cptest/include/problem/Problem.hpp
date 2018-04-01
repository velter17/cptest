#pragma once

#include "filesystem/filesystem.hpp"

namespace CPTest {
namespace Problem {

class CProblem
{
public:
    CProblem(const Filesystem::PathType& path = Filesystem::get_current_path());
    CProblem(const std::string& name);
};

} // namespace Problem
} // namespace CPTest
