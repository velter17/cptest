#include "test_archive/Test.hpp"

namespace CPTest {
namespace TestArchive {

CTest::CTest(
    const std::string& input_data,
    const std::string& output_data,
    const std::string& additional_data)
    : m_input(input_data)
    , m_output(output_data)
    , m_additional_data(additional_data)
{
}

const std::string& CTest::getInput() const
{
    return m_input;
}

const std::string& CTest::getOutput() const
{
    return m_output;
}

const std::string& CTest::getAdditionalData() const
{
    return m_additional_data;
}

}
}
