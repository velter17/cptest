#pragma once

#include "filesystem/filesystem.hpp"
#include "test_archive/Test.hpp"

namespace CPTest {
namespace TestArchive {

class CStoredTest
{
public:
    CStoredTest(
        const Filesystem::PathType& file_input,
        const Filesystem::PathType& file_output,
        const Filesystem::PathType& file_add_data = Filesystem::PathType());

    CStoredTest(const Filesystem::PathType& test_path, std::size_t number);

    bool exists() const;

    CTest getTest() const;

    void deleteFiles();
    void changeNumber(std::size_t new_number);

    const Filesystem::PathType& inputFile() const;
    const Filesystem::PathType& outputFile() const;
    const Filesystem::PathType& additionalDataFile() const;

private:
    Filesystem::PathType m_input_file_path;
    Filesystem::PathType m_output_file_path;
    Filesystem::PathType m_additional_data_file_path;
};

class CTempStoredTest : public CStoredTest
{
public:
    CTempStoredTest(const CTest& test);
    ~CTempStoredTest();
};

} // namespace TestArchive
} // namespace CPTest
