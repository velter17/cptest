#include "filesystem/io.hpp"

namespace CPTest {
namespace Filesystem {

const std::string read_from_stream(std::istream&& stream)
{
    std::string ret;
    std::string tmp;
    while (std::getline(stream, tmp))
    {
        ret += tmp + "\n";
    }
    if (!ret.empty())
    {
        ret.pop_back();
    }
    return ret;
}

void write_to_stream(std::ostream&& stream, const std::string& str)
{
    stream << str;
}

const std::string read_from_file(const boost::filesystem::path& path)
{
    return read_from_stream(std::ifstream(path.string()));
}

void write_to_file(const boost::filesystem::path& path, const std::string& str)
{
    write_to_stream(std::ofstream(path.string()), str);
}

} // namespace Filesystem
} // namespace CPTest
