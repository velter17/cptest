#include "filesystem/temp.hpp"
#include "filesystem/io.hpp"

namespace CPTest {
namespace Filesystem {

const Filesystem::PathType createTempDir()
{
    auto ret = FS::temp_directory_path() / FS::unique_path();
    FS::create_directory(ret);

    return ret;
}

const Filesystem::PathType createTempFile(const std::string& content, const std::string& extension)
{
    auto ret = FS::temp_directory_path() / (FS::unique_path().string() + extension);
    if (!content.empty())
    {
        write_to_file(ret, content);
    }

    return ret;
}

bool remove(const Filesystem::PathType& path)
{
    if (Filesystem::exists(path))
    {
        FS::remove(path);
        return true;
    }
    else
    {
        return false;
    }
}

} // namespace Filesystem
} // namespace CPTest
