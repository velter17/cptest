#pragma once

#include <fstream>
#include "filesystem/filesystem.hpp"

namespace CPTest {
namespace Filesystem {

const std::string read_from_stream(std::istream&& stream);
void write_to_stream(std::ostream&& stream, const std::string& str);
const std::string read_from_file(const boost::filesystem::path& path);
void write_to_file(const boost::filesystem::path& path, const std::string& str);

} // namespace Filesystem
} // namespace CPTest
