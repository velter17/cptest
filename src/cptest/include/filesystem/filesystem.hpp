#pragma once

#include <boost/filesystem.hpp>

namespace CPTest {
namespace Filesystem {

namespace FS = boost::filesystem;
using PathType = FS::path;

const PathType get_current_path();
const PathType get_abs_path(const PathType& path);
const std::string get_file_name(const PathType& path);
const std::string get_file_extension(const PathType& path);
bool exists(const PathType& path);

} // namespace Filesystem
} // namespace CPTest
