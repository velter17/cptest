#pragma once

#include "filesystem/filesystem.hpp"

namespace CPTest {
namespace Filesystem {

const Filesystem::PathType createTempDir();
const Filesystem::PathType createTempFile(
    const std::string& content = std::string(),
    const std::string& extension = std::string());

bool remove(const Filesystem::PathType& path);

} // namespace Filesystem
} // namespace CPTest
