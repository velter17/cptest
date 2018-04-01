#pragma once

#include "commands/CCommand.hpp"
#include "filesystem/filesystem.hpp"

namespace CPTest {

class CInitCommand : public CCommand
{
public:
    CInitCommand();

    ICommand::EResult run(const std::vector<std::string>& args) override;

    bool init(const Filesystem::PathType& path); 
};

} // namespace CPTest
