#include <bits/stdc++.h>
#include "test_archive/Archive.hpp"
#include "filesystem/filesystem.hpp"
#include "aixlog/aixlog.hpp"

using namespace CPTest;

int main(int argc, char** argv)
{
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace, AixLog::Type::normal);

    Filesystem::PathType test_path = argv[1];
    if (!Filesystem::exists(test_path))
    {
        std::cerr << "Test path doesn't exist" << std::endl;
        return 1;
    }

    TestArchive::CTestArchive<TestArchive::CStoredTest> archive(test_path);
    LOG(INFO) << "archive size is " << archive.size() << std::endl;
    LOG(INFO) << "input: " << archive[0].getTest().getInput() << std::endl;
    LOG(INFO) << "output: " << archive[0].getTest().getOutput() << std::endl;
    return 0;
}

