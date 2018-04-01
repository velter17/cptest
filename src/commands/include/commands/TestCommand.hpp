#pragma once

#include "commands/CCommand.hpp"

namespace CPTest {

class CTestCommand : public CCommand
{
public:
    using TestList = std::vector<std::size_t>;
public:
    CTestCommand();

    EResult run(const std::vector<std::string>& args) override;

private:
    EResult printTest(const TestList& tests);
    EResult printInfo();
    EResult addTest();
    EResult removeTests(TestList tests);
    EResult copyTests(const TestList& tests, const std::string& dest_folder);
    EResult moveTests(const TestList& tests, const std::string& dest_folder);
    EResult checkout(const std::string& folder);

    TestList readTests(const std::vector<std::string>& tests);
};

} // namespace CPTest
