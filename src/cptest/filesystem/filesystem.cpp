#include "filesystem/filesystem.hpp"

namespace CPTest {
namespace Filesystem {

const PathType get_current_path()
{
    return boost::filesystem::current_path();
}

const PathType get_abs_path(const PathType& path)
{
    return boost::filesystem::absolute(path, get_current_path());
}

const std::string get_file_name(const PathType& path)
{
    return path.filename().string();
}

const std::string get_file_extension(const PathType& path)
{
    return path.extension().string();
}

bool exists(const PathType& path)
{
    return boost::filesystem::exists(path);
}

} // namespace Filesystem
} // namespace CPTest
