#include "test_archive/StoredTest.hpp"
#include <iomanip>
#include <sstream>
#include "filesystem/temp.hpp"
#include "filesystem/io.hpp"
#include "aixlog/aixlog.hpp"

namespace CPTest {
namespace TestArchive {

CStoredTest::CStoredTest(
    const Filesystem::PathType& file_input,
    const Filesystem::PathType& file_output,
    const Filesystem::PathType& file_add_data)
    : m_input_file_path(file_input)
    , m_output_file_path(file_output)
    , m_additional_data_file_path(file_add_data)
{
}

CStoredTest::CStoredTest(const Filesystem::PathType& test_path, std::size_t number)
{
    std::stringstream test_name;
    test_name << std::setfill('0') << std::setw(3) << number;

    const std::string input_name = std::string(test_name.str()) + ".dat";
    const std::string output_name = std::string(test_name.str()) + ".ans";
    const std::string add_name = std::string(test_name.str()) + ".add";

    m_additional_data_file_path =
        Filesystem::exists(test_path / add_name) ? test_path / add_name : Filesystem::PathType();
    m_input_file_path = test_path / input_name;
    m_output_file_path = test_path / output_name;
}

bool CStoredTest::exists() const
{
    return Filesystem::exists(m_input_file_path) && Filesystem::exists(m_output_file_path);
}

void CStoredTest::deleteFiles()
{
    assert ("Test files don't exist for deletion" && exists());
    Filesystem::remove(m_input_file_path);
    Filesystem::remove(m_output_file_path);
    if (m_additional_data_file_path != Filesystem::PathType())
    {
        Filesystem::remove(m_additional_data_file_path);
    }
}

void CStoredTest::changeNumber(std::size_t new_number)
{
    CStoredTest tmp(m_input_file_path.parent_path(), new_number);
    assert (!tmp.exists() && "Cannot change number - test is occupied");
    Filesystem::FS::rename(m_input_file_path, tmp.inputFile());
    Filesystem::FS::rename(m_output_file_path, tmp.outputFile());
    if (Filesystem::exists(m_additional_data_file_path))
    {
        Filesystem::FS::rename(m_additional_data_file_path, tmp.additionalDataFile());
    }
}

CTest CStoredTest::getTest() const
{
    assert("Test files don't exist" && exists());
    return CTest(
        Filesystem::read_from_file(inputFile()),
        Filesystem::read_from_file(outputFile()),
        Filesystem::exists(m_additional_data_file_path)
            ? Filesystem::read_from_file(m_additional_data_file_path)
            : std::string());
}

const Filesystem::PathType& CStoredTest::inputFile() const
{
    return m_input_file_path;
}

const Filesystem::PathType& CStoredTest::outputFile() const
{
    return m_output_file_path;
}

const Filesystem::PathType& CStoredTest::additionalDataFile() const
{
    return m_additional_data_file_path;
}

CTempStoredTest::CTempStoredTest(const CTest& test)
    : CStoredTest(
          Filesystem::createTempFile(test.getInput(), ".dat"),
          Filesystem::createTempFile(test.getOutput(), ".ans"),
          Filesystem::createTempFile(test.getAdditionalData(), ".add"))
{
}

CTempStoredTest::~CTempStoredTest()
{
    Filesystem::remove(inputFile());
    Filesystem::remove(outputFile());
    Filesystem::remove(additionalDataFile());
}

} // namespace TestArchive
} // namespace CPTest
